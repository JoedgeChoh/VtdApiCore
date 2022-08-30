#include "ExampleVehDynInteqUdp.h"

#include <cstdio>
#include <string>
#include <cmath>

namespace
{
    // default player
    static const unsigned int EGO_ID = 1;

    // if message contains extended data structure
    static const bool OBJECT_STATE_EXTENDED = true;

    // if message not contains extended data structure
    static const bool OBJECT_STATE_NOT_EXTENDED = false;

    // deafult player name
    static const std::string DEFAULT_PLAYER_NAME = "Ego";

    // Steering ratio refers to the ratio between the turn of the steering wheel (in degrees) or handlebars and the turn of the wheels (in degrees).
    // In most passenger cars, the ratio is between 12:1 and 20:1.
    static const float STEERING_RATIO = 19.0f;
    // User should enter local broadcast adsress
    static const std::string BROADCAST_IP_ADDRESS = "192.168.101.255";
}

VehDynInteqUDP::VehDynInteqUDP()
    : handleIncoming_(0)
    , handleOutgoing_(0)
    , playerId_(EGO_ID)
{
}

bool VehDynInteqUDP::initVtdApi()
{
    // Handle for incomming data
    handleIncoming_ = api.connectRDB(BROADCAST_IP_ADDRESS, DEFAULT_UDP_RX_PORT, Protocols::RDB_UDP_RECEIVE_ONLY);
    // Handle for outgoing data
    handleOutgoing_ = api.connectRDB(BROADCAST_IP_ADDRESS, DEFAULT_UDP_TX_PORT, Protocols::RDB_UDP_SEND_ONLY);
    if(handleIncoming_)
    {
        api.registerEventFunc<VehDynInteqUDP, ReceiveRDB>(this, &VehDynInteqUDP::handleRdbMessage, handleIncoming_);
        printf("VtdApi: Initalized \n");
        return true;
    }
    else
    {
        return false;
    }
}

void VehDynInteqUDP::handleRdbMessage(const ReceiveRDB* msg)
{
     processObjectState(msg->getData(), OBJECT_STATE_EXTENDED);

     processDriverControl(msg->getData(), OBJECT_STATE_NOT_EXTENDED);
}

void VehDynInteqUDP::processDriverControl(const RDB_MSG_t& RDBMessage, const bool& isExtended)
{
    unsigned int noElements = 0;

    RDB_DRIVER_CTRL_t* item = reinterpret_cast<RDB_DRIVER_CTRL_t*>(Framework::RDBHandler::getFirstEntry(&RDBMessage, RDB_PKG_ID_DRIVER_CTRL, noElements, isExtended));

    if(!noElements) return;

    static bool sShowMessage = false;
    static double sLastSimTime = -1.0;

    fprintf( stderr, "handleRDBitem: handling driver control for player %d\n", item->playerId);

     // is this message for me?
    if (item->playerId != playerId_) return;

     // check for valid inputs (only some may be valid)
     mdSteeringAngleRequest_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_STEERING_WHEEL) ? item->steeringWheel / STEERING_RATIO : 0.0f;
     mdThrottlePedal_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_THROTTLE) ? item->throttlePedal : 0.0f;
     mdBrakePedal_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_BRAKE) ? item->brakePedal : 0.0f;
     mInputAccel_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL) ? item->accelTgt : 0.0f;
     mInputSteering_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_STEERING) ? item->steeringTgt : 0.0f;
     mdSteeringRequest_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_STEERING) ? item->steeringTgt : 0.0f;
     mdAccRequest_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL) ? item->accelTgt : 0.0f;
     mInputGear_ = 0;

     // check the input validity
     unsigned int validFlagsLat = RDB_DRIVER_INPUT_VALIDITY_TGT_STEERING | RDB_DRIVER_INPUT_VALIDITY_STEERING_WHEEL;
     unsigned int validFlagsLong = RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL | RDB_DRIVER_INPUT_VALIDITY_THROTTLE | RDB_DRIVER_INPUT_VALIDITY_BRAKE;
     unsigned int checkFlags = item->validityFlags & 0x00000fff;

     if (checkFlags)
     {
         if ((checkFlags & validFlagsLat) && (checkFlags & validFlagsLong))
         {
             sShowMessage = false;
         }
         else if (checkFlags != RDB_DRIVER_INPUT_VALIDITY_GEAR) // "gear only" is also fine
         {
             if (!sShowMessage)
                 fprintf( stderr, "Invalid driver input for vehicle dynamics" );

             sShowMessage = true;
         }
     }

     // use pedals/wheel or targets?
     bool mUseSteeringTarget = ((item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_STEERING) != 0);
     bool mUseAccelTarget = ((item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL) != 0);

    if(item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_GEAR)
    {
         if  (item->gear == RDB_GEAR_BOX_POS_R)
             mInputGear_ = -1;
         else if (item->gear == RDB_GEAR_BOX_POS_N)
             mInputGear_ = 0;
         else if (item->gear == RDB_GEAR_BOX_POS_D)
             mInputGear_ = 1;
         else
             mInputGear_ = 1;
    }

    // now, depending on the inputs, select the control mode and compute outputs
    if(mUseSteeringTarget && mUseAccelTarget)
    {
        fprintf(stderr, "Compute new vehicle position from acceleration target and steering target.\n");
        // call your user methods here to compute new vehicle position from acceleration target and steering target
    }
    else if(!mUseSteeringTarget && !mUseAccelTarget)
    {
        fprintf(stderr, "Compute new vehicle position from brake pedal, throttle pedal and steering wheel angle.\n");
        // call your user methods here compute new vehicle position from brake pedal, throttle pedal and steering wheel angle
    }
    else
    {
        fprintf(stderr, "Compute new vehicle position from a mix of targets and pedals / steering wheel angle.\n");
        // call your user methods here to compute new vehicle position from a mix of targets and pedals
    }

    bool useDummy = true;

    // the following assignments are for dummy purposes only
    // vehicle moves along x-axis with given speed
    // ignore first message
    if(useDummy && (sLastSimTime >= 0.0))
    {
          double speedX = 5.0;    // m/s
          double speedY = 0.0;    // m/s
          double speedZ = 0.0;    // m/s
          double dt = RDBMessage.hdr.simTime - sLastSimTime;

          OwnObjectState_.base.id = playerId_;
          OwnObjectState_.base.category = RDB_OBJECT_CATEGORY_PLAYER;
          OwnObjectState_.base.type = RDB_OBJECT_TYPE_PLAYER_CAR;
          strcpy(OwnObjectState_.base.name, DEFAULT_PLAYER_NAME.c_str());

          // dimensions of own vehicle
          OwnObjectState_.base.geo.dimX = 4.60f;
          OwnObjectState_.base.geo.dimY = 1.86f;
          OwnObjectState_.base.geo.dimZ = 1.60f;

          // offset between reference point and center of geometry
          OwnObjectState_.base.geo.offX = 0.8f;
          OwnObjectState_.base.geo.offY = 0.0f;
          OwnObjectState_.base.geo.offZ = 0.3f;

          OwnObjectState_.base.pos.x += dt * speedX;
          OwnObjectState_.base.pos.y += dt * speedY;
          OwnObjectState_.base.pos.z += dt * speedZ;
          OwnObjectState_.base.pos.h = 0.0f;
          OwnObjectState_.base.pos.p = 0.0f;
          OwnObjectState_.base.pos.r = 0.0f;
          OwnObjectState_.base.pos.flags = RDB_COORD_FLAG_POINT_VALID | RDB_COORD_FLAG_ANGLES_VALID;

          OwnObjectState_.ext.speed.x = speedX;
          OwnObjectState_.ext.speed.y = speedY;
          OwnObjectState_.ext.speed.z = speedZ;
          OwnObjectState_.ext.speed.h = 0.0f;
          OwnObjectState_.ext.speed.p = 0.0f;
          OwnObjectState_.ext.speed.r = 0.0f;
          OwnObjectState_.ext.speed.flags = RDB_COORD_FLAG_POINT_VALID | RDB_COORD_FLAG_ANGLES_VALID;

          OwnObjectState_.ext.accel.x = 0.0;
          OwnObjectState_.ext.accel.y = 0.0;
          OwnObjectState_.ext.accel.z = 0.0;
          OwnObjectState_.ext.accel.flags = RDB_COORD_FLAG_POINT_VALID;

          OwnObjectState_.base.visMask = RDB_OBJECT_VIS_FLAG_TRAFFIC | RDB_OBJECT_VIS_FLAG_RECORDER;
    }

    // ok, I have a new object state, so let's send the data
    sendOwnObjectState (RDBMessage);

    // remember last simulation time
    sLastSimTime = RDBMessage.hdr.simTime;
}

