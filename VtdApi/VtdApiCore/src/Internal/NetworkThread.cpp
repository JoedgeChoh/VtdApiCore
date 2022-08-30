#include "VtdApi/Internal/NetworkThread.h"
#include "VtdApi/Internal/NetworkHandler.h"
#include "VtdApi/Internal/AsyncEventHandler.h"
#include "VtdApi/Events.h"
#include "VtdApi/NetworkEvents.h"

#include <VtdToolkit//scpIcd.h>
#include <VtdCore/Timer.h>
#include <VtdNetwork/Socket.h>
#include <VtdCore/Logging/Log.h>

#include <cmath>
#include <vector>
#include <sstream>

using namespace VTD;
using namespace VTD::Internal;

namespace {
    const char SENDER_NAME[] = "VtdApi";
    const char RECEIVER_NAE[] = "TaskControl";
}

namespace {

template<typename T> std::string toString(T value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

#define CASE_ENUM2STRING(value) case value: return #value
std::string portProtocolToString(int protocol) {
    switch(protocol) {
    CASE_ENUM2STRING(Com::PortBase::protoRaw);
    CASE_ENUM2STRING(Com::PortBase::protoSimcon);
    CASE_ENUM2STRING(Com::PortBase::protoVIRES);
    CASE_ENUM2STRING(Com::PortBase::protoSCP);
    CASE_ENUM2STRING(Com::PortBase::protoMagic);
    CASE_ENUM2STRING(Com::PortBase::protoGSI);
    CASE_ENUM2STRING(Com::PortBase::protoVTP);
    CASE_ENUM2STRING(Com::PortBase::protoRDB);
    CASE_ENUM2STRING(Com::PortBase::protoSUMO);
    default: return "UNKNOWN";
    }
}

} //namespace

#ifndef VTD_API_BOOST
NetworkThread::NetworkThread(AsyncEventHandler* scpHandler) :
    networkHandler_(NetworkHandler::getInstance()),
    eventHandler_(scpHandler),
    sleepTimeMus_(1500),
    isRunning_(false)
{
    networkHandler_->registerForRdb<NetworkThread>(this, &NetworkThread::handleRdb);
    networkHandler_->registerForScp<NetworkThread>(this, &NetworkThread::handleScp);
    networkHandler_->registerForConnectionEvent<NetworkThread>(this, &NetworkThread::handleConnectionEvent);
}

NetworkThread::~NetworkThread()
{
    /*DTOR*/
}

ConnectionHandle NetworkThread::connectScp(const std::string& hostname, UInt portNumber)
{
    return networkHandler_->connect(hostname, portNumber, VTD::IVtdApi::Protocol::SCP);
}

ConnectionHandle NetworkThread::connectRdb(const std::string& hostname, UInt portNumber, Protocol::Enum protocol)
{
    return networkHandler_->connect(hostname, portNumber, protocol);
}

bool NetworkThread::isConnectedScp(const ConnectionHandle& handle)
{
    return networkHandler_->isConnected(handle);
}

bool NetworkThread::isConnectedRdb(const ConnectionHandle& handle)
{
    return networkHandler_->isConnected(handle);
}

void NetworkThread::disconnectScp(ConnectionHandle& handle)
{
    networkHandler_->disconnectSCP(handle);
}

void NetworkThread::disconnectRdb(ConnectionHandle& handle)
{
    networkHandler_->disconnectRDB(handle);
}

bool NetworkThread::sendScpCommand(const ConnectionHandle& handle, const std::string& cmd)
{
    if(!networkHandler_->isConnected(handle)) {
        return false;
    }

    SizeType totalSize = sizeof(SCP_MSG_HDR_t) + cmd.length();

    unsigned char* data = new unsigned char[totalSize];
    SCP_MSG_HDR_t* msg  = reinterpret_cast<SCP_MSG_HDR_t*>(data);

    // target pointer for actual SCP message data
    data += sizeof(SCP_MSG_HDR_t);

    // fill the header information
    msg->magicNo  = SCP_MAGIC_NO;
    msg->version  = SCP_VERSION;
    msg->dataSize = cmd.length();
    memcpy(msg->sender, SENDER_NAME, SCP_NAME_LENGTH);
    memcpy(msg->receiver, RECEIVER_NAE, SCP_NAME_LENGTH);
    memcpy(data, cmd.c_str(), cmd.length());

    VTD_DEBUG_LOG("Send SCP: " << cmd);

    bool result = networkHandler_->writeScp(handle, msg, totalSize);

    return result;
}

bool NetworkThread::sendRdbMessage(const ConnectionHandle& handle, RDB_MSG_t& msg)
{
    return networkHandler_->writeRdb(handle, &msg);
}

void NetworkThread::run()
{
    isRunning_ = true;

    Timer timer;
    while(isRunning_) {
        timer.start();

        networkHandler_->update();

        UInt elapsedTime = static_cast<UInt>(std::ceil(timer.elapsedTime()));
        if(elapsedTime < sleepTimeMus_) {
            Thread::sleep(sleepTimeMus_ - elapsedTime);
        }
        else {
            Thread::yield();
        }
    }
}

void NetworkThread::handleRdb(RDB_MSG_t* msg, size_t size, const std::string& partner)
{
    if (!msg) {
        return;
    }

    RdbMessage* rdbMessage = new RdbMessage(*msg, size); //ownership is passed to AsyncEventHandler
    rdbMessage->partner = partner;
    eventHandler_->queueEvent(rdbMessage);
}

void NetworkThread::handleScp(SCP_MSG_HDR_t* msg, void* data, const std::string& partner)
{
    char* dataStr = new char[msg->dataSize + 1];
    if (!dataStr) {
        VTD_LOG_ERR("VtdApi: Could not allocate " << msg->dataSize+1 << " bytes.");
        return;
    }

    memset(dataStr, 0, msg->dataSize + 1);
    memcpy(dataStr, data, msg->dataSize);
    ScpMessage* scpMessage = new ScpMessage(*msg, std::string(dataStr)); //ownership is passed to AsyncEventHandler
    scpMessage->partner = partner;
    eventHandler_->queueEvent(scpMessage);
    delete[] dataStr;
}

void NetworkThread::handleConnectionEvent(ConnectionEvent* event)
{
    if (!event) {
        return;
    }
    eventHandler_->queueEvent(event);
}

void NetworkThread::stop()
{
    isRunning_ = false;
}
#endif
