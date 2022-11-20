#ifndef _WRITE_HDF5_DATA_H
#define _WRITE_HDF5_DATA_H

#include <hdf5.h>
#include <hdf5_hl.h>
#include "RDBHDF5lib.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>

#include <vector>
#include <string>
#include <map>
#include "WriteHdf5RDB.h"

namespace  RdbToHdf5Writer
{
    class WriteHdf5Data : public WriteHdf5RDB
    {

    public:
        // CheckValue && CheckVec
        typedef int64_t CheckValue;
        typedef std::vector<CheckValue> CheckVec;
        typedef std::pair<uint64_t, CheckVec> CheckVecPair;
        typedef std::map<CheckVecPair::first_type, CheckVecPair::second_type> CheckVecMap;

        // CheckPair && CheckMap
        typedef std::pair<uint64_t, hid_t> CheckPair;
        typedef std::map<CheckPair::first_type, CheckPair::second_type> CheckMap;

        // CheckStrPair && CheckStrMap
        typedef std::pair<std::string, hid_t> CheckStrPair;
        typedef std::map<CheckStrPair::first_type, CheckStrPair::second_type> CheckStrMap;
        typedef std::pair<uint64_t, CheckStrMap> CheckStrMapPair;
        typedef std::map<CheckStrMapPair::first_type, CheckStrMapPair::second_type> CheckStrMapMap;

        static const int HEADER_NUMBER = 99999;
        static const hid_t INVALID_HID = -1;
        static const std::string DATA_STR;
        static const std::string BASE_STR;
        static const std::string EXT_STR;
        static const std::string POS_STR;
        static const uint64_t FAKE_HEADER_PKG_ID;

        struct SensorInfo
        {
            std::string name;
            unsigned int id;
            unsigned int playerId;
            unsigned int port;
            unsigned int handle;
        };

        typedef std::vector<SensorInfo> SensorInfoVec;
        typedef std::pair<unsigned int, SensorInfo> SensorConnectionPair;
        typedef std::map<SensorConnectionPair::first_type, SensorConnectionPair::second_type> SensorConnectionMap;

        /**
        *	constructor
        */
        WriteHdf5Data();

        /**
        *	destructor
        */
        virtual ~WriteHdf5Data();

        /**
         * @brief init - create shared pointer to hdf5 structure
         */
        void init();

        /**
         * @brief createRootHdf5FolderGroup - create root group
         * @param pkgId - package ID
         */
        void createRootHdf5FolderGroup(const unsigned int& pkgId);

        /**
         * @brief createRootHdf5FolderGroup - create root group
         * @param name - group name
         * @param id - package ID
         */
        void createRootHdf5FolderGroup(const std::string& name, const unsigned int& id);

        /**
         * @brief createNestedHdf5ObjectFolderGroup - create nested group
         * @param grp - root group handler
         * @param name - name of the group
         * @param folderMap - folder group
         * @return hid of created group of, if failed a negative value
         */
        hid_t createNestedHdf5ObjectFolderGroup(hid_t grp, const std::string& name, CheckStrMap& checkStrMap);

        /**
         * @brief createNestedHdf5ObjectFolderGroup - create nested group
         * @param grp - root group handler
         * @param id - id of the group
         * @param checkMap - id/hid map
         * @return hid of created group of, if failed a negative value
         */
        hid_t createNestedHdf5ObjectFolderGroup(hid_t grp, const std::string& name, const uint64_t id, CheckMap& checkMap);

        /**
         * @brief closeHeaderHdf5Group - close hdf5 group
         * @param groupId - group Id
         */
        void closeHeaderHdf5Group(hid_t groupId);

        /**
         * @brief closeHdf5AllFolders - close folders
         */
        void closeHdf5AllFolders();

        /**
         * @brief clearTableCreationMap - clears table creation map
         */
        void clearTableCreationMap();

        /**
         * @brief setTableCreateAppend - set created tables to false
         */
        void setTableCreateAppend();

