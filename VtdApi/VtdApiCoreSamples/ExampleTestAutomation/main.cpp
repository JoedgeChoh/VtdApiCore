#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <VtdCore/FileSystemIO.h>
#include <VtdThreads/Thread.h>

#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace VTD;

typedef std::vector<std::string> ScenarioList;

namespace
{
    // default host local ip where VTD is running
    const std::string DEFAULT_HOST = "127.0.0.1";
    // microseconds in second
    static const unsigned int MICROSEC_IN_SEC = 1000000;
}

void SecDelay(float seconds)
{
    Thread::sleep( boost::numeric_cast<UInt64>( seconds * MICROSEC_IN_SEC ) );
}

void RunScenarioFile(VtdApi& api, const std::string& scenarioFilename)
{
    if(api.getOperationStage() == OperationStage::CONFIG)
    {
        api.applyConfiguration(/*startByScript*/ false, /*isBlocking*/ true);
    }
    api.stopSimulation(/*isBlocking*/ false);
    api.loadScenario(scenarioFilename);
    api.initSimulation(VtdApi::OperationMode::OPERATION);
    api.startSimulation();
    SecDelay(5.0f);
    api.sendScpCommand("<Symbol name=\"expl01\" > <Text data=\"End of Test\" colorRGB=\"0xffff00\" size=\"50.0\" /> <PosScreen x=\"0.01\" y=\"0.05\" /></Symbol>");
    SecDelay(1.0f);
    api.stopSimulation();
}

void RunScenarioList(VtdApi& api, const ScenarioList& list)
{
    for (ScenarioList::const_iterator it = list.begin(); it != list.end(); ++it)
    {
        const std::string& scenarioName = *it;
        std::cout << "Starting scenario " <<  scenarioName << std::endl;
        RunScenarioFile(api, scenarioName);
        std::cout << "Scenario " << scenarioName << "terminated." << std::endl;
    }

}

void DefineScenario(VtdApi& api)
{
    std::cout << "Defining scenario." << std::endl;

    if(api.getOperationStage() != OperationStage::CONFIG)
    {
        api.applyConfiguration(/*startByScript*/ false, /*isBlocking*/ true);
    }

    if(api.getOperationStage() != OperationStage::READY)
    {
        api.stopSimulation(/*isBlocking*/ true);
    }

    static const std::string scenarioDefinition =
    "<SimCtrl> <LoadScenario> \
        <Scenario RevMajor=\"2\" RevMinor=\"0\"> \
            <Layout Database=\"Projects/Current/Databases/TestAuto/straight45deg.opt.osgb\" File=\"Projects/Current/Databases/TestAuto/straight45deg.xodr\"/> \
            <VehicleList ConfigFile=\"Distros/Current/Config/Players/Vehicles\"/> \
            <DriverList ConfigFile=\"Distros/Current/Config/Players/driverCfg.xml\"/> \
            <CharacterList ConfigFile=\"Distros/Current/Config/Players/characterCfg.xml\"/> \
            <ObjectList ConfigFile=\"Distros/Current/Config/Players/Objects\"/> \
            <DynObjects Path=\"Distros/Current/Config/DynObjects/Logic\"/> \
            <TrafficElements> \
                <LaneChangeDef Name=\"Slow\" Time=\"1.2000000000000000e+01\"/> \
                <LaneChangeDef Name=\"Standard\" Time=\"8.0000000000000000e+00\"/> \
                <LaneChangeDef Name=\"Fast\" Time=\"4.0000000000000000e+00\"/> \
            </TrafficElements> \
            <PulkTraffic/> \
            <TrafficControl> \
                <Player> \
                    <Description Driver=\"DefaultDriver\" Control=\"external\" AdaptDriverToVehicleType=\"false\" Type=\"Audi_A6_2007_blue\" Name=\"Ego\"/> \
                    <Init> \
                        <Speed Value=\"0.0000000000000000e+00\"/> \
                        <PosAbsolute X=\"0.0000000000000000e+00\" Y=\"0.0000000000000000e+00\" Z=\"0.0000000000000000e+00\" Direction=\"0.7\" AlignToRoad=\"false\"/> \
                    </Init> \
                </Player> \
                <Player> \
                    <Description Driver=\"DefaultDriver\" Control=\"internal\" AdaptDriverToVehicleType=\"false\" Type=\"Audi_A6_2007_blue\" Name=\"Other1\"/> \
                    <Init> \
                        <Speed Value=\"0.0000000000000000e+00\"/> \
                        <PosAbsolute X=\"0.0000000000000000e+00\" Y=\"0.0000000000000000e+00\" Z=\"0.0000000000000000e+00\" Direction=\"3.9269908169800001e+00\" AlignToRoad=\"false\"/> \
                    </Init> \
                </Player> \
                <Player> \
                    <Description Driver=\"DefaultDriver\" Control=\"internal\" AdaptDriverToVehicleType=\"false\" Type=\"Audi_A6_2007_red\" Name=\"Other2\"/> \
                    <Init> \
                        <Speed Value=\"0.0000000000000000e+00\"/> \
                        <PosAbsolute X=\"0.0000000000000000e+00\" Y=\"0.0000000000000000e+00\" Z=\"0.0000000000000000e+00\" Direction=\"3.9269908169800001e+00\" AlignToRoad=\"false\"/> \
                    </Init> \
                </Player> \
                <PlayerActions Player=\"Ego\"/> \
                <PlayerActions Player=\"Other1\"/> \
                <PlayerActions Player=\"Other2\"/> \
            </TrafficControl> \
            <MovingObjectsControl/> \
            <Selections/> \
        </Scenario> \
    </LoadScenario> </SimCtrl>";

    api.sendScpCommand(scenarioDefinition);
}

