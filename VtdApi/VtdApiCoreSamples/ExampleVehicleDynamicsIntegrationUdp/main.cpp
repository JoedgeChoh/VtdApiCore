#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <VtdThreads/Thread.h>

#include "ExampleVehDynInteqUdp.h"

#include <iostream>
#include <unistd.h>

using namespace VTD;
/**
 * Sample showing how to use VtdApi with RdbMessages using UDP.
 */

int main()
{
    VehDynInteqUDP commSample;

    if(!commSample.initVtdApi())
    {
        std::cout << "Start VTD with Standard.UDP setup and Sample project" << std::endl;
        std::cout << "Set RDB connection to UDP instead of TCP" << std::endl;
        std::cout << "Start simmulation" << std::endl;
        exit(1);
    }

    VtdApi& api = commSample.api;

    while (commSample.handleIncoming_)
    {
        api.update();
    }

    return 0;
}