        /**
         * @brief closeGroupTemplate - close group
         * @param folderMap - folder map
         */
        template<typename T>
        void closeGroupTemplate(std::map<T, hid_t>& folderMap)
        {
            typename std::map<T, hid_t>::iterator itr;
            // All open folder must be closed
            for (itr = folderMap.begin(); itr != folderMap.end(); ++itr)
            {
                closeGroup(itr->second);
            }

            folderMap.clear();
            setTableCreateAppend(); // TODO [BB] sets all "table created" booleans to false for a single closeGroupTemplate call?
        }

        /**
         * @param - template param
         * @return string
         */
        template<typename T>
        std::string toString(T value)
        {
            std::stringstream ss;
            ss << value;
            return ss.str();
        }

        // General
        void writeRdbMessage(const RDB_MSG_t& rdbMessage);
        void writeRdbMessageEntry(const RDB_MSG_ENTRY_HDR_t* const entryHdr, const RDB_MSG_t& rdbMessage);
        void writeSensorRdbMessage(const RDB_MSG_t& rdbMessage, SensorInfo& sensorInfo);
        void writeSensorRdbMessageEntry(const RDB_MSG_ENTRY_HDR_t* const entryHdr, const RDB_MSG_t& rdbMessage, SensorInfo& sensorInfo);

        /**
         * @brief write<T> - write data to hdf5 file
         * @param RDBMessage - rdb message
         * @param isExtended - is extended or not
         */
        void writeHeader(const RDB_MSG_HDR_t& messageHeader);
        void writeObjectCfgEntry(const double simTime, const unsigned int simFrame, const RDB_OBJECT_CFG_t& data);
        void writeCoordEntry(const double simTime, const unsigned int simFrame, const RDB_COORD_t& data);
        void writeRoadPosEntry(const double simTime, const unsigned int simFrame, const RDB_ROAD_POS_t& data);
        void writeVehicleSystemEntry(const double simTime, const unsigned int simFrame, const RDB_VEHICLE_SYSTEMS_t& data);
        void writeVehicleSetupEntry(const double simTime, const unsigned int simFrame, const RDB_VEHICLE_SETUP_t& data);
        void writeDriverCtrlEntry(const double simTime, const unsigned int simFrame, const RDB_DRIVER_CTRL_t& data);
        void writeDriverPerceptionEntry(const double simTime, const unsigned int simFrame, const RDB_DRIVER_PERCEPTION_t& data);
        void writeEnvironmentData(const double simTime, const unsigned int simFrame, const RDB_ENVIRONMENT_t& data);
        void writeRoadStateEntry(const double simTime, const unsigned int simFrame, const RDB_ROAD_STATE_t& data);
        void writeLaneInfoEntry(const double simTime, const unsigned int simFrame, const RDB_LANE_INFO_t& data);
        void writeSyncEntry(const double simTime, const unsigned int simFrame, const RDB_SYNC_t& data);
        void writeCustomScoringEntry(const double simTime, const unsigned int simFrame, const RDB_CUSTOM_SCORING_t& data);
        void writeObjectStateEntry(const double simTime, const unsigned int simFrame, const RDB_OBJECT_STATE_t& data, const bool isExtended);
        void writeEngineEntry(const double simTime, const unsigned int simFrame, const RDB_ENGINE_t& data, const bool isExtended);
        void writeWheelEntry(const double simTime, const unsigned int simFrame, const RDB_WHEEL_t& data, const bool isExtended);
        void writeTrafficLightEntry(const double simTime, const unsigned int simFrame, const RDB_TRAFFIC_LIGHT_t& data, const bool isExtended);
        void writeSensorObjectEntry(const double simTime, const unsigned int simFrame, const RDB_SENSOR_OBJECT_t& data);
        void writeSensorStateEntry(const double simTime, const unsigned int simFrame, const RDB_SENSOR_STATE_t& data);

        void updateSensorInfoFromSensorState(const RDB_MSG_t& rdbMessage, SensorInfo& sensorInfo);

        // set file id, handler to file
        void setFileId(hid_t fileId){fileId_ = fileId;}
        // get file id, handler to file
        hid_t getFileId(){ return fileId_;}

