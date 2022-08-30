#include "VtdApi/VtdApi.h"
#include "VtdApi/Internal/VtdState.h"

#include <VtdCore/Logging/Log.h>

#include <VtdToolkit/scpIcd.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <VtdToolkit/RDBHandler.hh>
#include <VtdThreads/Thread.h>
#include <VtdNetwork/Timer.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

//#include <unistd.h>
#include "boost/filesystem.hpp"


namespace VTD {

VtdApi::VtdApi()
    : vtdState_(new Internal::VtdStateContext())
    , scpHandle_ (0)
    , rdbHandle_ (0)
    , isTimeOut_ (false)
{
}

VtdApi::~VtdApi()
{
    std::map<ConnectionHandle, ServicePort_ptr>::const_iterator active = connectServiceMap_.end();
    while (connectServiceMap_.begin() != active)
    {
        --active;
        ConnectionHandle handle = active->first;
        if (handle == 0)
            continue;

        disconnectRDB(handle);
    }

    connectServiceMap_.clear();
}

ConnectionHandle VtdApi::connectSCP(const std::string& hostname, unsigned int scpPortNumber, bool directMode)
{
    ServicePort_ptr scpPort (new TcpPort);
    // connect to scp port
    scpHandle_ = scpPort->connectSCP(hostname, scpPortNumber);
    // check if connecting was successful
    if (scpHandle_ == 0)
        return scpHandle_;

    scpPort->setDirectMode(directMode);
    connectServiceMap_.insert(std::make_pair(scpHandle_, scpPort));

    // Register to messages
    connectServiceMap_.find(scpHandle_)->second->registerEventFunc<Internal::VtdStateContext, ReceiveSCP>(vtdState_.get(), &Internal::VtdStateContext::handleScpMessage, scpHandle_);
    connectServiceMap_.find(scpHandle_)->second->registerEventFunc<Internal::VtdStateContext, ConnectionEvent>(vtdState_.get(), &Internal::VtdStateContext::handleConnectionEvent, scpHandle_);

    // Start communication thread
    communicationThreads_.insert(std::make_pair(scpHandle_, boost::make_shared<boost::thread> (boost::bind(&ServicePort::startReading, connectServiceMap_.find(scpHandle_)->second))));

    return scpHandle_;
}

bool VtdApi::disconnectSCP(ConnectionHandle& handle)
{
    if (handle == 0)
        return false;

    // Erase communication thread
    connectServiceMap_.find(handle)->second->stopReading();
    if (communicationThreads_[handle]->joinable())
    {
         communicationThreads_[handle]->join();
         communicationThreads_.erase(communicationThreads_.find(handle));
    }

    // Deregister if handle == scpHandle_
    if (handle == scpHandle_)
    {
        connectServiceMap_.find(handle)->second->deregisterEventFunc<Internal::VtdStateContext, ReceiveSCP>(vtdState_.get(), &Internal::VtdStateContext::handleScpMessage, handle);
        connectServiceMap_.find(handle)->second->deregisterEventFunc<Internal::VtdStateContext, ConnectionEvent>(vtdState_.get(), &Internal::VtdStateContext::handleConnectionEvent, handle);
    }

    // Disconnect
    ConnectionHandle tmpHandle = handle;
    connectServiceMap_.find(handle)->second->disconnect(tmpHandle);
    if (connectServiceMap_.count(handle))
        connectServiceMap_.erase(connectServiceMap_.find(handle));

    // Invalidate handle and scpHandle_ if necessary
    handle = tmpHandle;
    if (handle == scpHandle_)
        scpHandle_ = handle = 0;

    return true;
}

bool VtdApi::disconnectRDB(ConnectionHandle& handle)
{
    if (handle == 0)
        return false;

    // Erase communication thread
    connectServiceMap_.find(handle)->second->stopReading();
    if (communicationThreads_[handle]->joinable())
    {
         communicationThreads_[handle]->join();
         communicationThreads_.erase(communicationThreads_.find(handle));
    }

    // Disconnect
    ConnectionHandle tmpHandle = handle;
    connectServiceMap_.find(handle)->second->disconnect(tmpHandle);
    if (connectServiceMap_.count(handle))
        connectServiceMap_.erase(connectServiceMap_.find(handle));

    // Invalidate handle
    handle = tmpHandle;

    return true;
}

ConnectionHandle VtdApi::connectRDB(const std::string& hostname, unsigned int rdbPortNumber, Protocols::Enum rdbProtocol, bool directMode)
{
    switch (rdbProtocol)
    {
        case Protocols::RDB_TCP:
        {
            ServicePort_ptr rdbPort (new TcpPort());
            ConnectionHandle handle = rdbPort->connectRDB(hostname, rdbPortNumber, rdbProtocol);
            connectServiceMap_.insert(std::make_pair(handle, rdbPort));
            if (handle  == 0) return handle;

            rdbPort->setDirectMode(directMode);
            communicationThreads_.insert(std::make_pair(handle, boost::make_shared<boost::thread> (boost::bind(&ServicePort::startReading, connectServiceMap_.find(handle)->second))));
            return handle;
         }break;

        case Protocols::RDB_UDP_SEND_ONLY:
        {
            ServicePort_ptr udpPort (new UdpPort());
            ConnectionHandle handle = udpPort->connectRDB(hostname, rdbPortNumber, rdbProtocol, false, true);
            connectServiceMap_.insert(std::make_pair(handle, udpPort));
            if (handle  == 0)
                return handle;

            udpPort->setDirectMode(directMode);
            communicationThreads_.insert(std::make_pair(handle, boost::make_shared<boost::thread> (boost::bind(&ServicePort::startReading, connectServiceMap_.find(handle)->second))));
            return handle;
        }break;

        case Protocols::RDB_UDP_RECEIVE_ONLY:
        {
            ServicePort_ptr udpPort (new UdpPort());
            ConnectionHandle handle = udpPort->connectRDB(hostname, rdbPortNumber, rdbProtocol, true, false);
            connectServiceMap_.insert(std::make_pair(handle, udpPort));
            if (handle  == 0)
                return handle;

            udpPort->setDirectMode(directMode);
            communicationThreads_.insert(std::make_pair(handle, boost::make_shared<boost::thread> (boost::bind(&ServicePort::startReading, connectServiceMap_.find(handle)->second))));
            return handle;
        }break;

        case Protocols::RDB_UDP:
        {
            ServicePort_ptr udpPort (new UdpPort());
            ConnectionHandle handle = udpPort->connectRDB(hostname, rdbPortNumber, rdbProtocol);
            connectServiceMap_.insert(std::make_pair(handle, udpPort));
            if (handle  == 0)
                return handle;

            udpPort->setDirectMode(directMode);
            communicationThreads_.insert(std::make_pair(handle, boost::make_shared<boost::thread> (boost::bind(&ServicePort::startReading, connectServiceMap_.find(handle)->second))));
            return handle;
        }break;

        default:
            break;
    }

    return 0;
}

using namespace boost::filesystem;
 // This function change the current project link to a new project  [Moh]  11.12.2019
void VtdApi::changeProject(const std::string& projectName, const std::string& currentProjectPath)
{
    try
    {
        VTD_LOG_ERR("VtdApi: Removing Existing Link");
        remove(currentProjectPath.c_str());
    }
    catch (...)
    {

        VTD_LOG_ERR("VtdApi: Error removing Link from "+ currentProjectPath);
        return;
    }

    try
    {
        VTD_LOG_ERR("VtdApi: Linking Current Project to " + projectName);
        create_symlink(projectName.c_str(), currentProjectPath.c_str());
    }
    catch (...)
    {
        VTD_LOG_ERR("VtdApi: Error Linking " + projectName + " at " + currentProjectPath);
    }
}

void VtdApi::initSimulation(OperationMode::Enum mode, bool isBlocking, const double& timeOut)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }

    // Build SimCtrl tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
    // Build Start tag
    sb.beginScpCommand(ScpCommand::Init);
    if (mode != OperationMode::UNSET)
        sb.addScpAttribute("mode", OperationMode::toString(mode));

    sb.endScpCommand();
    sb.endScpCommand();
    sendScpCommand(sb.asString());
    if (isBlocking)
        waitUntilStateReached(OperationStage::INITDONE, timeOut);
}

