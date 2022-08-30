#include "ExampleRdbPrint.h"

#include <string>
#include <cmath>
#include <cstdio>

namespace
{
    // default host local ip where VTD is running
    const std::string DEFAULT_HOST = "127.0.0.1";
    // default player
    static const unsigned int EGO_ID = 1;

    // if message contains extended data structure
    static const bool OBJECT_STATE_EXTENDED = true;

    // 30 frames per second simulation
    static const double DELTA_TIME_30_FPS = 0.033;
} // namespace

ExampleRdbPrint::ExampleRdbPrint(bool shouldSendTrigger)
    : ConnectionHandle_(0)
    , playerId_(EGO_ID)
    , shouldSendTrigger_(shouldSendTrigger)
{
}

bool ExampleRdbPrint::initVtdApi()
{
    // Handle for incoming data and outgoing data
    ConnectionHandle_ = api_.connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP);

    // Register event if RDB has been connected
    if (ConnectionHandle_)
    {
        api_.registerEventFunc<ExampleRdbPrint, ReceiveRDB>(this, &ExampleRdbPrint::handleRdbMessage, ConnectionHandle_);
        return true;
    }
    else
    {
        printf("ERROR: Could not establish connection\n");
        return false;
    }
}

void ExampleRdbPrint::handleRdbMessage(const ReceiveRDB* msg)
{
    processObjectState(msg->getData(), OBJECT_STATE_EXTENDED);
}

void ExampleRdbPrint::processObjectState(const RDB_MSG_t& RDBMessage, const bool& isExtended)
{
    unsigned int noElements = 0;

    RDB_OBJECT_STATE_t* objState = reinterpret_cast<RDB_OBJECT_STATE_t*>(Framework::RDBHandler::getFirstEntry(&RDBMessage, RDB_PKG_ID_OBJECT_STATE, noElements, isExtended));

    if (!noElements) return;

    while (noElements)
    {
        if (RDBMessage.hdr.frameNo == 0)
        {
            ++objState;
            --noElements;
            continue;
        }

        fprintf(stderr, "handleRDBitem: handling object state\n");
        fprintf(stderr, "    simTime = %.3lf, simFrame = %d\n", RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo);
        fprintf(stderr, "    object = %s, id = %d\n", objState->base.name, objState->base.id);
        fprintf(stderr, "    position = %.3lf / %.3lf / %.3lf\n", objState->base.pos.x, objState->base.pos.y, objState->base.pos.z);
        if (isExtended) fprintf(stderr, "    speed = %.3lf / %.3lf / %.3lf\n", objState->ext.speed.x, objState->ext.speed.y, objState->ext.speed.z);

        ++objState;
        --noElements;
    }
}

