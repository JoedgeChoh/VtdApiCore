#ifndef EXAMPLE_DIRECT_MODE_H
#define EXAMPLE_DIRECT_MODE_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>

/**
 * Class Example Direct Mode is an example how to use VtdApi for bufferless callbacks
 */

using namespace VTD;

class ExampleDirectMode
{
public:
    /**
     * constructor
     */
    ExampleDirectMode();

    /**
     * @brief handleRdbMessage - receive RDB
     * @param msg - RDB message
     */
    void handleRdbMessage(const ReceiveRDB* msg);

    /**
     * @brief handleScpMessage - receive SCP
     * @param msg - SCP message
     */
    void handleScpMessage(const ReceiveSCP* msg);

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
    ConnectionHandle connectionHandleRdb_;

    // Handle for incomming and outgoing SCP data
    ConnectionHandle connectionHandleScp_;

    // VtdApi instance
    VtdApi api_;
};

#endif // EXAMPLE_DIRECT_MODE_H
