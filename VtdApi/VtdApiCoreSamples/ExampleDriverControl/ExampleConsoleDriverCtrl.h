#ifndef EXAMPLE_CONSOLE_DRIVER_CTRL_H
#define EXAMPLE_CONSOLE_DRIVER_CTRL_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>
#include <VtdToolkit/Scp/ScpBuilder.h>

/**
 *  Class ExampleConsole Defines - the entry point for the console application and send simple driver control command
 */

using namespace VTD;

class ExampleConsoleDriverCtrl
{
public:
    /**
    * Constructor
    */
    ExampleConsoleDriverCtrl();
    /**
     * @brief handleRdbMessage - receive RDB
     * @param msg - RDB message
     */
    void handleRdbMessage(const ReceiveRDB* msg);
    /**
     * @brief processObjectState - procces object state
     * @param RDBMessage - RDB message
     * @param isExtended - true if message contains extended data structure
     */
    void processObjectState(const RDB_MSG_t& RDBMessage, const bool& isExtended);
    /**
     * @brief sendDriverCtrl - send trigger control command
     * @param RDBMessage - RDB message
     */
    void sendDriverCtrl(const RDB_MSG_t& RDBMessage);

    /**
     * @brief initVtdApi - initalaze VtdApi
     * @return true when API is initalized
     */
    bool initVtdApi();

    // handleIncommngOutgoing_ handle for incomming and outgoing RDB connection
    ConnectionHandle handleIncomingOutgoing_;

    // VTD api
    VtdApi api;

private:
    // Default player Id
    unsigned int playerId_;
};

#endif // EXAMPLE_CONSOLE_DRIVER_CTRL_H
