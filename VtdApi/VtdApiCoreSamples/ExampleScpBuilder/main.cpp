#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <VtdThreads/Thread.h>

#include <iostream>
#include <unistd.h>

using namespace VTD;

namespace
{
    // default host local ip where VTD is running
    const std::string DEFAULT_HOST = "127.0.0.1";
}
/**
 * Sample showing the use of ScpBuilder to send custom ScpMessages.
 */

int main(int argc, char** argv) {

    bool isBlocking = true;
    std::string vtdDir = ".";

    if(argc > 1)
    {
        vtdDir = argv[1];
    }
    else
    {
        std::cout << "Usage: ExampleScpBuilder <VTD_ROOT>" << std::endl;
        std::cout << "e.g.: ExampleScpBuilder /home/dw/projects/VTD" << std::endl;
        exit(1);
    }

    std::string projectPath = vtdDir + "/Data/Projects/Current";
    std::string scenarioFilePath = vtdDir + "/Data/Projects/Current/Scenarios/Crossing8Demo.xml";

    VtdApi api;

    ConnectionHandle handle = api.connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);

    if(handle)
    {
        //ensure simulation is stopped and VTD is in configuration mode
        std::cout << "Stopping Simulation..." << std::endl;
        api.stopSimulation(false);

        std::cout << "Entering Configuration Stage..." << std::endl;

        if(api.getOperationStage() != OperationStage::CONFIG)
        {
            api.enterConfigurationStage(true);
            Thread::sleep(1000000);
        }

        std::cout << "Entering ready stage..." << std::endl;
        api.applyConfiguration(/*startByScript*/ false, isBlocking);

        std::cout << "Loading project \"" << projectPath << "\" ..." << std::endl;
        api.changeProject("SampleProject", projectPath);

        std::cout << "Loading scenario \"" << scenarioFilePath << "\" ..." << std::endl;
        api.loadScenario(scenarioFilePath);

        std::cout << "Init simulation..." << std::endl;
        api.initSimulation(VtdApi::OperationMode::UNSET, isBlocking);

        std::cout << "Start simulation..." << std::endl;
        api.startSimulation(VtdApi::OperationMode::UNSET, /*maxDuration*/ -1.0f, isBlocking);

        std::cout << "Pause simulation..." << std::endl;
        api.pauseSimulation();

        // Build Set tag
        ScpBuilder sb;
        sb.beginScpCommand(ScpCommand::Set); // TODO [BB] create set root command in shared method
        sb.addScpAttribute("entity", VtdApi::SetEntity::toString(VtdApi::SetEntity::PLAYER));
        sb.addScpAttribute("name", "Ego");
            // Build Speed tag
            sb.beginScpCommand(ScpCommand::Speed);
            sb.addScpAttribute("value", 100);
            sb.endScpCommand();
        sb.endScpCommand();

        api.sendScpCommand(sb.asString());

        //Alteratively one can also create the string oneself or load it from a file, e.g.:
        //api.sendScpCommand("<Set entity=\"player\" name=\"Ego\"><Speed value=\"100\"/></Set>");

        std::cout << "Start simulation..." << std::endl;
        api.startSimulation(IVtdApi::OperationMode::UNSET, /*duration*/ -1.0f, isBlocking);

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
