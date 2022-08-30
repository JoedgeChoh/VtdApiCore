#ifndef VTDAPICORE_IVtdApi_H
#define VTDAPICORE_IVtdApi_H

#include <VtdCore/Macros.h>
#include <VtdMath/Vector.h>
#include <VtdToolkit/viRDBIcd.h>

#include <VtdNetwork/service_port.h>
#include <VtdNetwork/tcp_port.h>
#include <VtdNetwork/udp_port.h>

namespace VTD {
    
// maximum time out time is used as default time out parameter
static const unsigned int MAXIMUM_TIMEOUT = 1200; // 20 min
// update each 3 microsec
static const unsigned int MICROSEC_UPDATE = 3; // 20 min
// time to update stage in microseconds
static const uint64_t UPDATE_STAGE = 100000;
// pause to give thread some time
static const uint64_t MIN_PAUSE_NANO_SEC = 10;
/**
* VTD Operation stages, see VTD Documentation.
*/
struct OperationStage {
    enum Enum {
        UNDEFINED = 0,
        CONFIG,
        READY,
        INITDONE,
        RUN,
        PAUSE
    };
    /**
     * @brief toString return string with operation stage
     * @param stage enum stage
     * @return string
     */
    static std::string toString(Enum stage)
    {
        switch (stage) {
        case CONFIG:
            return "CONFIG";
        case READY:
            return "READY";
        case INITDONE:
            return "INITDONE";
        case RUN:
            return "RUN";
        case PAUSE:
            return "PAUSE";
        default:
            return "UNDEFINED";
        }
    }
};

/**
 * @brief The IVtdApi abstract VtdApi class
 */
class IVtdApi
{
    public:

        /**
        * @brief The OperationMode struct
        */
        struct OperationMode
        {
            enum Enum
            {
                UNSET = 0,
                PREPARATION,
                OPERATION
            };

            /**
             * @brief toString return string with operation mode
             * @param mode opeartion mode
             * @return string
             */
            static std::string toString(Enum mode) {
                switch(mode) {
                case UNSET:
                    return "unset";
                case OPERATION:
                    return "operation";
                case PREPARATION:
                    return "preparation";
                }
                return "unknown";
        }
    };

    /**
     * @brief The Protocol struct
     */
    struct Protocol
    {
        enum Enum {
            SCP = 0
            , RDB_TCP
            , RDB_UDP
            , RDB_UDP_SEND_ONLY
            , RDB_UDP_RECEIVE_ONLY
        };
    };

    /**
     * @brief The PlayerControl struct
     */
    struct PlayerControl
    {
        enum Enum {
            INTERNAL = 0,
            EXTERNAL
        };

        /**
         * @brief toString string control
         * @param control internal or external
         * @return string
         */
        static std::string toString(Enum control) {
            switch(control) {
            case INTERNAL:
                return "internal";
            case EXTERNAL:
                return "external";
            }
            return "unknown";
        }
    };

    /**
     * @brief The PlayerCategory struct
     */
    struct PlayerCategory
    {
        enum Enum {
            VEHICLE = 0,
            PEDESTRIAN,
            OBJECT
        };

        /**
         * @brief toString return category
         * @param category
         * @return string
         */
        static std::string toString(Enum category) {
            switch(category) {
            case VEHICLE:
                return "vehicle";
            case PEDESTRIAN:
                return "pedestrian";
            case OBJECT:
                return "object";
            }
            return "unknown";
        }
    };

    /**
     * @brief The SetEntity struct
     */
    struct SetEntity {
        enum Enum
        {
            SCENARIOEDITOR = 0,
            PLAYER,
            TRAFFIC,
            SOUND,
            IMAGEGENERATOR,
            TASKCONTROL,
            DYNAMICS,
            RDBLOG,
            ODRGATEWAY
        };

        /**
         * @brief toString return entity
         * @param entity
         * @return string
         */
        static std::string toString(Enum entity)
        {
            switch (entity)
            {
            case DYNAMICS:
                return "dynamics";
            case IMAGEGENERATOR:
                return "imageGenerator";
            case ODRGATEWAY:
                return "odrGateway";
            case PLAYER:
                return "player";
            case RDBLOG:
                return "RDBlog";
            case SCENARIOEDITOR:
                return "scenarioEditor";
            case SOUND:
                return "sound";
            case TASKCONTROL:
                return "taskControl";
            case TRAFFIC:
                return "traffic";
            }

            return "unknown";
        }
    };

    virtual ~IVtdApi(void) { /**/ }

