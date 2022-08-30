#ifndef EXAMPLE_CONSOLE_PROXY_PKG_H
#define EXAMPLE_CONSOLE_PROXY_PKG_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>
#include <VtdToolkit/Scp/ScpBuilder.h>

/**
 * Class Example Console Proxy Pkg is an example how to use VtdApi to get proxy state
 */

using namespace VTD;

class ExampleConsoleProxyPkg
{
public:
     /**
     * Constructor
     */
     ExampleConsoleProxyPkg();

     /**
     * @brief handleRdbMessage - receive RDB
     * @param msg - RDB message
     */
    void handleRdbMessage(const ReceiveRDB* msg);

    /**
     * @brief processObjectState
     * @param RDBMessage
     */
    void processProxyState(const RDB_MSG_t& RDBMessage, const bool& isExtended);

    /**
     * @brief sendProxyPkg - send proxy package
     * @param RDBMessage
     */
    void sendProxyPkg(const RDB_MSG_t& RDBMessage);

    /**
     * @brief initVtdApi - initalaze VtdApi
     * @return true when API is initalized
     */
    bool initVtdApi();

    // handleInCominOutGoing_ handle for incomming and outgoing RDB ports
    ConnectionHandle handleIncomingOutgoing_;
    // VTD api
    VtdApi api;

private:
    // Ego Id most probably 1
    unsigned int playerId_;
};

#endif // EXAMPLE_CONSOLE_PROXY_PKG_H
