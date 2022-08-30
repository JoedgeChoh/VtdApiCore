#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <VtdCore/FileSystemIO.h>
#include <VtdThreads/Thread.h>

#include <iostream>
#include <stdlib.h>
#include <unistd.h>

/**
 * VTD remote control sample. Run three diff. setups with two scenarios
 */

using namespace VTD;

namespace
{
    // default host local ip where VTD is running
    const std::string DEFAULT_HOST = "127.0.0.1";
    // microseconds in second
    static const unsigned int MICROSEC_IN_SEC = 1000000;
}

// Vector of setups and scenario lists
typedef std::vector<std::string> ScenarioList;
typedef std::vector<std::string> Setups;

void SecDelay(float seconds)
{
    Thread::sleep( boost::numeric_cast<UInt64>( seconds * MICROSEC_IN_SEC ) );
}

void sendSCPCommand(VtdApi& api, const std::string& messageText)
{
    ScpBuilder sb;

    sb.beginScpCommand(ScpCommand::Symbol);
    sb.addScpAttribute("name", "expl01");

    sb.beginScpCommand(ScpCommand::Text);
    sb.addScpAttribute("data", messageText);
    sb.addScpAttribute("colorRGB", "0xffff00");
    sb.addScpAttribute("size", "50.0");
    sb.endScpCommand();

    sb.beginScpCommand(ScpCommand::PosScreen);
    sb.addScpAttribute("x","0.01"),
    sb.addScpAttribute("y","0.05");
    sb.endScpCommand();

    sb.endScpCommand();

    api.sendScpCommand(sb.asString());
}

void RunAndAutoEndScenario(VtdApi& api)
{
    // Start simulation
    api.stopSimulation();
    api.startSimulation();
    // Send Scp command
    sendSCPCommand(api,"Start test");
    SecDelay(1.0f);
    // Send SCP command
    sendSCPCommand(api,"End test");
    SecDelay(1.0f);
    // Stop simulation
    api.stopSimulation();
}

void InitScenario(VtdApi& api)
{
    // Init simulation
    std::cout << "Initializing scenario." << std::endl;
    api.initSimulation(VtdApi::OperationMode::OPERATION);
    SecDelay(1.0f);
    // Send Scp command
    api.sendScpCommand("<Info/>");
}

void RunScenarioFile(VtdApi& api, const std::string& scenarioFilename)
{
    // Stop stopping
    std::cout << "Stopping scenario " << scenarioFilename << std::endl;
    api.stopSimulation(/*isBlocking*/ false);
    // Load scenario
    std::cout << "Loading scenario " << scenarioFilename << std::endl;
    api.loadScenario(scenarioFilename);
    // Init scenario
    InitScenario(api);
    std::cout << "Starting scenario " << scenarioFilename << std::endl;
    // Run and end scenario
    RunAndAutoEndScenario(api);
    std::cout << "Scenario " << scenarioFilename << " terminated" << std::endl;
}

void RunScenarioList(VtdApi& api, const ScenarioList& list)
{
    // Run scenario list
    for (ScenarioList::const_iterator it = list.begin(); it != list.end(); ++it)
    {
        const std::string& scenarioFilename = *it;
        RunScenarioFile(api, scenarioFilename);
    }
}

int main(int argc, char** argv) {

    // Default Root, project name and setup name
    std::string vtdRoot = ".";
    std::string projectName = "SampleProject";

    // Read root from command line
    if (argc > 1)
    {
        vtdRoot = argv[1];
    }
    else
    {
        std::cout << "Usage: ExampleVtdRemoteControl <VTD_ROOT>" << std::endl;
        std::cout << "e.g.: ExampleVtdRemoteControl /home/dw/projects/VTD" << std::endl;
        exit(1);
    }

    // Stop VTD if it is still running
    std::cout << "Kill previous instance." << std::endl;
    Internal::FileSystemIO::turnOffVtd(vtdRoot);

    // Collect list of scenarios
    ScenarioList scenarioList;
    scenarioList.push_back("Crossing8Demo.xml");
    scenarioList.push_back("TrafficDemo.xml");

    // Collect list of setups
    Setups setupsList;
    setupsList.push_back("Standard");
    setupsList.push_back("Standard");
    setupsList.push_back("Standard");

    VtdApi api;
    ConnectionHandle handle = 0;


    for (Setups::iterator it = setupsList.begin(); it != setupsList.end(); ++it)
    {
        // Set setup name
        std::string setupName = *it;
        // Print out setup and project name
        std::cout << "Setup: " << setupName << "; Project: " << projectName << std::endl;
        // Start VTD
        Internal::FileSystemIO::turnOnVtd(vtdRoot, setupName, projectName);
        std::cout << "Load VTD Environment; for debug information see debug.txt." << std::endl;

        if(!handle)
            handle = api.connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);

        if (handle)
        {
            api.update();
            api.stopSimulation();

            // Wait until VTD is in ready stage (autoconfigure)
            while (api.getOperationStage() != OperationStage::READY)
            {
                api.update();
                Thread::sleep(1000000);
            }
            // Run scenario list
            RunScenarioList(api, scenarioList);
            std::cout << "All scenarios done." << std::endl;
        }
        else
        {
            std::cout << "SCP Connection Failed." << std::endl;
        }

        std::cout << "Stopping VTD." << std::endl;
        api.disconnectSCP(handle);
        handle = 0;

        // Stop VTD
        Internal::FileSystemIO::turnOffVtd(vtdRoot);
    }

    std::cout << "Exiting..." << std::endl;
    return 0;
}