void VehDynInteqUDP::sendOwnObjectState(const RDB_MSG_t& RDBMessage)
{
    Framework::RDBHandler myHandler;

    // start a new message
    myHandler.initMsg();

    // begin with an SOF identifier
    myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_START_OF_FRAME);

    // add extended package for the object state
    RDB_OBJECT_STATE_t *objState = reinterpret_cast<RDB_OBJECT_STATE_t*>(myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_OBJECT_STATE, 1, true));

    if (!objState)
    {
        fprintf(stderr, "sendOwnObjectState: could not create object state\n");
        return;
    }

    // copy contents of internally held object state to output structure
    memcpy(objState, &OwnObjectState_, sizeof( RDB_OBJECT_STATE_t ));
    fprintf(stderr, "sendOwnObjectState: sending pos x/y/z = %.3lf/%.3lf/%.3lf,\n", objState->base.pos.x, objState->base.pos.y, objState->base.pos.z);

    // terminate with an EOF identifier
    myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_END_OF_FRAME);

    api.sendRdbMessage(handleOutgoing_, *myHandler.getMsg());
}

void VehDynInteqUDP::processObjectState(const RDB_MSG_t& RDBMessage, const bool& isExtended)
{
    // number of elelments
    unsigned int noElements = 0;

    RDB_OBJECT_STATE_t* objState = reinterpret_cast<RDB_OBJECT_STATE_t*>(Framework::RDBHandler::getFirstEntry(&RDBMessage, RDB_PKG_ID_OBJECT_STATE, noElements, isExtended));

    // if there is no elements return
    if (!noElements) return;

    while (noElements)
    {
        fprintf(stderr, "handleRDBitem: handling object state\n");
        fprintf(stderr, "    simTime = %.3lf, simFrame = %d\n", RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo);
        fprintf(stderr, "    object = %s, id = %d\n", objState->base.name, objState->base.id);
        fprintf(stderr, "    position = %.3lf / %.3lf / %.3lf\n", objState->base.pos.x, objState->base.pos.y, objState->base.pos.z);

        if (isExtended)
            fprintf(stderr, "    speed = %.3lf / %.3lf / %.3lf\n", objState->ext.speed.x, objState->ext.speed.y, objState->ext.speed.z);

        ++objState;
        --noElements;
    }
}


