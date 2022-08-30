#ifndef VEH_DYN_INTEQ_UDP_H
#define VEH_DYN_INTEQ_UDP_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>

/**
 * Class Communication Sample is an example how to use Vtd Api to controll vihacle
 */

using namespace VTD;

class VehDynInteqUDP
{
public:
    /**
    * constructor
    */
     VehDynInteqUDP();

     ~VehDynInteqUDP(){}

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
     * @return true when API is initalized
     */
    bool initVtdApi();

    // handleIncoming_ and handleOutgoing_ handles for incoming and outgoing RDB connection
    ConnectionHandle handleIncoming_, handleOutgoing_;

    //VTD api
    VtdApi api;

private:
    // Default player Id
    unsigned int playerId_;

    RDB_OBJECT_STATE_t OwnObjectState_;
    float mdSteeringAngleRequest_;
    float mdThrottlePedal_;
    float mdBrakePedal_;
    float mInputAccel_;
    float mInputSteering_;
    float mdSteeringRequest_;
    float mdAccRequest_;
    int   mInputGear_;

};

#endif //  VEH_DYN_INTEQ_UDP_H
