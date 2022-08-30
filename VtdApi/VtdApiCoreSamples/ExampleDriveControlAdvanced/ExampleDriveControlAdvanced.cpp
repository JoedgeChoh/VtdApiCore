#include "ExampleDriveControlAdvanced.h"

#include <string>
#include <cmath>
#include <cstdio>

namespace
{
    // default sensor port
    static const unsigned int SENSOR_PORT = 48185;
    // default player
    static const unsigned int EGO_ID = 1;
    // const to convert m/s to km/h
    static const double METERS_SEC_KILOMETERS_HOUR = 3.6;
    // convert km/h to m/s
    static const double KILOMETERS_HOUR_TO_METERS_SEC = 0.27777777777778;
    // distance until sensor can detect object
    static const double MAXIMUM_SENSOR_DISTANCE = 100.0;
    // distance when auto starts to break or speed up
    static const double START_SENSOR_DATA_PROCCES = 50.0;
    // default host
    const std::string DEFAULT_HOST = "127.0.0.1";
    // if message contains extended data structure
    static const bool OBJECT_STATE_EXTENDED = true;
    // if message not contains extended data structure
    static const bool OBJECT_STATE_NOT_EXTENDED = false;
}

ExampleConsoleSensorAndDriverCtrl::ExampleConsoleSensorAndDriverCtrl()
    : handleIncoming_(0)
    , handleOutgoing_(0)
    , playerId_(EGO_ID)
{

}

bool ExampleConsoleSensorAndDriverCtrl::initVtdApi()
{
    // Handle for incomming data
    handleIncoming_ = api.connectRDB(DEFAULT_HOST, SENSOR_PORT, Protocols::RDB_TCP);
    // Handle for outcomming data
    handleOutgoing_ = api.connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::Protocols::RDB_TCP);
    // Register event if RDB has been connected
    if( handleOutgoing_ && handleIncoming_)
    {
        api.registerEventFunc<ExampleConsoleSensorAndDriverCtrl, ReceiveRDB>(this, &ExampleConsoleSensorAndDriverCtrl::handleRdbMessage, handleIncoming_);
        printf("VtdApi: Initalized \n");
        return true;
    }
    else
    {
        return false;
    }
}

void ExampleConsoleSensorAndDriverCtrl::handleRdbMessage(const ReceiveRDB* msg)
{
    double distanceToNearestObject = MAXIMUM_SENSOR_DISTANCE;

    unsigned int nearestObjectDetectedId = 0;

    proccesSensorObject( msg->getData(), distanceToNearestObject, nearestObjectDetectedId);

    processObjectState( msg->getData(), distanceToNearestObject, nearestObjectDetectedId);
}

void ExampleConsoleSensorAndDriverCtrl::sendDriverCtrl(const RDB_MSG_t& RDBMessage, const double& accelerationTarget)
{
    Framework::RDBHandler myHandler;

    myHandler.initMsg();

    RDB_DRIVER_CTRL_t* myDriver = reinterpret_cast<RDB_DRIVER_CTRL_t*> (myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_DRIVER_CTRL));

    if (!myDriver) return;

    myDriver->playerId = playerId_;
    myDriver->accelTgt = boost::numeric_cast<float>( accelerationTarget * KILOMETERS_HOUR_TO_METERS_SEC );
    myDriver->validityFlags = RDB_DRIVER_INPUT_VALIDITY_TGT_ACCEL | RDB_DRIVER_INPUT_VALIDITY_ADD_ON;

    printf ("\nEgo acceleration target = %f\n",myDriver->accelTgt);
    api.sendRdbMessage(handleOutgoing_, *myHandler.getMsg());
}

double ExampleConsoleSensorAndDriverCtrl::calculateSpeed(const double& xSpeedCorr, const double& ySpeedCorr , const double& zSpeedCorr, const Vector3lf& headingVec)
{
    const Vector3lf speedVec(xSpeedCorr, ySpeedCorr, zSpeedCorr);

    const Vector3lf headingSpeedVec = headingVec * speedVec.dot(headingVec);
    //Calculating speed vector magnitude
    return sqrt(pow(headingSpeedVec.x(), 2) + pow(headingSpeedVec.y(), 2) + pow(headingSpeedVec.z(), 2)) * METERS_SEC_KILOMETERS_HOUR;
}

Vector3lf ExampleConsoleSensorAndDriverCtrl::headingVecCalc(const float& pitch,const float& heading)
{
    Vector3lf headingVecTemp(cos(pitch) * cos(heading), sin(heading), sin(pitch) * cos(heading));

    headingVecTemp.normalize();

    return headingVecTemp;
}