    protected:

        CheckVec* getTableCreationCheckVec(int64_t id);

        // file name
        std::string fileName_;
        // group maps
        CheckMap groupsMap_;
        // sub group map
        CheckStrMapMap subGroupsMap_;
        // table creation check map
        CheckVecMap tableCreationCheckMap_;

        // TODO [BB]: get rid of all groups down here
        // sensor state pos group
        CheckStrMap groupsSensorStatePos_; // TODO [BB] rework to CheckMap
        // object state group
        CheckStrMap groupsObjectStateMap_; // TODO [BB] rework to CheckMap
        // engine group
        CheckStrMap groupsEngine_; // TODO [BB] rework to CheckMap
        // wheel group
        CheckStrMap groupsWheel_; // TODO [BB] rework to CheckMap
        CheckMap groupsWheelGroup_; // TODO [BB] rework to CheckMap
        // sensor group
        CheckMap groupsSensorStateGroup_; // TODO [BB] rework to CheckMap
        CheckMap groupsSensorObjectGroup_; // TODO [BB] rework to CheckMap
        // traffic light group
        CheckStrMap groupsTrafficlight_; // TODO [BB] rework to CheckMap

        // shared pointers to hdf5 structure
        boost::shared_ptr<Hdf5RdbMessageHeader> hdf5RdbMessageHeader_;
        boost::shared_ptr<Hdf5RdbMessageObjectCfg> hdf5RdbMessageObjectCfg_;
        boost::shared_ptr<Hdf5RdbMessageCoord> hdf5RdbMessageCoord_;
        boost::shared_ptr<Hdf5RdbMessageRoadPos> hdf5RdbMessageRoadPos_;
        boost::shared_ptr<Hdf5RdbMessageVehicleSystem> hdf5RdbMessageVehicleSystem_;
        boost::shared_ptr<Hdf5RdbMessageVehicleSetup> hdf5RdbMessageVehicleSetup_;
        boost::shared_ptr<Hdf5RdbDriverCtrl> hdf5RdbDriverCtrl_;
        boost::shared_ptr<Hdf5RdbDriverPerception> hdf5RdbDriverPerception_;
        boost::shared_ptr<Hdf5RdbEnvironment> hdf5RdbEnvironment_;
        boost::shared_ptr<Hdf5RdbRoadState> hdf5RdbRoadState_;
        boost::shared_ptr<Hdf5RdbMessageLaneInfo> hdf5RdbMessageLaneInfo_;
        boost::shared_ptr<Hdf5RdbSync> hdf5RdbSync_;
        boost::shared_ptr<Hdf5RdbCustomScoring> hdf5RdbCustomScoring_;
        boost::shared_ptr<Hdf5RdbMessageObjectStateBase> hdf5RdbMessageObjectStateBase_;
        boost::shared_ptr<Hdf5RdbMessageObjectStateExt> hdf5RdbMessageObjectStateExt_;
        boost::shared_ptr<Hdf5RdbMessageGeometry> hdf5RdbMessageGeometry_;
        boost::shared_ptr<Hdf5RdbMessageEngineExt> hdf5RdbMessageEngineExt_;
        boost::shared_ptr<Hdf5RdbMessageEngineBase> hdf5RdbMessageEngineBase_;
        boost::shared_ptr<Hdf5RdbMessageWheelExt> hdf5RdbMessageWheelExt_;
        boost::shared_ptr<Hdf5RdbMessageWheelBase> hdf5RdbMessageWheelBase_;
        boost::shared_ptr<Hdf5RdbTrafficLightBase> hdf5RdbTrafficLightBase_;
        boost::shared_ptr<Hdf5RdbTrafficLightExt> hdf5RdbTrafficLightExt_;
        boost::shared_ptr<Hdf5RdbSensorObject> hdf5RdbSensorObject_;
        boost::shared_ptr<Hdf5RdbSensorState> hdf5RdbSensorState_;

        // if table has been created
        bool isHeaderTableCreated_ ;

        bool verbose_;
    };
}
#endif
