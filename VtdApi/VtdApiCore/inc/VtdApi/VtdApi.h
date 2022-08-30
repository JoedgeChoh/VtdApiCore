#ifndef VTDAPICORE_VTDAPI_H
#define VTDAPICORE_VTDAPI_H

#include <VtdCore/Macros.h>

#include <map>
#include <vector>

#include <VtdApi/IVtdApi.h>
#include <VtdApi/Internal/VtdState.h>

namespace Framework
{
    class RDBHandler;
}

namespace VTD
{

/**
 * @brief The VtdApi class
 */

typedef std::map<ConnectionHandle, ServicePort_ptr> ConnectServiceMap;
typedef std::map<ConnectionHandle, boost::shared_ptr<boost::thread> > CommunicationThreads;

class VtdApi : public IVtdApi {

public:
    VtdApi();
    virtual ~VtdApi(void) VTD_OVERRIDE;

    /**
     * @brief connectSCP - connect to port to receive SCP messages
     * @param hostname - host name
     * @param scpPortNumber - port number usually 48179
     * @param directMode - pass received messages directly to callbacks (false = use internal buffer; need to call update() to process the buffer)
     * @return return - communication handler
     */
    virtual ConnectionHandle connectSCP(const std::string& hostname, unsigned int scpPortNumber = DEFAULT_SCP_PORT, bool directMode = false) VTD_OVERRIDE;

    /**
     * @brief disconnectSCP - disconnected from scp port
     * @param handle - scp communication handle usually 48179
     * @return true if succes or false when not
     */
    virtual bool disconnectSCP(ConnectionHandle& handle) VTD_OVERRIDE;

    /**
     * @brief connectRDB - connect to port to receive RDB messages
     * @param hostname - host name for UDP usually adrress is broadcast adrress
     * @param rdbPortNumber - port number for general message we used 48190 for TCP and 48190 and 48191 for UDP
     * @param rdbProtocol - type of protocoll TCP or UDP
     * @param directMode - pass received messages directly to callbacks (false = use internal buffer; need to call update() to process the buffer)
     * @return connection handle
     */
    virtual ConnectionHandle connectRDB(const std::string& hostname, unsigned int rdbPortNumber = DEFAULT_RDB_PORT, Protocols::Enum rdbProtocol = Protocols::RDB_TCP, bool directMode = false) VTD_OVERRIDE;

    /**
     * @brief disconnectRDB - disconnect from rdb port
     * @param handle - communication handle
     * @return true if succes or false when not
     */
    virtual bool disconnectRDB(ConnectionHandle& handle) VTD_OVERRIDE;

    /**
     * @brief changeProject - change project
     * @param projectName - project name
     * @param projectPath - path to project
     */
    virtual void changeProject(const std::string& projectName, const std::string& projectPath) VTD_OVERRIDE;

    /**
     * @brief initSimulation - init simmulation
     * @param mode - mode of simulation refer to enum OpeartionMode
     * @param isBlocking - block until OperationStage::INITDONE is reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void initSimulation(OperationMode::Enum mode = OperationMode::UNSET, bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) VTD_OVERRIDE;

    /**
     * @brief isSimulationInitialized - check if simmulation is initilazed
     * @return true if it is or false when not
     */
    virtual bool isSimulationInitialized(void) VTD_OVERRIDE;

    /**
     * @brief loadScenario - load scenario fromm xml file
     * @param scenarioName - name of scenario
     */
    virtual void loadScenario(const std::string& scenarioName) VTD_OVERRIDE;

    /**
     * @brief applyConfiguration - apply configuration stage to VTD
     * @param startByScript - should it start by script
     * @param isBlocking - block until OperationStage::READY is reached
     */
    virtual void applyConfiguration(bool startByScript = false, bool isBlocking = true) VTD_OVERRIDE;

    /**
     * @brief enterConfigurationStage - enter to config stage
     * @param isBlocking - block until OperationStage::CONFIG is reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void enterConfigurationStage(bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) VTD_OVERRIDE;

    /**
     * @brief registerVtdComponent - register a VTD component via name
     * @param name - component name
     */
    virtual void registerVtdComponent(const std::string& name) VTD_OVERRIDE;

    /**
     * @brief sendInitDoneVtdComponent - send "InitDone" for component
     * @param name - component name
     */
    virtual void sendInitDoneVtdComponent(const std::string& name) VTD_OVERRIDE;