bool VtdApi::isSimulationInitialized(void)
{
    return(vtdState_->getCurrentOperationStage() == OperationStage::INITDONE);
}

void VtdApi::loadScenario(const std::string& scenarioName)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid.");
        return;
    }

    if (scenarioName.empty())
    {
        VTD_LOG_ERR("VtdApi: Scenario name cannot be empty.");
        return;
    }

    // Build SimCtrl tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
    // Build LoadScenario tag
    sb.beginScpCommand(ScpCommand::LoadScenario);
    sb.addScpAttribute("filename", scenarioName);
    sb.endScpCommand();
    sb.endScpCommand();
    sendScpCommand(sb.asString());
}

void VtdApi::applyConfiguration(bool startByScript, bool isBlocking)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }

    // Build SimCtrl tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
    // Build Apply tag
    sb.beginScpCommand(ScpCommand::Apply);
    if (startByScript)
        sb.addScpAttribute("startByScript", startByScript ? "true" : "false");

    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    sendScpCommand(sb.asString());
    if (isBlocking)
        waitUntilStateReached(OperationStage::READY);
}

void VtdApi::enterConfigurationStage(bool isBlocking, const double& timeOut)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }

    // Build SimCtrl tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
    // Build Config tag
    sb.beginScpCommand(ScpCommand::Config);
    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    sendScpCommand(sb.asString());
    if (isBlocking)
        waitUntilStateReached(OperationStage::CONFIG, timeOut);
}

