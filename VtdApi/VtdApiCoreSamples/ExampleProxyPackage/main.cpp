#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>

#include "ExampleConsoleProxyPkg.h"

#include <iostream>
#include <unistd.h>

using namespace VTD;

/**
 * Class Example Console Proxy Pkg is an example how to use VtdApi to get proxy state
 */

int main()
{
    ExampleConsoleProxyPkg commSample;

    if(!commSample.initVtdApi())
    {
        std::cout << "Start VTD with Standard setup and Sample project" << std::endl;
        std::cout << "Start simmulation" << std::endl;
        exit(1);
    }

    VtdApi& api = commSample.api;

    while (api.isConnected(commSample.handleIncomingOutgoing_))
    {
        api.update();
    }

    return 0;
}
