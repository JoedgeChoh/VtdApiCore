#include "ExampleDirectMode.h"

#include <string>
#include <cmath>
#include <cstdio>

namespace
{
    // default host local ip where VTD is running
    const std::string DEFAULT_HOST = "127.0.0.1";

    // if message contains extended data structure
    static const bool OBJECT_STATE_EXTENDED = true;

    // activate directMode of callbacks, no more buffering of callbacks
    static const bool DIRECT_MODE_BUFFERLESS_CALLBACK = true;
} // namespace

ExampleDirectMode::ExampleDirectMode()
    : connectionHandleRdb_(0), connectionHandleScp_(0)
{
}

bool ExampleDirectMode::initVtdApi()
{
    // RDB Handle for incoming data and outgoing data, use directMode for bufferless callback
    connectionHandleRdb_ = api_.connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP, DIRECT_MODE_BUFFERLESS_CALLBACK);

    // Register event if RDB has been connected
    if (connectionHandleRdb_)
    {
        api_.registerEventFunc<ExampleDirectMode, ReceiveRDB>(this, &ExampleDirectMode::handleRdbMessage, connectionHandleRdb_);
    }
    else
    {
        printf("ERROR: Could not establish RDB connection\n");
        return false;
    }

    // SCP Handle for incoming data and outgoing data, use directMode for bufferless callback
    connectionHandleScp_ =  api_.connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT, DIRECT_MODE_BUFFERLESS_CALLBACK);

    // Register event if SCP has been connected
    if (connectionHandleScp_)
    {
        api_.registerEventFunc<ExampleDirectMode, ReceiveSCP>(this, &ExampleDirectMode::handleScpMessage, connectionHandleScp_);

        boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
    }
    else
    {
        printf("ERROR: Could not establish SCP connection\n");
        return false;
    }

    return true;
}

void ExampleDirectMode::handleRdbMessage(const ReceiveRDB* msg)
{
    processObjectState(msg->getData(), OBJECT_STATE_EXTENDED);
}

void ExampleDirectMode::handleScpMessage(const ReceiveSCP* msg)
{
    // due to compiler optimizations in release builds the header has to be copied
    const SCP_MSG_HDR_t msgHdr = *(reinterpret_cast<const SCP_MSG_HDR_t*>(msg->getHeaderData().data()));

    std::cout << '\n' << "##################### SCP #####################" << '\n'
              << "  sender : " << msgHdr.sender << "  receiver: " << msgHdr.receiver << '\n'
              << "  command: " << msg->getDataString() << '\n'
              << "###############################################" << std::endl;
}


void ExampleDirectMode::processObjectState(const RDB_MSG_t& RDBMessage, const bool& isExtended)
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

        std::cout << '\n' << "##################### RDB #####################" << '\n'
                  << "  simTime : " << RDBMessage.hdr.simTime << "  simFrame: " << RDBMessage.hdr.frameNo << '\n'
                  << "  object  : " << objState->base.name << "  id: " << objState->base.id << '\n'
                  << "  position: " << objState->base.pos.x << "/" << objState->base.pos.y << "/" << objState->base.pos.z << '\n';

        if (isExtended)
        {
            std::cout << "  speed   : " << objState->ext.speed.x << "/" << objState->ext.speed.y << "/" << objState->ext.speed.z << std::endl;
        }
        std::cout      << "###############################################" << std::endl;

        ++objState;
        --noElements;
    }
}

