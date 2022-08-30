#include <VtdApi/VtdApi.h>

#include "ExampleDriveControl.h"

using namespace VTD;

/**
 * Sample showing how to use VtdApi with RdbMessages, and simple ACC which brakes when an object has been detected
 */

int main()
{
    ExampleAcc exampleAcc;
    if(!exampleAcc.initVtdApi())
    {
        std::cout << "Start VTD with Standard setup and Sample project" << std::endl;
        std::cout << "Set sensor properties" << std::endl;
        std::cout << "Start simulation" << std::endl;
        exit(1);
    }

    VtdApi& api = exampleAcc.api;
    while (api.isConnected(exampleAcc.handleIncoming_) && api.isConnected(exampleAcc.handleOutgoing_))
    {
        api.update();
    }

    return 0;
}
