#include "ExampleConsoleDriverCtrl.h"

#include <string>
#include <cstdio>
#include <cmath>

namespace
{
    // default player
    static const unsigned int EGO_ID = 1;

    // if message contains extended data structure
    static const bool OBJECT_STATE_EXTENDED = true;

    // 30 frames per second simulation
    static const double DELTA_TIME_30_FPS = 0.033;

    // default host
    const std::string DEFAULT_HOST = "127.0.0.1";
}

ExampleConsoleDriverCtrl::ExampleConsoleDriverCtrl()
    : handleIncomingOutgoing_(0)
    , playerId_(EGO_ID)
{

}

bool ExampleConsoleDriverCtrl::initVtdApi()
{
    // Handle for incoming data and outgoing data
    handleIncomingOutgoing_ =  api.connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::Protocols::RDB_TCP);

    // Register event if RDB has been connected
    if(handleIncomingOutgoing_)
    {
        api.registerEventFunc<ExampleConsoleDriverCtrl, ReceiveRDB>(this, &ExampleConsoleDriverCtrl::handleRdbMessage, handleIncomingOutgoing_);
        return true;
    }
    else
    {
        printf("ERROR: Could not establish connection\n");
        return false;
    }
}

void ExampleConsoleDriverCtrl::handleRdbMessage(const ReceiveRDB* msg)
{
    processObjectState(msg->getData(), OBJECT_STATE_EXTENDED);

}

void ExampleConsoleDriverCtrl::processObjectState(const RDB_MSG_t& RDBMessage, const bool& isExtended)
{
    unsigned int noElements = 0;

    RDB_OBJECT_STATE_t* objState = reinterpret_cast<RDB_OBJECT_STATE_t*>(Framework::RDBHandler::getFirstEntry(&RDBMessage, RDB_PKG_ID_OBJECT_STATE, noElements, isExtended));

    if(!noElements) return;

    while(noElements)
    {
        fprintf( stderr, "handleRDBitem: handling object state\n" );
        fprintf( stderr, "    simTime = %.3lf, simFrame = %d\n", RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo );
        fprintf( stderr, "    object = %s, id = %d\n", objState->base.name, objState->base.id );
        fprintf( stderr, "    position = %.3lf / %.3lf / %.3lf\n", objState->base.pos.x, objState->base.pos.y, objState->base.pos.z );

        if(isExtended)
            fprintf( stderr, "    speed = %.3lf / %.3lf / %.3lf\n", objState->ext.speed.x, objState->ext.speed.y, objState->ext.speed.z );

        ++objState;
        --noElements;

    }

     sendDriverCtrl(RDBMessage);
}

void ExampleConsoleDriverCtrl::sendDriverCtrl(const RDB_MSG_t& RDBMessage)
{
    Framework::RDBHandler myHandler;
    myHandler.initMsg();

    RDB_DRIVER_CTRL_t *myDriver = reinterpret_cast<RDB_DRIVER_CTRL_t*>(myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_DRIVER_CTRL));

    if(!myDriver)
      return;

    myDriver->playerId      = 1;
    myDriver->accelTgt      = boost::numeric_cast<float>( 2.0 * sin( 0.1 * RDBMessage.hdr.simTime ) );
    myDriver->validityFlags = RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL | RDB_DRIVER_INPUT_VALIDITY_ADD_ON;

    api.sendRdbMessage(handleIncomingOutgoing_, *myHandler.getMsg());
}
