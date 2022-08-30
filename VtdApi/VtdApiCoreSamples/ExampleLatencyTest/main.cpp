#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>

#include "LatencyTest.h"

#include <iostream>
#include <unistd.h>

using namespace VTD;

/**
 * ExamplevehDynInteq is an example showing how to use VtdApi to control vehicle dynamics
 */

int main()
{
    LatencyTest sample;

    if (!sample.initVtdApi())
    {
        std::cout << "Start VTD with Standard setup and Sample project" << std::endl;
        std::cout << "Start simmulation" << std::endl;
        exit(1);
    }

    while (sample.isConnected())
    {
        sample.update();
    }

    return 0;
}