    /**
     * @brief connectSCP - connect to port to receive SCP messages
     * @param hostname - host name
     * @param scpPortNumber - port number usually 48179
     * @param directModeForStates - use directMode for updating the internal VTD state
     * @return return - communication handler
     */
    virtual ConnectionHandle connectSCP(const std::string& hostname, unsigned int scpPortNumber = DEFAULT_SCP_PORT, bool directMode = false) = 0;

    /**
     * @brief disconnectSCP - disconnected from scp port
     * @param handle - scp communication handle usually 48179
     * @return true if succes or false when not
     */
    virtual bool disconnectSCP(ConnectionHandle& handle) = 0;

    /**
     * @brief connectRDB - connect to port to receive SCP messages
     * @param hostname - host name for UDP usually adrress is broadcast adrress
     * @param rdbPortNumber - port number for general message we used 48190 for TCP and 48190 and 48191 for UDP
     * @param rdbProtocol - type of protocoll TCP or UDP
     * @param directMode - pass received messages directly to callbacks (false = use internal buffer; need to call update() to process the buffer)
     * @return communication handle
     */
    virtual ConnectionHandle connectRDB(const std::string& hostname, unsigned int rdbPortNumber = DEFAULT_RDB_PORT, Protocols::Enum rdbProtocol = Protocols::RDB_TCP, bool directMode = false) = 0;

    /**
     * @brief disconnectRDB - disconnect from rdb port
     * @param handle - communication handle
     * @return true if succes or false when not
     */
    virtual bool disconnectRDB(ConnectionHandle& handle) = 0;

    /**
     * @brief changeProject - change project
     * @param projectName - project name
     * @param projectPath - path to project
     */
    virtual void changeProject(const std::string& projectName, const std::string& projectPath) = 0;

    /**
     * @brief initSimulation - init simulation
     * @param mode - mode of simulation refer to enum OperationMode
     * @param isBlocking - block until OperationStage::INITDONE is reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void initSimulation(OperationMode::Enum mode = OperationMode::UNSET, bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) = 0;

    /**
     * @brief isSimulationInitialized - check if simulation is initilazed
     * @return true if it is or false when not
     */
    virtual bool isSimulationInitialized(void) = 0;

    /**
     * @brief loadScenario - load scenario fromm xml file
     * @param scenarioName - name of scenario
     */
    virtual void loadScenario(const std::string& scenarioName) = 0;

    /**
     * @brief applyConfiguration - apply configuration stage to VTD
     * @param startByScript - should it start by script
     * @param isBlocking - block until OperationStage::READY is reached
     */
    virtual void applyConfiguration(bool startByScript = false, bool isBlocking = true) = 0;

    /**
     * @brief enterConfigurationStage - enter configuration stage
     * @param isBlocking - block until OperationStage::CONFIG is reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void enterConfigurationStage(bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) = 0;

    /**
     * @brief registerVtdComponent - register a VTD component via name
     * @param name - component name
     */
    virtual void registerVtdComponent(const std::string& name) = 0;

    /**
     * @brief sendInitDoneVtdComponent - send "InitDone" for component
     * @param name - component name
     */
    virtual void sendInitDoneVtdComponent(const std::string& name) = 0;

    /**
     * @brief start the simulation
     * @param mode The OperationMode in which to start the simulation
     * @param duration The duration for which to run the simulation, in seconds.
     * Default: -1.0f. Give a negative value to run the simulation indefinitely.
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void startSimulation(OperationMode::Enum mode = OperationMode::UNSET
                                , float maxDuration = -1.0f
                                , bool isBlocking = true
                                , const double& timeOut = MAXIMUM_TIMEOUT) = 0;

    /**
     * @brief pauseSimulation - paused simmulation
     * @param isBlocking - block until OperationStage::PAUSE is reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void pauseSimulation(bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) = 0;

    /**
     * @brief stopSimulation - stop simulation
     * @param isBlocking - block until OperationStage::READY is reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void stopSimulation(bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) = 0;

    /**
     * @brief restartSimulation - restart simulation
     * @param isBlocking - block until OperationStage::READY und OperationStage::RUN are reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void restartSimulation(bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) = 0;

    /**
     * @brief stepSimulation - Run the simulation for a specific number of frames.
     * @param stepSize - size of step
     * @param isBlocking - block until OperationStage::RUN und OperationStage::PAUSE are reached
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void stepSimulation(int stepSize, bool isBlocking = true, const double& timeOut = MAXIMUM_TIMEOUT) = 0;

    /**
     * @brief sendSyncSignalSCP via SCP for SCP response and lower framerates
     * @param deltaTime
     * @param timeOut - time to time out not to block application for ever
     */
    virtual void sendSyncSignalSCP(float deltaTime = 0.0f) = 0;

