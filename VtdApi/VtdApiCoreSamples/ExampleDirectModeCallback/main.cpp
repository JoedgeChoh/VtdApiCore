#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <iostream>
#include <unistd.h>

#include "ExampleDirectMode.h"

using namespace VTD;

/**
 * Sample showing how to use VtdApi with direct mode to suppress buffering of callbacks.
 */
int main(int argc, char** argv)
{
    ExampleDirectMode commSample;

    if (!commSample.initVtdApi())
    {
        std::cout << "Start VTD with Standard setup and Sample project" << std::endl;
        std::cout << "Start simmulation" << std::endl;
        exit(1);
    }

    VtdApi& api = commSample.api_;

    while (true)
    {
        // call of api update is not needed if direct mode for bufferless callbacks is enabled
//        api.update();

        // check connection state for RDB and SCP handles
        if (!api.isConnected(commSample.connectionHandleRdb_) || !api.isConnected(commSample.connectionHandleScp_))
        {
            break;
        }

        // sleep to reduce computing power
        boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
    }
    return 0;
}