double ExampleConsoleSensorAndDriverCtrl::calculateAcceleration(double objectDistance, double distanceToNearestObject,double speedEgo, double speedOfObject)
{
    // 1.0 - accelerate -1.0 to break 0.0 - to keep current speed
    double accelerationTarget, break_or_acc = 0;

    if ( objectDistance > distanceToNearestObject )
    {
        accelerationTarget = sqrt((speedEgo - speedOfObject) * (speedEgo - speedOfObject));
        break_or_acc = -1.0;
        // break upon distance
        return (4.0 - (0.04 * distanceToNearestObject)) * (speedEgo - accelerationTarget) * break_or_acc;
    }
    else if ( objectDistance < distanceToNearestObject)
    {
        accelerationTarget = sqrt((speedEgo + speedOfObject) * (speedEgo + speedOfObject));
        break_or_acc = 1.0;
        // accelerate upon distance
        return (4.0 - (0.04 * distanceToNearestObject)) * (accelerationTarget - speedEgo) * break_or_acc;
    }
    else
    {
        // keep same speed
        break_or_acc = 0;
        return 0.0;
    }
}

void ExampleConsoleSensorAndDriverCtrl::proccesSensorObject( const RDB_MSG_t& RDBMessage, double& distanceToNearestObject, unsigned int& nearestObjectDetectedId)
{
    unsigned int noElements = 0;
    RDB_SENSOR_OBJECT_t* sensorObject = reinterpret_cast<RDB_SENSOR_OBJECT_t*>(Framework::RDBHandler::getFirstEntry(&RDBMessage, RDB_PKG_ID_SENSOR_OBJECT, noElements, OBJECT_STATE_NOT_EXTENDED));

    if (noElements == 0) return;

    while (noElements)
    {
        // Check if detected object is nearest to sensor
        if (distanceToNearestObject > sensorObject->dist)
        {
            distanceToNearestObject = sensorObject->dist;
            nearestObjectDetectedId = sensorObject->id;
        }

        if (noElements--)
            ++sensorObject;
    }
}

void ExampleConsoleSensorAndDriverCtrl::processObjectState(const RDB_MSG_t& RDBMessage, const double& distanceToNearestObject, const unsigned int& nearestObjectDetectedId)
{
    // Ego speed, previous object distance and Ego heading vector
    static double speedEgo = 0, objectDistance = 0;
    static Vector3lf egoHeadingVec;

    double speedOfDetectedObject, accelerationTarget;
    Vector3lf headingVec;
    unsigned int noElements;
    RDB_COORD_t pos;

    RDB_OBJECT_STATE_t* objState = reinterpret_cast<RDB_OBJECT_STATE_t*>(Framework::RDBHandler::getFirstEntry(&RDBMessage, RDB_PKG_ID_OBJECT_STATE, noElements, OBJECT_STATE_EXTENDED));

    if(!objState) return;

    while(noElements)
    {
        if (objState->base.id == playerId_)
        {
            pos = objState->base.pos;
            egoHeadingVec = headingVecCalc(pos.p,pos.h);
            // Calculate Ego speed
            speedEgo = calculateSpeed(objState->ext.speed.x, objState->ext.speed.y, objState->ext.speed.z, egoHeadingVec);
            // Print out Ego speed
            printf("Object name: %s  Speed %lf vehSpdX \n", objState->base.name, speedEgo);
        }
        else
        {
            pos = objState->base.pos;
            // Calculate heading vector
            headingVec = headingVecCalc(pos.p,pos.h);
            // Check if detected object is moving in same direction
            int direction = checkVehicleDirection(egoHeadingVec,headingVec);
            printf("Distance to near object %f \n ", distanceToNearestObject);
            if( direction == -1) /*is moving in same direction*/
            {
                // User can adjust distance when will software start acceleration or break
                if (nearestObjectDetectedId == objState->base.id && distanceToNearestObject < (MAXIMUM_SENSOR_DISTANCE - START_SENSOR_DATA_PROCCES))
                {
                    // Calculating diff. speed
                    speedOfDetectedObject = calculateSpeed(objState->ext.speed.x, objState->ext.speed.y, objState->ext.speed.z, headingVec);
                    printf("Object name: %s  Speed differenc %lf vehSpdX and %f distance\n", objState->base.name, speedOfDetectedObject, distanceToNearestObject);
                    // Calculate acceleration target
                    accelerationTarget = calculateAcceleration(objectDistance, distanceToNearestObject, speedEgo, speedOfDetectedObject);
                    // Send driver control
                    sendDriverCtrl(RDBMessage, accelerationTarget );
                }
                else if (nearestObjectDetectedId == objState->base.id && distanceToNearestObject > (MAXIMUM_SENSOR_DISTANCE - START_SENSOR_DATA_PROCCES))
                {
                    // Slowly increase speed if object is further than set detetection distance assuming that object is moving faster than Ego
                    sendDriverCtrl(RDBMessage, 1.0f);
                }
          }
          else
          {
            sendDriverCtrl(RDBMessage, -0.01f);
          }
        }

        objectDistance = distanceToNearestObject;
        if (noElements--)
            ++objState;
   }
}

int ExampleConsoleSensorAndDriverCtrl::checkVehicleDirection(const Vector3lf& egoHeading, const Vector3lf& objectHeading)
{
    return boost::numeric_cast<int> (copysign(1.0, egoHeading.dot(objectHeading)));
}