    /**
     * @brief sendSyncSignalRDB - send sync via RDB port
     * @param handle - communication handle
     * @param deltaTime - delta time or time step
     * @param simTime - simulation time after sending sync
     * @param simFrame - frame number
     */
    virtual void sendSyncSignalRDB(const ConnectionHandle& handle, float deltaTime, double simTime, unsigned int simFrame) = 0;

    /**
     * @brief sendSyncRDB - send sync via RDB port
     * @param handle - communication handle
     * @param simTime - simulation time after sending sync
     * @param simFrame - frame number
     */
    virtual void sendSyncRDB(const ConnectionHandle& handle, double simTime, unsigned int simFrame) = 0;

    /**
     * @brief sendTriggerRDB - send sync via RDB port
     * @param handle - communication handle
     * @param deltaTime - delta time or time step
     * @param simTime - simulation time after sending sync
     * @param simFrame - frame number
     */
    virtual void sendTriggerRDB(const ConnectionHandle& handle, float deltaTime, double simTime, unsigned int simFrame) = 0;

    /**
     * @brief sendScpCommand - send scp command
     * @param message - message string
     * @param senderName - sender name
     * @param receiverName - reciver  name
     */
    virtual void sendScpCommand(const std::string& message, const char* senderName = "VtdApi", const char* receiverName = "TaskControl") = 0;

    /**
     * Send an RDB message to the connected VTD client.
     * @param msg a reference to the RDB_MSG_t that is to be sent.
     * @param handle the connection handle to which the messages shall be sent. If 0 the message will be broadcast.
     */
    virtual void sendRdbMessage(const ConnectionHandle& handle, const RDB_MSG_t& msg) = 0;

    /**
     * @brief createPlayerVehicle - creates player vihecle
     * @param playerName - name of player
     * @param vehicle - type of vehicle
     * @param driver - type of driver
     * @param playerControl - control internal or external
     * @param adaptDriverToVehicleType - should driver be addapted to vihecle type refer to documntation
     */
    virtual void createPlayerVehicle(const std::string& playerName,
                                     const std::string& vehicle = "",
                                     const std::string& driver = "",
                                     PlayerControl::Enum playerControl = PlayerControl::INTERNAL,
                                     bool adaptDriverToVehicleType = false) = 0;

    /**
     * @brief deletePlayerVehicle - delete player vehicle
     * @param playerName - name of player
     */
    virtual void deletePlayerVehicle(const std::string& playerName) = 0;

    /**
     * @brief setPlayerVehicleSpeed - set speed of vihecle
     * @param playerName - player name
     * @param speed - speed of player
     */
    virtual void setPlayerVehicleSpeed(const std::string& playerName, float speed) = 0;

    /**
     * @brief setPlayerVehicleSpeedRelative - set speed relativelly to pivot player
     * @param playerName - player name
     * @param pivotName - pivot player name
     * @param speed - amount of speed
     */
    virtual void setPlayerVehicleSpeedRelative(const std::string& playerName,
                                               const std::string& pivotName,
                                               float speed) = 0;

    /**
     * @brief setPlayerVehiclePosInertial - set player position
     * @param playerName - player name
     * @param xyz - vector of coortinates
     * @param hprDeg - heading, pitch and roll
     */
    virtual void setPlayerVehiclePosInertial(const std::string& playerName,
                                             const Vec3& xyz,
                                             const Vec3& hprDeg) = 0;


    /**
     * @brief setPlayerVehiclePosRelative - set player position relativelly to pivot player
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
                                             bool persistent = false) = 0;

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
                                                 bool persistent = false) = 0;

    /**
     * @brief queryPlayerName - query if player exist
     * @param player - player name
     */
    virtual void queryPlayerName(const std::string& player) = 0;

    /**
     * @brief isConnected - check if port is connected
     * @param handle communication handle
     * @return
     */
    virtual bool isConnected(const ConnectionHandle& handle) const = 0;

    /**
     * Query the OperationStage.
     * @return the current state the simulation is in.
     */
    virtual OperationStage::Enum getOperationStage() = 0;

    VTD_DEPRECATED_FUNC("Use isConnected instead", bool isConnectedSCP(const ConnectionHandle& handle) const);
    VTD_DEPRECATED_FUNC("Use isConnected instead", bool isConnectedRDB(const ConnectionHandle& handle) const);
};

} //namespace VTD

#endif //VTDAPICORE_IVtdApi_H