    /**
     * @brief startSimulation - start simmulation
     * @param mode - which mode
     * @param maxDuration - duration of simmulation when -1 no limit
     * @param isBlocking - block until OperationStage::RUN is reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void startSimulation(OperationMode::Enum mode = OperationMode::UNSET, float maxDuration = -1.0f, bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) VTD_OVERRIDE;

    /**
     * @brief pauseSimulation - paused simmulation
     * @param isBlocking - block until OperationStage::PAUSE is reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void pauseSimulation(bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) VTD_OVERRIDE;

    /**
     * @brief stopSimulation - stop simmulation
     * @param isBlocking - block until OperationStage::READY is reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void stopSimulation(bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) VTD_OVERRIDE;

    /**
     * @brief restartSimulation - restart simmulation
     * @param isBlocking - block until OperationStage::READY und OperationStage::RUN are reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void restartSimulation(bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) VTD_OVERRIDE;

    /**
     * @brief stepSimulation - step simullation
     * @param stepSize - size of step
     * @param isBlocking - block until OperationStage::RUN und OperationStage::PAUSE are reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void stepSimulation(int stepSize, bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) VTD_OVERRIDE;

    /**
     * @brief sendSyncSignalSCP - send sync via SCP port
     * @param deltaTime - size of step
     */
    virtual void sendSyncSignalSCP(float deltaTime = 0.0f) VTD_OVERRIDE;

    /**
     * @brief sendSyncSignalRDB - send sync via RDB port
     * @param handle - communication handle
     * @param deltaTime - delta time or time step
     * @param simTime - simulation time after sending sync
     * @param simFrame - frame number
     */
    VTD_DEPRECATED_FUNC("Use sendSyncRDB or sendTriggerRDB instead", virtual void sendSyncSignalRDB(const ConnectionHandle& handle, float deltaTime, double simTime, unsigned int simFrame) VTD_OVERRIDE);

    /**
     * @brief sendSyncRDB - send sync via RDB port
     * @param handle - communication handle
     * @param simTime - simulation time after sending sync
     * @param simFrame - frame number
     */
    virtual void sendSyncRDB(const ConnectionHandle& handle, double simTime, unsigned int simFrame) VTD_OVERRIDE;

    /**
     * @brief sendTriggerRDB - send sync via RDB port
     * @param handle - communication handle
     * @param deltaTime - delta time or time step
     * @param simTime - simulation time after sending sync
     * @param simFrame - frame number
     */
    virtual void sendTriggerRDB(const ConnectionHandle& handle, float deltaTime, double simTime, unsigned int simFrame) VTD_OVERRIDE;

    /**
     * @brief VtdApi::update - update method of VtdApi
     * @param microsencondsToSleep [optional] - microseconds the thread should sleep
     *                  < 0 [default] Thread doesn't sleep at all
     *                  = 0 Thread just makes room for other threads adn awaits to be woken up immediately
     *                  > 0 Thread sleeps at least the given microseconds an awaits to be woken up afterwards
     */
    virtual void update(int microsecondsToSleep = -1);

    /**
     * @brief sendScpCommand - send scp command
     * @param message - message string
     * @param senderName - sender name
     * @param receiverName - reciver  name
     *
     */
    virtual void sendScpCommand(const std::string& message, const char* senderName = "VtdApi", const char* receiverName = "TaskControl") VTD_OVERRIDE;

    /**
     * @brief sendRdbMessage - sends rdb message
     * @param handle - communication handle
     * @param msg - rdb message
     */
    virtual void sendRdbMessage(const ConnectionHandle& handle, const RDB_MSG_t& msg) VTD_OVERRIDE;

    /**
     * @brief createPlayerVehicle - creates player vehicle
     * @param playerName - name of player
     * @param vehicle - type of vehicle
     * @param driver - type of driver
     * @param playerControl - control internal or external
     * @param adaptDriverToVehicleType - should driver be adapted to vehicle type refer to documentation
     */
    virtual void createPlayerVehicle(const std::string& playerName,
                                     const std::string& vehicle = "",
                                     const std::string& driver = "",
                                     PlayerControl::Enum playerControl = PlayerControl::INTERNAL,
                                     bool adaptDriverToVehicleType = false) VTD_OVERRIDE;

    /**
     * @brief deletePlayerVehicle - delete player vehicle
     * @param playerName - name of player
     */
    virtual void deletePlayerVehicle(const std::string& playerName) VTD_OVERRIDE;

    /**
     * @brief setPlayerVehicleSpeed - set speed of vehicle
     * @param playerName - player name
     * @param speed - speed of player
     */
    virtual void setPlayerVehicleSpeed(const std::string& playerName,
                                       float speed) VTD_OVERRIDE;

    /**
     * @brief setPlayerVehicleSpeedRelative - set speed relatively to pivot player
     * @param playerName - player name
     * @param pivotName - pivot player name
     * @param speed - amount of speed
     */
    virtual void setPlayerVehicleSpeedRelative(const std::string& playerName,
                                               const std::string& pivotName,
                                               float speed) VTD_OVERRIDE;

    /**
     * @brief setPlayerVehiclePosInertial - set player position
     * @param playerName - player name
     * @param xyz - vector of coortinates
     * @param hprDeg - heading, pitch and roll
     */
    virtual void setPlayerVehiclePosInertial(const std::string& playerName,
                                             const Vec3& xyz,
                                             const Vec3& hprDeg) VTD_OVERRIDE;

    /**
     * @brief setPlayerVehiclePosRelative - set player position relatively to pivot player
     * @param playerName - player name
     * @param pivotName - pivot name
     * @param xyz - xyz coorinate
     * @param hprDeg - heading, roll and pitch
     * @param persistent
     */
    virtual void setPlayerVehiclePosRelative(const std::string& playerName,
                                             const std::string& pivotName,
                                             const Vec3& xyz,
                                             const Vec3& hprDeg,
                                             bool persistent = false) VTD_OVERRIDE;

