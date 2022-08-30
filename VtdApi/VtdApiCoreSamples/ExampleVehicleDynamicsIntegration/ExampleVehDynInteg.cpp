#include "ExampleVehDynInteg.h"

#include <string>
#include <cstdio>
#include <cmath>

namespace
{
	// default player
	const unsigned int EGO_ID = 1u;
	// if message contains extended data structure
	const bool OBJECT_STATE_EXTENDED = true;
	// if message not contains extended data structure
	const bool OBJECT_STATE_NOT_EXTENDED = false;
	// deafult player name
	const std::string DEFAULT_PLAYER_NAME = "Ego";
	// Steering ratio refers to the ratio between the turn of the steering wheel (in degrees) or handlebars and the turn of the wheels (in degrees).
	// In most passenger cars, the ratio is between 12:1 and 20:1.
	const float STEERING_RATIO = 19.0f;
    // default host local ip where VTD is running
    const std::string DEFAULT_HOST = "127.0.0.1";
}

ExampleVehDynInteg::ExampleVehDynInteg()
    : ConnectionHandle_(0)
    , playerId_(EGO_ID)
    , steeringAngleRequest_(0.0f)
    , throttlePedal_(0.0f)
    , brakePedal_(0.0f)
    , inputAccel_(0.0f)
    , inputSteering_(0.0f)
    , steeringRequest_(0.0f)
    , accRequest_(0.0f)
    , inputGear_(0)
{
    // initialize object state structure
    memset(&ownObjectState_, 0, sizeof(RDB_OBJECT_STATE_t));
}

bool ExampleVehDynInteg::initVtdApi()
{
    // Handle for incoming data and outgoing data
    ConnectionHandle_ =  api_.connectRDB (DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::Protocols::RDB_TCP);

    // Register event if RDB has been connected
    if(ConnectionHandle_)
    {
        api_.registerEventFunc<ExampleVehDynInteg, ReceiveRDB>(this, &ExampleVehDynInteg::handleRdbMessage, ConnectionHandle_);
        return true;
    }
    else
    {
        printf("ERROR: Could not establish connection\n");
        return false;
    }
}

bool ExampleVehDynInteg::isConnected()
{
    return api_.isConnected(ConnectionHandle_);
}

void ExampleVehDynInteg::update()
{
    api_.update();
}

void ExampleVehDynInteg::handleRdbMessage(const ReceiveRDB* msg)
{
    processObjectState(msg->getData(), OBJECT_STATE_EXTENDED);

    processDriverControl(msg->getData(), OBJECT_STATE_NOT_EXTENDED);
}

