#ifndef EXAMPLE_VEH_DYN_INTEQ_H
#define EXAMPLE_VEH_DYN_INTEQ_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>

/**
 * Class Communication Sample is an example how to use Vtd Api to control vihecle
 */

using namespace VTD;

class ExampleVehDynInteg {
public:
    /**
     * constructor
     */
    ExampleVehDynInteg(void);

    /**
     * @brief handleRdbMessage - receive RDB
     * @param msg - RDB message
     */
    void handleRdbMessage(const ReceiveRDB* msg);

    /**
     * @brief processObjectState
     * @param RDBMessage
     */
    void processDriverControl(const RDB_MSG_t& RDBMessage, const bool& isExtended);

    /**
     * @brief processObjectState - procces object state
     * @param RDBMessage - RDB message
     */
    void processObjectState(const RDB_MSG_t& RDBMessage, const bool& isExtended);

    /**
     * @brief sendOwnObjectState -
     * @param RDBMessage - RDB message
     */
    void sendOwnObjectState(const RDB_MSG_t& RDBMessage);

    /**
     * @brief initVtdApi - initalaze VtdApi
     * @return true if API is initalized
     */
    bool initVtdApi(void);

    /**
     * @brief isConnected - return connection state
     * @return true if connected
     */
    bool isConnected(void);

    /**
     * @brief update - update routine
     */
    void update(void);

private:
    //VTD api
    VtdApi api_;
    //ConnectionHandle_ handles for incoming and outgoing RDB connections
    ConnectionHandle ConnectionHandle_;
    // Default player Ego Id
    unsigned int playerId_;

    RDB_OBJECT_STATE_t ownObjectState_;

    float steeringAngleRequest_;
    float throttlePedal_;
    float brakePedal_;
    float inputAccel_;
    float inputSteering_;
    float steeringRequest_;
    float accRequest_;
    int inputGear_;
};
#endif //  EXAMPLE_VEH_DYN_INTEQ_H