void VtdApi::registerVtdComponent(const std::string& name)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }

    // Build SimCtrl tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::Query);
    sb.addScpAttribute("entity", "taskControl");
    // Build Config tag
    sb.beginScpCommand(ScpCommand::Init);
    sb.addScpAttribute("source", name);
    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    sendScpCommand(sb.asString());

    std::cout << "VtdApi: Registered external VTD component '" << name << "'" << std::endl;
}

void VtdApi::sendInitDoneVtdComponent(const std::string &name)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }

    // Build SimCtrl tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
    // Build Config tag
    sb.beginScpCommand(ScpCommand::InitDone);
    sb.addScpAttribute("source", name);
    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    sendScpCommand(sb.asString());
}

void VtdApi::startSimulation(OperationMode::Enum mode, float maxDuration, bool isBlocking, const double &timeOut)
{
    // TODO [BB]: ensure configuration was applied and apply it if not
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }

    // Build SimCtrl tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
    // Build Start tag
    sb.beginScpCommand(ScpCommand::Start);
    if (mode != OperationMode::UNSET)
        sb.addScpAttribute("mode", OperationMode::toString(mode));

    if (maxDuration > 0.0f)
        sb.addScpAttribute("tMax", maxDuration);

    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    sendScpCommand(sb.asString());
    if (isBlocking)
        waitUntilStateReached(OperationStage::RUN, timeOut);
}

void VtdApi::pauseSimulation(bool isBlocking, const double& timeOut)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }

    // Build SimCtrl tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
    // Build Pause tag
    sb.beginScpCommand(ScpCommand::Pause);
    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    sendScpCommand(sb.asString());
    if (isBlocking)
        waitUntilStateReached(OperationStage::PAUSE, timeOut);
}

void VtdApi::stopSimulation(bool isBlocking, const double &timeOut)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }

    // Build SimCtrl tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
    // Build Stop tag
    sb.beginScpCommand(ScpCommand::Stop);
    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    sendScpCommand(sb.asString());
    if (isBlocking)
         waitUntilStateReached(OperationStage::READY, timeOut);
}

void VtdApi::restartSimulation(bool isBlocking, const double &timeOut)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }

    // Build SimCtrl tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
    // Build Restart tag
    sb.beginScpCommand(ScpCommand::Restart);
    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    sendScpCommand(sb.asString());
    if (isBlocking)
    {
        waitUntilStateReached(OperationStage::READY, timeOut);
        waitUntilStateReached(OperationStage::RUN, timeOut);
    }
}

void VtdApi::stepSimulation(int stepSize, bool isBlocking, const double &timeOut)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }

    // Build SimCtrl tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
    // Build Step tag
    sb.beginScpCommand(ScpCommand::Step);
    if (stepSize > 0)
        sb.addScpAttribute("size", stepSize);

    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    sendScpCommand(sb.asString());
    if (isBlocking)
    {
        waitUntilStateReached(OperationStage::RUN, timeOut);
        waitUntilStateReached(OperationStage::PAUSE, timeOut);
    }
}

void VtdApi::sendSyncSignalSCP(float deltaTime)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }

    // Build SimCtrl tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
    // Build Sync tag
    sb.beginScpCommand(ScpCommand::Sync);
    if (deltaTime > 0.0f)
        sb.addScpAttribute("dt", deltaTime);

    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    sendScpCommand(sb.asString());
}

