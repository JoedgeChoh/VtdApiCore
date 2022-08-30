#include "ExampleConsoleProxyPkg.h"

#include <cstdio>
#include <string>
#include <cmath>

namespace
{
    // default host local ip where VTD is running
    const std::string DEFAULT_HOST = "127.0.0.1";

    // default player
    static const unsigned int EGO_ID = 1;

    // proxy package Id
    static const unsigned int PROXY_PACKAGE_ID = 444;

    // if message not contains extended data structure
    static const bool OBJECT_STATE_NOT_EXTENDED = false;

    // 50 bytes
    static const size_t TRAILING_DATA_SIZE = 50;
}

ExampleConsoleProxyPkg::ExampleConsoleProxyPkg()
    : handleIncomingOutgoing_(0)
    , playerId_(EGO_ID)
{

}

bool ExampleConsoleProxyPkg::initVtdApi()
{
    // Handle for incoming data and outgoing data
    handleIncomingOutgoing_ = api.connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP);
    // Register event if RDB has been connected
    if(handleIncomingOutgoing_)
    {
        api.registerEventFunc<ExampleConsoleProxyPkg, ReceiveRDB>(this, &ExampleConsoleProxyPkg::handleRdbMessage, handleIncomingOutgoing_);
        return true;
    }
    else
    {
        printf("ERROR: Could not establish connection\n");
        return false;
    }
}

void ExampleConsoleProxyPkg::handleRdbMessage(const ReceiveRDB* msg)
{
    sendProxyPkg(msg->getData());

    processProxyState(msg->getData(), OBJECT_STATE_NOT_EXTENDED);
}

void ExampleConsoleProxyPkg::processProxyState(const RDB_MSG_t& RDBMessage, const bool& isExtended)
{
    unsigned int noElements = 0;

    RDB_PROXY_t* item = reinterpret_cast<RDB_PROXY_t*>(Framework::RDBHandler::getFirstEntry(&RDBMessage, RDB_PKG_ID_PROXY, noElements, isExtended));

    if(!noElements) return;

    fprintf(stderr, "handleRDBitem: handling proxy package\n");
    fprintf(stderr, "    simTime = %.3lf\n", RDBMessage.hdr.simTime);
    fprintf(stderr, "    protocol = %d\n", item->protocol);
    fprintf(stderr, "    pkgId    = %d\n", item->pkgId);
    fprintf(stderr, "    dataSize = %d\n", item->dataSize);

    unsigned char* myDataPtr = reinterpret_cast<unsigned char*>((reinterpret_cast<char*>(item)) + sizeof(RDB_PROXY_t));

    fprintf(stderr, "testData = %d\n", myDataPtr[0]);
}

void ExampleConsoleProxyPkg::sendProxyPkg(const RDB_MSG_t& RDBMessage)
{
    Framework::RDBHandler myHandler;

    myHandler.initMsg();

    RDB_PROXY_t* myProxy = reinterpret_cast<RDB_PROXY_t*> ((myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_PROXY, 1, false, TRAILING_DATA_SIZE)));

    if (!myProxy)
        return;

    myProxy->protocol = boost::numeric_cast<uint16_t>( RDBMessage.hdr.frameNo % 65000 );
    myProxy->pkgId = PROXY_PACKAGE_ID;
    myProxy->dataSize = TRAILING_DATA_SIZE;

    unsigned char* myDataPtr = reinterpret_cast<unsigned char*> ((reinterpret_cast<char*>(myProxy)) + sizeof(RDB_PROXY_t));

    myDataPtr[0] = static_cast<unsigned char>(RDBMessage.hdr.frameNo % 255);

   api.sendRdbMessage(handleIncomingOutgoing_, *myHandler.getMsg());;

}