    /**
     * @brief setPlayerVehiclePosRelativeRoad - set player position releativelly to road
     * @param playerName - player name
     * @param pivotName - pivot name
     * @param distance - distance to road
     * @param lane - lane ID
     * @param lateralOffset - leteral offset
     * @param deltaHeadingDeg - delta heading
     * @param persistent
     */
    virtual void setPlayerVehiclePosRelativeRoad(const std::string& playerName,
                                                 const std::string& pivotName,
                                                 float distance,
                                                 int lane,
                                                 float lateralOffset,
                                                 float deltaHeadingDeg,
                                                 bool persistent = false) VTD_OVERRIDE;

    /**
     * @brief queryPlayerName - query if player exist
     * @param player - player name
     */
    virtual void queryPlayerName(const std::string& playerName) VTD_OVERRIDE;

    /**
     * @brief isConnected - check if port is connected
     * @param handle communication handle
     * @return
     */
    virtual bool isConnected(const ConnectionHandle& handle) const VTD_OVERRIDE;

    VTD_DEPRECATED_FUNC("Use isConnected instead", bool isConnectedSCP(const ConnectionHandle& handle) const);
    VTD_DEPRECATED_FUNC("Use isConnected instead", bool isConnectedRDB(const ConnectionHandle& handle) const);

    /**
     * Query the OperationStage.
     * @return the current state the simulation is in.
     */
    virtual OperationStage::Enum getOperationStage() VTD_OVERRIDE;

    /**
     * @brief registerEventFunc - register callback function
     * @param receiver - callback function
     * @param connectionHandle - communication handle
     */
    template <class ReceiverT, class EventT> void registerEventFunc(ReceiverT* receiver, void (ReceiverT::*memberFunc)(const EventT*), const ConnectionHandle& connectionHandle);

    /**
     * @brief deregisterEventFunc - deregister callback function
     * @param receiver - callback function
     * @param connectionHandle - communication handle
     */
    template <class ReceiverT, class EventT> void deregisterEventFunc(ReceiverT*, void (ReceiverT::*memberFunc)(const EventT*), const ConnectionHandle& connectionHandle);

    /**
     * @brief waitUntilStateReached - wait until timeout
     * @param state - operation stage
     * @param timeOut - timeOut in seconds
     * @return true if there is no time out
     */
    bool waitUntilStateReached(OperationStage::Enum state, const double& timeOut = MAXIMUM_TIMEOUT);

private:
    /**
     * @brief checkStage - check if operation stage has been reached
     * @param state - operation state
     * @param timeOut - time out in millisec
     */
    void checkStage(OperationStage::Enum state, const double& timeOut = MAXIMUM_TIMEOUT);

private:

    boost::shared_ptr<Internal::VtdStateContext> vtdState_;
    ConnectionHandle scpConnection_;
    ConnectServiceMap connectServiceMap_;
    CommunicationThreads communicationThreads_;
    std::vector<std::string> receivedScpMsgs_;
    ConnectionHandle scpHandle_, rdbHandle_;
    bool isTimeOut_;
    // Implement time_out
    boost::condition_variable cv_;
    boost::mutex mutex_;
};

template <class ReceiverT, class EventT>
void VtdApi::registerEventFunc(ReceiverT* receiver, void (ReceiverT::*memberFunc)(const EventT*), const ConnectionHandle& connectionHandle)
{
    MessageHandler messageHandle;

    switch (EventT::MsgId)
    {
        case MESSAGE_RDB:
        {
            messageHandle.setHandler<EventT>(boost::bind(memberFunc, receiver, boost::placeholders::_1));
            connectServiceMap_.find(connectionHandle)->second->handleRDBMessages_.insert(std::make_pair(connectionHandle, messageHandle));
        }break;

        case MESSAGE_SCP:
        {
            messageHandle.setHandler<EventT>(boost::bind(memberFunc, receiver, boost::placeholders::_1));
            connectServiceMap_.find(connectionHandle)->second->callbackScp_.push_back(messageHandle);
        }break;

        default:
            break;
    }
}


template <class ReceiverT, class EventT>
void VtdApi::deregisterEventFunc(ReceiverT*, void (ReceiverT::*memberFunc)(const EventT*), const ConnectionHandle& connectionHandle)
{
    if (connectServiceMap_.empty())
        return;

    switch (EventT::MsgId)
    {
        case MESSAGE_RDB:
        {
            connectServiceMap_.find(connectionHandle)->second->handleRDBMessages_.find(connectionHandle)->second.unsetHandler<EventT>();
        }break;

        case MESSAGE_SCP:
        {
            connectServiceMap_.find(connectionHandle)->second->callbackScp_.back().unsetHandler<EventT>();
        }break;

        default:
            break;
    }
}

} //namespace VTD

#endif //VTDAPICORE_VTDAPI_H