void VtdApi::sendSyncRDB(const ConnectionHandle& handle, double simTime, unsigned int simFrame)
{
    if (handle == 0) return;

    Framework::RDBHandler rdbHandler;
    rdbHandler.initMsg();
    RDB_SYNC_t* sync = static_cast<RDB_SYNC_t*>(rdbHandler.addPackage(simTime, simFrame, RDB_PKG_ID_SYNC));
    if (!sync)
        return;

    RDB_MSG_t* msg = rdbHandler.getMsg();

    sendRdbMessage(handle, *msg);
}

void VtdApi::sendTriggerRDB(const ConnectionHandle& handle, float deltaTime, double simTime, unsigned int simFrame)
{
    if (handle == 0) return;

    Framework::RDBHandler rdbHandler;
    rdbHandler.initMsg();
    RDB_TRIGGER_t* trigger = static_cast<RDB_TRIGGER_t*>(rdbHandler.addPackage(simTime, simFrame, RDB_PKG_ID_TRIGGER));
    if (!trigger)
        return;

    trigger->frameNo = simFrame + 1;
    trigger->deltaT = deltaTime;
    RDB_MSG_t* msg = rdbHandler.getMsg();

    sendRdbMessage(handle, *msg);
}

void VtdApi::sendSyncSignalRDB(const ConnectionHandle& handle, float deltaTime, double simTime, unsigned int simFrame)
{
    std::cerr << std::endl;
    std::cerr << "* DEPRECATED method sendSyncSignalRDB()        *" << std::endl;
    std::cerr << "* please use sendSyncRDB() or sendTriggerRDB() *" << std::endl;
    std::cerr << std::endl;

    // This was what the function did until 2019.1
    sendTriggerRDB(handle, deltaTime, simTime, simFrame);
}

void VtdApi::update(int microsecondsToSleep /* = -1*/)
{    
    for (ConnectServiceMap::iterator itr = connectServiceMap_.begin(); itr != connectServiceMap_.end(); ++itr)
        itr->second->update();

    if (microsecondsToSleep >= 0)
        Thread::sleep( boost::numeric_cast<UInt64>( microsecondsToSleep ) );
    else
        Thread::sleepNanoSec(MIN_PAUSE_NANO_SEC);
}

void VtdApi::sendScpCommand(const std::string& command, const char* senderName, const char* receiverName)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }

    ConnectServiceMap::iterator it = connectServiceMap_.find(scpHandle_);

    if (it != connectServiceMap_.end())
        it->second->writeScpData(command, scpHandle_, senderName, receiverName);
}

void VtdApi::sendRdbMessage(const ConnectionHandle& handle, const RDB_MSG_t& msg)
{
    if (handle == 0) // TODO [BB]: put proper logging
        return;

    std::vector<char> buffer(msg.hdr.dataSize + msg.hdr.headerSize);
    std::memcpy(buffer.data(), &msg, (msg.hdr.dataSize + msg.hdr.headerSize));

    ConnectServiceMap::iterator it = connectServiceMap_.find(handle);

    if (it != connectServiceMap_.end())
        connectServiceMap_.find(handle)->second->writeRDBData(buffer, handle);
}

void VtdApi::createPlayerVehicle(const std::string& playerName, const std::string& vehicle, const std::string& driver, PlayerControl::Enum playerControl, bool adaptDriverToVehicleType)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }
    if (playerName.empty())
    {
        VTD_LOG_ERR("VtdApi: Player name cannot be empty.");
        return;
    }

    // Build Player tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::Player);
    sb.addScpAttribute("name", playerName);
    // Build Create tag
    sb.beginScpCommand(ScpCommand::Create);
    sb.addScpAttribute("category", PlayerCategory::toString(PlayerCategory::VEHICLE));
    sb.addScpAttribute("adaptDriverToVehicleType", adaptDriverToVehicleType ? "true" : "false");     // TODO [BB]: check the right default type
    sb.addScpAttribute("control", PlayerControl::toString(playerControl));
    if (!vehicle.empty())
        sb.addScpAttribute("vehicle", vehicle);

    if (!driver.empty())
        sb.addScpAttribute("driver", driver);

    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    connectServiceMap_.find(scpHandle_)->second->writeScpData(sb.asString(), scpHandle_);
}

