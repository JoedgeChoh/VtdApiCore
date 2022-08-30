#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <VtdThreads/Thread.h>

#include <iostream>

using namespace VTD;

namespace
{
    // default host local ip where VTD is running
    const std::string DEFAULT_HOST = "127.0.0.1";
    // microseconds in second
    const unsigned int MICROSEC_IN_SEC = 1000000;
}

void SecDelay(float seconds)
{
    Thread::sleep( boost::numeric_cast<UInt64>( seconds * MICROSEC_IN_SEC ) );
}

/**
 * Basic sample showing use of VtdApi to control the simulation in different ways.
 */
int main(int argc, char** argv)
{
    std::string vtdDir = ".";
    if (argc > 1)
    {
        vtdDir = argv[1];
    }
    else
    {
        std::cout << "Usage: ExampleScpVtdControl <VTD_ROOT>" << std::endl;
        std::cout << "e.g.: ExampleScpVtdControl /home/dw/projects/VTD" << std::endl;
        exit(1);
    }

    std::string projectPath = vtdDir + "/Data/Projects/Current";
    std::string scenarioFilePath = vtdDir + "/Data/Projects/Current/Scenarios/Crossing8Demo.xml";

    VtdApi api;
    ConnectionHandle handle = api.connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    if (handle)
    {
        //ensure simulation is stopped and VTD is in configuration mode
        std::cout << "Stopping Simulation..." << std::endl;
        api.stopSimulation(false);
        if (api.getOperationStage() != OperationStage::CONFIG)
        {
            api.enterConfigurationStage(/*isBlocking*/ false);
            SecDelay(1.0);
        }

        std::cout << "Entering ready stage..." << std::endl;
        api.applyConfiguration();

        std::cout << "Loading project \"" << projectPath << "\" ..." << std::endl;
        api.changeProject("SampleProject", projectPath);

        std::cout << "Loading scenario \"" << scenarioFilePath << "\" ..." << std::endl;
        api.loadScenario(scenarioFilePath);

        std::cout << "Init simulation..." << std::endl;
        api.initSimulation();

        std::cout << "Start simulation..." << std::endl;
        api.startSimulation();

        std::cout << "Pause simulation..." << std::endl;
        api.pauseSimulation();

        std::cout << "Step simulation..." << std::endl;
        api.stepSimulation(100);

        std::cout << "Start simulation..." << std::endl;
        api.startSimulation();

        boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));

        std::cout << "Restart simulation..." << std::endl;
        api.restartSimulation();

        boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));

        std::cout << "Stop simulation..." << std::endl;
        api.stopSimulation();
    }
    else
    {
        std::cout << "SCP Connection Failed." << std::endl;
        std::cout << "Start VTD with Standard setup and sample project" << std::endl;
    }

    std::cout << "Exiting..." << std::endl;

    api.disconnectSCP(handle);
    return 0;
}
