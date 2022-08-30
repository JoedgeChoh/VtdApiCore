#ifndef EXAMPLE_ACC_H
#define EXAMPLE_ACC_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>

/**
 * Class ExampleAcc is an example how to use Vtd Api to receive data from sensor and to send driver control via TCP
 */

using namespace VTD;

class ExampleAcc
{
public:
    /**
    * Constructor
    */
     ExampleAcc();

    /**
     * @brief handleRdbMessage - receive RDB
     * @param msg - RDB message
     */
    void handleRdbMessage(const ReceiveRDB* msg);

    /**
     * @brief processObjectState - procces object state
     * @param RDBMessage - RDB message
     */
    void processObjectState(const RDB_MSG_t& RDBMessage, const bool& isExtended);

    /**
     * @brief proccesSensorObject - procces sensor objects
     * @param RDBMessage - RDB message
     */
    void proccesSensorObject(const RDB_MSG_t& RDBMessage);

    /**
     * @brief sendDriverCtrl - send driver control command
     * @param frameId - curent frame
     * @param simTime - simulation time
     */
    void sendDriverCtrl(const RDB_MSG_t& RDBMessage);

    /**
     * @brief initVtdApi - initalaze VtdApi
     * @return true when API is initalized
     */
    bool initVtdApi();

    // handleIncoming_ and handleOutgoing_ handles for incoming and outgoing RDB connection
    ConnectionHandle handleIncoming_, handleOutgoing_;

    // VTD api
    VtdApi api;

private:
    // Default player Id
    unsigned int playerId_;

    // nearest object destination
    double distanceToNearestObject_;

    // nearest object Id
    int nearestObjectDetectedId_;
};

#endif // EXAMPLE_ACC_H