void VtdApi::deletePlayerVehicle(const std::string& playerName)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }
    if (playerName.empty())
    {
        VTD_LOG_ERR("VtdApi: Player name cannot be empty.");
        return;
    }

    // Build Player tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::Player);
    sb.addScpAttribute("name", playerName);
    // Build Create tag
    sb.beginScpCommand(ScpCommand::Delete);
    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    connectServiceMap_.find(scpHandle_)->second->writeScpData(sb.asString(), scpHandle_);
}

void VtdApi::setPlayerVehicleSpeed(const std::string& playerName, float speed)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }
    if (playerName.empty())
    {
        VTD_LOG_ERR("VtdApi: Player name cannot be empty.");
        return;
    }

    // Build Set tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::Set);
    sb.addScpAttribute("entity", SetEntity::toString(SetEntity::PLAYER));
    sb.addScpAttribute("name", playerName);
    // Build Speed tag
    sb.beginScpCommand(ScpCommand::Speed);
    sb.addScpAttribute("value", speed);
    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    connectServiceMap_.find(scpHandle_)->second->writeScpData(sb.asString(), scpHandle_);
}

void VtdApi::setPlayerVehicleSpeedRelative(const std::string& playerName, const std::string& pivotName, float speed)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }
    if (playerName.empty())
    {
        VTD_LOG_ERR("VtdApi: Player name cannot be empty.");
        return;
    }
    if (pivotName.empty())
    {
        VTD_LOG_ERR("VtdApi: Pivot name cannot be empty.");
        return;
    }

    // Build Set tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::Set);
    sb.addScpAttribute("entity", SetEntity::toString(SetEntity::PLAYER));
    sb.addScpAttribute("name", playerName);
    // Build SpeedRelative tag
    sb.beginScpCommand(ScpCommand::SpeedRelative);
    sb.addScpAttribute("pivot", pivotName);
    sb.addScpAttribute("value", speed);
    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    connectServiceMap_.find(scpHandle_)->second->writeScpData(sb.asString(), scpHandle_);
}

void VtdApi::setPlayerVehiclePosInertial(const std::string& playerName, const Vec3& xyz, const Vec3& hprDeg)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }
    if (playerName.empty())
    {
        VTD_LOG_ERR("VtdApi: Player name cannot be empty.");
        return;
    }

    // Build Set tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::Set);
    sb.addScpAttribute("entity", SetEntity::toString(SetEntity::PLAYER));
    sb.addScpAttribute("name", playerName);
    // Build PosInertial tag
    sb.beginScpCommand(ScpCommand::PosInertial);
    sb.addScpAttribute("x", xyz[0]);
    sb.addScpAttribute("y", xyz[1]);
    sb.addScpAttribute("z", xyz[2]);
    sb.addScpAttribute("hDeg", hprDeg[0]);     // TODO [BB] not pretty, would be nice if vector implementation has hpr which uses xyz internally. isn't that common practice?
    sb.addScpAttribute("pDeg", hprDeg[1]);     // TODO [BB] not pretty, would be nice if vector implementation has hpr which uses xyz internally. isn't that common practice?
    sb.addScpAttribute("rDeg", hprDeg[2]);     // TODO [BB] not pretty, would be nice if vector implementation has hpr which uses xyz internally. isn't that common practice?
    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    connectServiceMap_.find(scpHandle_)->second->writeScpData(sb.asString(), scpHandle_);
}

void VtdApi::setPlayerVehiclePosRelative(const std::string& playerName, const std::string& pivotName, const Vec3& xyz, const Vec3& hprDeg, bool persistent)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }
    if (playerName.empty())
    {
        VTD_LOG_ERR("VtdApi: Player name cannot be empty.");
        return;
    }
    if (pivotName.empty())
    {
        VTD_LOG_ERR("VtdApi: Pivot name cannot be empty.");
        return;
    }

    // Build Set tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::Set); // TODO [BB] create set root command in shared method
    sb.addScpAttribute("entity", SetEntity::toString(SetEntity::PLAYER));
    sb.addScpAttribute("name", playerName);
    // Build PosRelative tag
    sb.beginScpCommand(ScpCommand::PosRelative);
    sb.addScpAttribute("player", pivotName);
    sb.addScpAttribute("dx", xyz[0]);
    sb.addScpAttribute("dy", xyz[1]);
    sb.addScpAttribute("dz", xyz[2]);
    sb.addScpAttribute("dhDeg", hprDeg[0]);     // TODO [BB] not pretty, would be nice if vector implementation has hpr which uses xyz internally. isn't that common practice?
    sb.addScpAttribute("dpDeg", hprDeg[1]);     // TODO [BB] not pretty, would be nice if vector implementation has hpr which uses xyz internally. isn't that common practice?
    sb.addScpAttribute("drDeg", hprDeg[2]);     // TODO [BB] not pretty, would be nice if vector implementation has hpr which uses xyz internally. isn't that common practice?
    sb.addScpAttribute("persistent", persistent ? "true" : "false" );
    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    connectServiceMap_.find(scpHandle_)->second->writeScpData(sb.asString(), scpHandle_);
}

