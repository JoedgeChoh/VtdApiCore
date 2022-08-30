#include "VtdApi/Internal/NetworkHandler.h"
#include "VtdApi/NetworkEvents.h"

#include <VtdCore/Logging/Log.h>
#include <VtdToolkit//viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>
#include <boost/lexical_cast.hpp>
#include <ComHandler.hh>

#include <cstdlib>
#include <sstream>
#include <string>

using namespace VTD;
using namespace VTD::Internal;

#ifndef VTD_API_BOOST

namespace {

template<typename T> std::string toString(T value)
{
    using boost::bad_lexical_cast;

    try
    {
        std::string temp = boost::lexical_cast<std::string>(value);
        return temp;
    }
    catch (const bad_lexical_cast &)
    {
        toString(value);
    }

}

//threadsafe initialization of ComHandler singleton (intialized before main)
Com::ComHandler* instantiateComHandler()
{
    Com::ComHandler* comHandler = Com::ComHandler::sInstance;
    if (!comHandler)
    {
        comHandler = new Com::ComHandler("VtdApi", NULL, false, false);
        if (!comHandler)
        {
            VTD_LOG_ERR("VtdApi: ComHandler could not be initialized! Abort.");
            exit(1);
        }
    }
    return comHandler;
}

} //namespace

Com::ComHandler* NetworkHandler::comHandler_ = instantiateComHandler();

NetworkHandler* NetworkHandler::getInstance()
{
    static NetworkHandler* instance = new NetworkHandler();
    return instance;
}
NetworkHandler* networkHandlerForceStaticInit = NetworkHandler::getInstance();

NetworkHandler::NetworkHandler()
    : Base()
{
    Base::setComHandler(NetworkHandler::comHandler_);
}

NetworkHandler::~NetworkHandler()
{ /**/ }

ConnectionHandle NetworkHandler::connect(const std::string& address, UInt port, VTD::IVtdApi::Protocol::Enum protocol)
{
    ConnectionHandle handle = generateHandle(address, port, protocol);
    std::string handleStr = toString(handle);
    bool result = false;

    ScopedLock<CriticalSection> lock(cs_);

    switch (protocol)
    {
    case VTD::IVtdApi::Protocol::RDB_UDP:
        result = comHandler_->initUDPPort(handleStr, address, port, true /*canSend*/, true /*canRcv*/);
        break;
    case VTD::IVtdApi::Protocol::RDB_UDP_SEND_ONLY:
        result = comHandler_->initUDPPort(handleStr, address, port, true /*canSend*/, false /*canRcv*/);
        break;
    case VTD::IVtdApi::Protocol::RDB_UDP_RECEIVE_ONLY:
        result = comHandler_->initUDPPort(handleStr, address, port, false /*canSend*/, true /*canRcv*/);
        break;
    case VTD::IVtdApi::Protocol::RDB_TCP:
    case VTD::IVtdApi::Protocol::SCP:
    default:
        result = comHandler_->createClientPort(handleStr, address, port, false /*blockSend*/, false /*blockRcv*/);
        break;
    }

    if (result && comHandler_->setProtocol(handleStr, Com::PortBase::protoMagic))
    {
        registerPortCallback(port);

        if (protocol == VTD::IVtdApi::Protocol::SCP)
        {
            scpConnectionStates_[handle].isConnected = true;
        }
        return handle;
    }

    return 0;
}

void NetworkHandler::incomingPackage(const Com::NetPackage& netPkg, const std::string& partner)
{
    const Com::PortBase::PortProtocol& protocol = netPkg.getProtocol();

    switch (protocol)
    {
    case Com::PortBase::protoSCP:
        handleSCPMessage(netPkg.getData(), netPkg.getSize(), partner);
        break;
    default:
        handleMessage(netPkg.getData(), netPkg.getSize(), protocol, partner);
        break;
    }
}

void NetworkHandler::handleSCPMessage(void* data, size_t /*size*/, const std::string& partner)
{
    unsigned char* dataPtr = static_cast<unsigned char*>(data);
    SCP_MSG_HDR_t* msg = static_cast<SCP_MSG_HDR_t*>(data);
    dataPtr += sizeof(SCP_MSG_HDR_t);

    scpMessageSignal_(msg, static_cast<void*>(dataPtr), partner);
}

void NetworkHandler::handleMessage(void* data, size_t size, int /*protocol*/, const std::string& partner)
{
    if ((data == 0) || (size < sizeof(RDB_MSG_HDR_t)))
        return;

    RDB_MSG_t* msg = static_cast<RDB_MSG_t*>(data);
    size_t totalSize = msg->hdr.dataSize + sizeof(RDB_MSG_HDR_t);

    if ((msg->hdr.magicNo != RDB_MAGIC_NO) || (size < totalSize))
        return;

    rdbMessageSignal_(msg, size, partner);
}

void NetworkHandler::update()
{
    ScopedLock<CriticalSection> lock(cs_);
    comHandler_->update();

    for (ConnectionStateMap::iterator it = scpConnectionStates_.begin(); it != scpConnectionStates_.end(); ++it)
    {
        bool& currentState = (it->second).isConnected;
        bool previousState = currentState;
        currentState = comHandler_->portIsConnected(toString(it->first));

        if (previousState != currentState) //only propagate state changes (connect, disconnect)
        {
            ConnectionEvent* event = new ConnectionEvent(it->first, currentState);
            event->partner = toString(it->first);
            connectionStateSignal_(event);
        }
    }
}


bool NetworkHandler::writeRdb(const ConnectionHandle& handle, RDB_MSG_t* message)
{
    ScopedLock<CriticalSection> lock(cs_);
    size_t totalSize = message->hdr.headerSize + message->hdr.dataSize;
    return (comHandler_->sendRaw(toString(handle), static_cast<void*>(message), totalSize) > 0);
}

bool NetworkHandler::writeScp(const ConnectionHandle& handle, SCP_MSG_HDR_t* message, size_t totalSize)
{
    ScopedLock<CriticalSection> lock(cs_);
    bool result = (comHandler_->sendRaw(toString(handle), static_cast<void*>(message), totalSize) > 0);
    delete[] message;
    return result;
}

bool NetworkHandler::isConnected(const ConnectionHandle& handle)
{
    ScopedLock<CriticalSection> lock(cs_);
    return comHandler_->portIsConnected(toString(handle));
}

UInt NetworkHandler::generateHandle(const std::string& hostname, unsigned int port, VTD::IVtdApi::Protocol::Enum protocol)
{
    UInt handle = protocol;
    handle = port + (handle << 6) + (handle << 16) - handle;
    const UInt length = hostname.length();
    for (UInt i = 0; i < length; ++i)
    {
        handle = hostname[i] + (handle << 6) + (handle << 16) - handle;
    }
    return handle;
}

void NetworkHandler::disconnectSCP(ConnectionHandle& handle)
{
    if(comHandler_->portIsConnected(toString(handle)))
    {
        comHandler_->deletePorts(toString(handle));
    }
}

void NetworkHandler::disconnectRDB(ConnectionHandle& handle)
{
    if(comHandler_->portIsConnected(toString(handle)))
    {
        comHandler_->deletePorts(toString(handle));
    }
}
#endif