void InitScenario(VtdApi& api)
{
    std::cout << "Initializing scenario." << std::endl;

    api.initSimulation(VtdApi::OperationMode::OPERATION);
    SecDelay(1.0f);
    api.sendScpCommand("<Info/>");
}

void SetPlayerPositions(VtdApi& api)
{
    std::cout << "Setting player positions." << std::endl;

    static const std::string scp =
            "<Set entity=\"player\" name=\"Other1\"> \
                <PosInertial x=\"1.1800000000000000e+01\" y=\"1.0000000000000000e+01\" hDeg=\"45.0\" pDeg=\"0.0\" rDeg=\"0.0\"/>\
                <Speed value=\"10.0\"/></Set> <Set entity=\"player\" name=\"Other2\"> \
                <PosInertial x=\"2.1800000000000000e+01\" y=\"2.0000000000000000e+01\" hDeg=\"45.0\" pDeg=\"0.0\" rDeg=\"0.0\"/> \
                <Speed value=\"20.0\"/>\
            </Set>";
    api.sendScpCommand(scp);
}

void StartAndAutoEndScenario(VtdApi& api)
{
    std::string scenarioName = "<unknown>";
    std::cout << "Starting Scenario: " << scenarioName << std::endl; //GK TODO get scenario name
    api.startSimulation();
    SecDelay(5.0f);
    api.sendScpCommand("<Symbol name=\"expl01\" > <Text data=\"End of Test\" colorRGB=\"0xffff00\" size=\"50.0\" /> <PosScreen x=\"0.01\" y=\"0.05\" /></Symbol>");
    SecDelay(1.0f);
    api.stopSimulation();
}

void StopScenario(VtdApi& api)
{
    std::cout << "Stopping Scenario." << std::endl;
    api.stopSimulation();
}

void StartAndTriggerScenario(VtdApi& api)
{
    std::string scenarioName = "<unknown>";
    std::cout << "Starting Scenario " << scenarioName << std::endl; //GK TODO get scenario name

    api.startSimulation(IVtdApi::OperationMode::UNSET, /*maxDuration*/ -1.0f, /*isBlocking*/ false);
    for (UInt i = 0; i < 100; ++i)
    {
        api.sendSyncSignalSCP(0.05f);
        SecDelay(0.1f);
    }
}

void RunScenarioDefinition(VtdApi& api)
{
    DefineScenario(api);
    InitScenario(api);
    SetPlayerPositions(api);
    StartAndAutoEndScenario(api);
    StartAndTriggerScenario(api);
    StopScenario(api);

    std::cout << "Scenario terminated." << std::endl;
}
/**
 * Milestone Features sample. Use with Setup SimManagerTriggerSCP and SimManager project.
 */
int main(int argc, char** argv)
{
    std::string vtdRoot = ".";
    std::string projectName = "SampleProject";
    std::string setupName = "Standard";

    if (argc > 1)
    {
        vtdRoot = argv[1];
    }
    else
    {
        std::cout << "Usage: ExampleTestAutomation <VTD_ROOT> <Setup>" << std::endl;
        std::cout << "e.g.: ExampleTestAutomation /home/dw/projects/VTD Standard" << std::endl;
        exit(1);
    }

    if (argc > 2)
    {
       setupName = argv[2];
    }

    std::cout << "Kill previous instance." << std::endl;
    Internal::FileSystemIO::turnOffVtd(vtdRoot);

    std::cout << "Load VTD Environment; for debug information see debug.txt." << std::endl;
    Internal::FileSystemIO::turnOnVtd(vtdRoot, setupName, projectName);

    std::string projectPath = vtdRoot + "/Data/Projects/" + projectName;
    std::string scenarioBasePath = vtdRoot + projectPath + "/Scenarios/";

    ScenarioList scenarioList;
    scenarioList.push_back(scenarioBasePath + "Crossing8Demo.xml");
    scenarioList.push_back(scenarioBasePath + "TrafficDemo.xml");

    VtdApi api;
    ConnectionHandle handle = api.connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);

    if (handle)
    {
        if (setupName == "SimManagerTriggerSCP")
        {
            std::cout << "Run a specific scenario." << std::endl;
            RunScenarioDefinition(api);
        }
        else
        {
            std::cout << "Run scenario list." << std::endl;
            RunScenarioList(api, scenarioList);
        }

        std::cout << "All scenarios done." << std::endl;
    }
    else
    {
        std::cout << "SCP Connection Failed." << std::endl;
    }

    std::cout << "Stopping VTD." << std::endl;

    api.disconnectSCP(handle);

    Internal::FileSystemIO::turnOffVtd(vtdRoot);

    std::cout << "Exiting..." << std::endl;
    return 0;
}
