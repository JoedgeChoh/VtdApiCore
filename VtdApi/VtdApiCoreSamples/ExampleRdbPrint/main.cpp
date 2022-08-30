#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <iostream>
#include <unistd.h>

#include "ExampleRdbPrint.h"

using namespace VTD;

/**
 * Sample showing how to use VtdApi with RdbMessages to print data to console and to trigger VTD.
 */
namespace
{
    static const bool SHOULD_SEND_TRIGGER = true;
    static const float DEFAULT_FRAME_TIME = 0.033f;
}

int main(int argc, char** argv)
{
    ExampleRdbPrint commSample(SHOULD_SEND_TRIGGER);

    if (!commSample.initVtdApi())
    {
        std::cout << "Start VTD with Standard setup and Sample project" << std::endl;
        std::cout << "Start simmulation" << std::endl;
        exit(1);
    }

    VtdApi& api = commSample.api_;

    while (api.isConnected(commSample.ConnectionHandle_))
    {
        api.update();
        if (SHOULD_SEND_TRIGGER)
            api.sendTriggerRDB(commSample.ConnectionHandle_, DEFAULT_FRAME_TIME, 0, 0);

    }

    return 0;
}
