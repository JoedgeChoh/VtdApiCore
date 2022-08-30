#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>

#include "ExampleDriveControlAdvanced.h"

#include <iostream>
#include <unistd.h>

using namespace VTD;

/**
 * Sample showing how to use VtdApi with RdbMessages.
 */

int main(int argc, char** argv)
{
    ExampleConsoleSensorAndDriverCtrl commSample;

    if(!commSample.initVtdApi())
    {
        std::cout << "Start VTD with Standard setup and Sample project" << std::endl;
        std::cout << "Set sensor properties" << std::endl;
        std::cout << "Start simmulation" << std::endl;
        exit(1);
    }

    VtdApi& api = commSample.api;

     while (api.isConnected(commSample.handleIncoming_)
            && api.isConnected(commSample.handleOutgoing_))
    {
        api.update();
    }

    return 0;
}

