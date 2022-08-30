#ifndef EXAMPLE_CONSOLE_SENSOR_AND_DRIVER_CTRL_H
#define EXAMPLE_CONSOLE_SENSOR_AND_DRIVER_CTRL_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>
#include <VtdToolkit/Scp/ScpBuilder.h>

/**
 * Class ExampleConsoleSensorAndDriverCtrl is an example how to use VtdApi to control vehicle,
 * it receives data from sensor,
 * calculate position of detected object,
 * check if object has same direction as Ego,
 * control ego's vehicle to follow object in front of him
 */

using namespace VTD;

class ExampleConsoleSensorAndDriverCtrl
{
public:
    /**
    * Constructor
    */
    ExampleConsoleSensorAndDriverCtrl();

   /**
    * @brief handleRdbMessage - receive RDB
    * @param msg - RDB message
    */
    void handleRdbMessage(const ReceiveRDB* msg);

   /**
    * @brief sendDriverCtrl - send driver control structure
    * @param msg - RDB message
    * @param accelerationTarget - target should be in km/h
    */
    void sendDriverCtrl(const RDB_MSG_t& RDBMessage, const double& accelerationTarget);

    /**
     * @brief calculateSpeed - calculate speed vector magnitude
     * @param xSpeedCorr - speed vector x coordinate
     * @param ySpeedCorr - speed vector y coordinate
     * @param zSpeedCorr - speed vedctor z coordinate
     * @param headingVec - heading vector
     * @return
     */
    double calculateSpeed(const double& xSpeedCorr, const double& ySpeedCorr, const double& zSpeedCorr, const Vector3lf& headingVec);

    /**
     * @brief calculateAcceleration direction of direction of acceleration (break or acceleration)
     * @param objectDistane - distance to privious object position
     * @param distanceToNearestObject - current distance
     * @param speedEgo - speed of Ego
     * @param speedOfObject - object speed
     * @return
     */
    double calculateAcceleration(double objectDistane, double distanceToNearestObject, double speedEgo, double speedOfObject);

    /**
     * @brief headingVecCalc - calculate heading vector
     * @param pitch - object pitch
     * @param heading - object heading
     * @return
     */
    Vector3lf headingVecCalc(const float& pitch, const float& heading);

    /**
     * @brief proccesSensorObject
     * @param RDBmessage
     * @param distanceToNearestObject
     * @param nearestObjectDetectedId - Id of nearest detected object
     */
    void proccesSensorObject(const RDB_MSG_t& RDBmessage, double& distanceToNearestObject, unsigned int& nearestObjectDetectedId);

    /**
     * @brief processObjectState
     * @param RDBMessage
     * @param distanceToNearestObject
     * @param nearestObjectDetectedId
     */
    void processObjectState(const RDB_MSG_t& RDBMessage, const double& distanceToNearestObject, const unsigned int& nearestObjectDetectedId);

    /**
     * @brief checkVehicleDirection
     * @param egoHeading
     * @param objectHeading
     * @return
     */
    int checkVehicleDirection(const Vector3lf& egoHeading, const Vector3lf& objectHeading);

    /**
     * @brief initVtdApi - initalaze VtdApi
     * @return true when API is initalized
     */
    bool initVtdApi();

    // handleIncoming_ and hanleOutgoing_ handles for incoming and outgoing RDB connections
    ConnectionHandle handleIncoming_, handleOutgoing_;

    //VTD api
    VtdApi api;

private:
    // Default player Id
    unsigned int playerId_;
};

#endif // EXAMPLE_CONSOLE_SENSOR_AND_DRIVER_CTRL_H
