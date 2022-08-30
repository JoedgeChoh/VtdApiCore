#ifndef EXAMPLE_RDB_PRINT_H
#define EXAMPLE_RDB_PRINT_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>

/**
 * Class ExampleRdbPrint defines - the entry point for the console application.
 */

using namespace VTD;

class ExampleRdbPrint {
public:
    /**
     * constructor
     */
    ExampleRdbPrint(bool shouldSendTrigger);

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
     * @brief initVtdApi - initalaze VtdApi
     * @return true when API is initalized
     */
    bool initVtdApi();

    // Handle for incomming and outgoing RDB data
    ConnectionHandle ConnectionHandle_;

    // VtdApi instance
    VtdApi api_;

private:
    // Default player ID
    unsigned int playerId_;

    // If sample should send trigger
    bool shouldSendTrigger_;
};
#endif // EXAMPLE_RDB_PRINT_H