void ExampleVehDynInteg::processDriverControl(const RDB_MSG_t& RDBMessage, const bool& isExtended)
{
    unsigned int noElements = 0;

    RDB_DRIVER_CTRL_t* item = reinterpret_cast<RDB_DRIVER_CTRL_t*>(Framework::RDBHandler::getFirstEntry(&RDBMessage, RDB_PKG_ID_DRIVER_CTRL, noElements, isExtended));

    if (!noElements) return;

    static bool sShowMessage = false;
    static double sLastSimTime = -1.0;

    fprintf(stderr, "handleRDBitem: handling driver control for player %d\n", item->playerId);

    // is this message for me?
    if (item->playerId != playerId_) return;

    // check for valid inputs (only some may be valid)
    steeringAngleRequest_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_STEERING_WHEEL) ? item->steeringWheel / STEERING_RATIO : 0.0f;
    throttlePedal_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_THROTTLE) ? item->throttlePedal : 0.0f;
    brakePedal_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_BRAKE) ? item->brakePedal : 0.0f;
    inputAccel_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL) ? item->accelTgt : 0.0f;
    inputSteering_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_STEERING) ? item->steeringTgt : 0.0f;
    steeringRequest_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_STEERING) ? item->steeringTgt : 0.0f;
    accRequest_ = (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL) ? item->accelTgt : 0.0f;
    inputGear_ = 0;

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
            if (!sShowMessage) fprintf(stderr, "Invalid driver input for vehicle dynamics");

            sShowMessage = true;
        }
    }

    // use pedals/wheel or targets?
    bool mUseSteeringTarget = ((item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_STEERING) != 0);
    bool mUseAccelTarget = ((item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL) != 0);

    if (item->validityFlags & RDB_DRIVER_INPUT_VALIDITY_GEAR)
    {
        if (item->gear == RDB_GEAR_BOX_POS_R) inputGear_ = -1;
        else if (item->gear == RDB_GEAR_BOX_POS_N) inputGear_ = 0;
        else if (item->gear == RDB_GEAR_BOX_POS_D) inputGear_ = 1;
        else inputGear_ = 1;
    }

    // now, depending on the inputs, select the control mode and compute outputs
    if (mUseSteeringTarget && mUseAccelTarget)
    {
        fprintf(stderr, "Compute new vehicle position from acceleration target and steering target.\n");
        // call your user methods here to compute new vehicle position from acceleration target and steering target
    }
    else if (!mUseSteeringTarget && !mUseAccelTarget)
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
    if (useDummy && (sLastSimTime >= 0.0))
    {
        double speedX = 5.0; // m/s
        double speedY = 0.0; // m/s
        double speedZ = 0.0; // m/s
        double dt = RDBMessage.hdr.simTime - sLastSimTime;

        ownObjectState_.base.id = playerId_;
        ownObjectState_.base.category = RDB_OBJECT_CATEGORY_PLAYER;
        ownObjectState_.base.type = RDB_OBJECT_TYPE_PLAYER_CAR;
        strcpy(ownObjectState_.base.name, DEFAULT_PLAYER_NAME.c_str());

        // dimensions of own vehicle
        ownObjectState_.base.geo.dimX = 4.60f;
        ownObjectState_.base.geo.dimY = 1.86f;
        ownObjectState_.base.geo.dimZ = 1.60f;

        // offset between reference point and center of geometry
        ownObjectState_.base.geo.offX = 0.8f;
        ownObjectState_.base.geo.offY = 0.0f;
        ownObjectState_.base.geo.offZ = 0.3f;

        ownObjectState_.base.pos.x += dt * speedX;
        ownObjectState_.base.pos.y += dt * speedY;
        ownObjectState_.base.pos.z += dt * speedZ;
        ownObjectState_.base.pos.h = 0.0f;
        ownObjectState_.base.pos.p = 0.0f;
        ownObjectState_.base.pos.r = 0.0f;
        ownObjectState_.base.pos.flags = RDB_COORD_FLAG_POINT_VALID | RDB_COORD_FLAG_ANGLES_VALID;

        ownObjectState_.ext.speed.x = speedX;
        ownObjectState_.ext.speed.y = speedY;
        ownObjectState_.ext.speed.z = speedZ;
        ownObjectState_.ext.speed.h = 0.0f;
        ownObjectState_.ext.speed.p = 0.0f;
        ownObjectState_.ext.speed.r = 0.0f;
        ownObjectState_.ext.speed.flags = RDB_COORD_FLAG_POINT_VALID | RDB_COORD_FLAG_ANGLES_VALID;

        ownObjectState_.ext.accel.x = 0.0;
        ownObjectState_.ext.accel.y = 0.0;
        ownObjectState_.ext.accel.z = 0.0;
        ownObjectState_.ext.accel.flags = RDB_COORD_FLAG_POINT_VALID;

        ownObjectState_.base.visMask = RDB_OBJECT_VIS_FLAG_TRAFFIC | RDB_OBJECT_VIS_FLAG_RECORDER;

        // ok, I have a new object state, so let's send the data
        sendOwnObjectState(RDBMessage);
    }

    // remember last simulation time
    sLastSimTime = RDBMessage.hdr.simTime;
}

void ExampleVehDynInteg::sendOwnObjectState(const RDB_MSG_t& RDBMessage)
{
    Framework::RDBHandler myHandler;

    // start a new message
    myHandler.initMsg();

    // begin with an SOF identifier
    myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_START_OF_FRAME);

    // add extended package for the object state
    RDB_OBJECT_STATE_t*objState = reinterpret_cast<RDB_OBJECT_STATE_t*>(myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_OBJECT_STATE, 1, true));

    if (!objState)
    {
        fprintf(stderr, "sendOwnObjectState: could not create object state\n");
        return;
    }

    // copy contents of internally held object state to output structure
    memcpy(objState, &ownObjectState_, sizeof(RDB_OBJECT_STATE_t));
    //handle driver control input and compute vehicle dynamics output
    fprintf(stderr, "sendOwnObjectState: sending pos x/y/z = %.3lf/%.3lf/%.3lf,\n", objState->base.pos.x, objState->base.pos.y, objState->base.pos.z);
    // terminate with an EOF identifier
    myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_END_OF_FRAME);

    api_.sendRdbMessage(ConnectionHandle_, *myHandler.getMsg());
}

void ExampleVehDynInteg::processObjectState(const RDB_MSG_t& RDBMessage, const bool& isExtended)
{
    unsigned int noElements = 0;

    RDB_OBJECT_STATE_t* objState = reinterpret_cast<RDB_OBJECT_STATE_t*>(Framework::RDBHandler::getFirstEntry(&RDBMessage, RDB_PKG_ID_OBJECT_STATE, noElements, isExtended));

    if (!noElements) return;

    //handle driver control input and compute vehicle//handle driver control input and compute vehicle dynamics output dynamics output
    while (noElements)
    {
        fprintf(stderr, "handleRDBitem: handling object state\n");
        fprintf(stderr, "    simTime = %.3lf, simFrame = %d\n", RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo);
        fprintf(stderr, "    object = %s, id = %d\n", objState->base.name, objState->base.id);
        fprintf(stderr, "    position = %.3lf / %.3lf / %.3lf\n", objState->base.pos.x, objState->base.pos.y, objState->base.pos.z);
        if (isExtended) fprintf(stderr, "    speed = %.3lf / %.3lf / %.3lf\n", objState->ext.speed.x, objState->ext.speed.y, objState->ext.speed.z);

        objState++;
        noElements--;
    }
}

