#include "ExampleDriveControl.h"

#include <string>
#include <cmath>
#include <cstdio>

namespace
{
    // default sensor port
    static const unsigned int SENSOR_PORT = 48185;
    // default player
    static const unsigned int EGO_ID = 1;
    // const to convert m/s to k/h
    static const double METERS_SEC_KILOMETERS_HOUR = 3.6;
    // if message contains extended data structure
    static const bool OBJECT_STATE_EXTENDED = true;
    // acceleration target speed
    static const double ACCELERATION_TARGET_SPEED = -2.5;
    // default host
    const std::string DEFAULT_HOST = "127.0.0.1";
}

ExampleAcc::ExampleAcc()
    : handleIncoming_(0)
    , handleOutgoing_(0)
    , playerId_(EGO_ID)
{

}

bool ExampleAcc::initVtdApi()
{
    // Handle for incomming data
    handleIncoming_ = api.connectRDB(DEFAULT_HOST, SENSOR_PORT, Protocols::RDB_TCP);
    // Handle for outcomming data
    handleOutgoing_ = api.connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::Protocols::RDB_TCP);
    // Register event if RDB has been connected
    if( handleOutgoing_ && handleIncoming_)
    {
        api.registerEventFunc<ExampleAcc, ReceiveRDB>(this, &ExampleAcc::handleRdbMessage, handleIncoming_);
        printf("VtdApi: Initalized \n");
        return true;
    }
    else
    {
        return false;
    }
}

void ExampleAcc::handleRdbMessage(const ReceiveRDB* msg)
{
    // process sensor data
    proccesSensorObject(msg->getData());
    // procces object state
    processObjectState(msg->getData(), OBJECT_STATE_EXTENDED);
}

void ExampleAcc::processObjectState(const RDB_MSG_t& RDBMessage, const bool& isExtended)
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
        if (objState->base.id == playerId_)
            sendDriverCtrl(RDBMessage);

        if (isExtended)
            fprintf(stderr, "    speed = %.3lf / %.3lf / %.3lf\n", objState->ext.speed.x, objState->ext.speed.y, objState->ext.speed.z);

        --noElements;
        ++objState;

    }
}

void ExampleAcc::proccesSensorObject(const RDB_MSG_t& RDBMessage)
{
    unsigned int noElements = 0;
    nearestObjectDetectedId_ = 0;
    distanceToNearestObject_ = 5000.0;
    RDB_SENSOR_OBJECT_t* sensorObject = reinterpret_cast<RDB_SENSOR_OBJECT_t*>(Framework::RDBHandler::getFirstEntry(&RDBMessage, RDB_PKG_ID_SENSOR_OBJECT, noElements, false));
    if (noElements == 0) return;

    while (noElements)
    {
        // Check if detected object is nearest to sensor
        if (distanceToNearestObject_ > sensorObject->dist)
        {
            distanceToNearestObject_ = sensorObject->dist;
            nearestObjectDetectedId_ = sensorObject->id;
            fprintf(stderr, "    Nearest object Id = %d, distance %.3lf\n", sensorObject->id, sensorObject->dist);
        }

        --noElements;
        ++sensorObject;
    }
}

void ExampleAcc::sendDriverCtrl(const RDB_MSG_t& RDBMessage)
{
    Framework::RDBHandler myHandler;
    myHandler.initMsg();
    RDB_DRIVER_CTRL_t *myDriver = reinterpret_cast<RDB_DRIVER_CTRL_t*>(myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_DRIVER_CTRL));

    if (!myDriver) return;
    // do we have a valid nearest object?
    if (nearestObjectDetectedId_ > 0)
    {
        myDriver->playerId = 1;
        myDriver->accelTgt = ACCELERATION_TARGET_SPEED;
        myDriver->validityFlags = RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL | RDB_DRIVER_INPUT_VALIDITY_ADD_ON;

        api.sendRdbMessage(handleOutgoing_, *myHandler.getMsg());
    }
}