void VtdApi::setPlayerVehiclePosRelativeRoad(const std::string& playerName, const std::string& pivotName, float distance, int lane, float lateralOffset, float deltaHeadingDeg, bool persistent)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }
    if (playerName.empty())
    {
        VTD_LOG_ERR("VtdApi: Player name cannot be empty.");
        return;
    }
    if (pivotName.empty())
    {
        VTD_LOG_ERR("VtdApi: Pivot name cannot be empty.");
        return;
    }

    // Build Set tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::Set);
    sb.addScpAttribute("entity", SetEntity::toString(SetEntity::PLAYER));
    sb.addScpAttribute("name", playerName);
    // Build PosRelativeRoad tag
    sb.beginScpCommand(ScpCommand::PosRelativeRoad);
    sb.addScpAttribute("player", pivotName);
    sb.addScpAttribute("distance", distance);
    sb.addScpAttribute("lane", lane);
    sb.addScpAttribute("offset", lateralOffset);
    sb.addScpAttribute("dhDeg", deltaHeadingDeg);
    sb.addScpAttribute("persistent", persistent ? "true" : "false" );
    sb.endScpCommand();
    sb.endScpCommand();
    // Send command
    connectServiceMap_.find(scpHandle_)->second->writeScpData(sb.asString(), scpHandle_);
}

bool VtdApi::isConnected(const ConnectionHandle& handle) const
{
    if (connectServiceMap_.count(handle) == 0) return false;

    return connectServiceMap_.find(handle)->second->isConnected(handle);
}

OperationStage::Enum VtdApi::getOperationStage()
{
    return vtdState_->getCurrentOperationStage();
}

void VtdApi::queryPlayerName(const std::string& playerName)
{
    if (scpHandle_ == 0)
    {
        VTD_LOG_ERR("VtdApi: SCP handle invalid");
        return;
    }
    if (playerName.empty())
    {
        VTD_LOG_ERR("VtdApi: Player name cannot be empty.");
        return;
    }

    // Build Set tag
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::Query);
    sb.addScpAttribute("entity", SetEntity::toString(SetEntity::PLAYER));
    sb.addScpAttribute("name", playerName);
    sb.endScpCommand();
    // Send command
    connectServiceMap_.find(scpHandle_)->second->writeScpData(sb.asString(), scpHandle_);
}

bool VtdApi::waitUntilStateReached(OperationStage::Enum state, const double& timeOut)
{
    isTimeOut_ = false;
    boost::unique_lock<boost::mutex> lck(mutex_);
    boost::thread t1(boost::bind(&VtdApi::checkStage, this, state, boost::ref(timeOut)));
    if ((cv_.wait_for(lck, boost::chrono::milliseconds(boost::numeric_cast<uint64_t> (timeOut * MILLISEC_IN_SEC))) == boost::cv_status::timeout) == isTimeOut_)
    {
        if (t1.joinable()) t1.join();

        return true;
    }
    else
    {
        if (t1.joinable()) t1.join();

        return false;
    }
}

void VtdApi::checkStage(OperationStage::Enum state, const double& timeOut)
{
    Timer timer;
    timer.start();
    while (vtdState_->getCurrentOperationStage() != state && timer.elapsedMilliseconds() < (timeOut  * MILLISEC_IN_SEC))
    {
        update( MICROSEC_UPDATE );
        Thread::sleep( UPDATE_STAGE );
    }

    if (timer.elapsedMilliseconds() > (timeOut  * MILLISEC_IN_SEC))
        isTimeOut_ = true;

    cv_.notify_one();
}

} //namespace
