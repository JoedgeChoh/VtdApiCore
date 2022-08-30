#include <VtdHdf5/WriteHdf5Data.h>
#include <iostream>
#include <boost/cast.hpp>

namespace
{

    RdbToHdf5Writer::WriteHdf5Data::CheckStrMap& getGroupMapFromGroupsMap(RdbToHdf5Writer::WriteHdf5Data::CheckStrMapMap& subGroupsMap, uint64_t pkgId)
    {
        auto subGroupsIt = subGroupsMap.find(pkgId);
        if (subGroupsIt == subGroupsMap.end())
        {
            std::cout << "ERROR: Couldn't find sub-group \"" << pkgId << "\"" << std::endl;
        }

        return subGroupsIt->second;
    }

}

namespace RdbToHdf5Writer
{
    const std::string DATA_STR = "data";
    const std::string BASE_STR = "base";
    const std::string EXT_STR = "ext";
    const std::string POS_STR = "pos";
    const uint64_t FAKE_HEADER_PKG_ID = 1000;

    WriteHdf5Data::WriteHdf5Data()
        : verbose_(false)
    {
    #ifdef LOG_HDF5
        H5Eset_auto(H5E_DEFAULT, NULL, NULL);
    #endif

        if (verbose_) std::cout << "WriteHdf5Data::CTOR()" << std::endl;

        chunkSize_ = 100;
        compress_ = 0;
        this->init();
    }

    WriteHdf5Data::~WriteHdf5Data()
    {
    }

    void WriteHdf5Data::init()
    {
        if (verbose_) std::cout << "WriteHdf5Data::init()" << std::endl;
        hdf5RdbMessageHeader_ = boost::shared_ptr<Hdf5RdbMessageHeader> (new Hdf5RdbMessageHeader);
        hdf5RdbMessageObjectCfg_ = boost::shared_ptr<Hdf5RdbMessageObjectCfg> (new Hdf5RdbMessageObjectCfg);
        hdf5RdbMessageCoord_ = boost::shared_ptr<Hdf5RdbMessageCoord> (new Hdf5RdbMessageCoord);
        hdf5RdbMessageRoadPos_ = boost::shared_ptr<Hdf5RdbMessageRoadPos>(new Hdf5RdbMessageRoadPos) ;
        hdf5RdbMessageVehicleSystem_ = boost::shared_ptr<Hdf5RdbMessageVehicleSystem> (new Hdf5RdbMessageVehicleSystem);
        hdf5RdbMessageVehicleSetup_ = boost::shared_ptr<Hdf5RdbMessageVehicleSetup>(new Hdf5RdbMessageVehicleSetup);
        hdf5RdbDriverCtrl_ = boost::shared_ptr<Hdf5RdbDriverCtrl>(new Hdf5RdbDriverCtrl);
        hdf5RdbDriverPerception_ = boost::shared_ptr<Hdf5RdbDriverPerception>(new Hdf5RdbDriverPerception);
        hdf5RdbEnvironment_ = boost::shared_ptr<Hdf5RdbEnvironment>(new Hdf5RdbEnvironment);
        hdf5RdbRoadState_ = boost::shared_ptr<Hdf5RdbRoadState> (new Hdf5RdbRoadState);
        hdf5RdbMessageLaneInfo_ = boost::shared_ptr<Hdf5RdbMessageLaneInfo> (new Hdf5RdbMessageLaneInfo);
        hdf5RdbSync_ = boost::shared_ptr<Hdf5RdbSync>(new Hdf5RdbSync);
        hdf5RdbCustomScoring_ = boost::shared_ptr<Hdf5RdbCustomScoring>(new Hdf5RdbCustomScoring);
        hdf5RdbMessageObjectStateBase_ = boost::shared_ptr<Hdf5RdbMessageObjectStateBase> (new Hdf5RdbMessageObjectStateBase);
        hdf5RdbMessageObjectStateExt_ =boost::shared_ptr<Hdf5RdbMessageObjectStateExt> (new Hdf5RdbMessageObjectStateExt);
        hdf5RdbMessageGeometry_ = boost::shared_ptr<Hdf5RdbMessageGeometry>(new Hdf5RdbMessageGeometry);
        hdf5RdbMessageEngineExt_ = boost::shared_ptr<Hdf5RdbMessageEngineExt>(new Hdf5RdbMessageEngineExt);
        hdf5RdbMessageEngineBase_ = boost::shared_ptr<Hdf5RdbMessageEngineBase>(new Hdf5RdbMessageEngineBase);
        hdf5RdbMessageWheelExt_ = boost::shared_ptr<Hdf5RdbMessageWheelExt>(new Hdf5RdbMessageWheelExt);
        hdf5RdbMessageWheelBase_ = boost::shared_ptr<Hdf5RdbMessageWheelBase>(new Hdf5RdbMessageWheelBase);
        hdf5RdbTrafficLightBase_ = boost::shared_ptr<Hdf5RdbTrafficLightBase>(new Hdf5RdbTrafficLightBase);
        hdf5RdbTrafficLightExt_ = boost::shared_ptr<Hdf5RdbTrafficLightExt>(new Hdf5RdbTrafficLightExt);
        hdf5RdbSensorObject_ = boost::shared_ptr<Hdf5RdbSensorObject> (new Hdf5RdbSensorObject);
        hdf5RdbSensorState_ = boost::shared_ptr<Hdf5RdbSensorState> (new Hdf5RdbSensorState);
        setTableCreateAppend();

    }

    void WriteHdf5Data::createRootHdf5FolderGroup(const unsigned int& pkgId)
    {
        hid_t temp = createRootGroup(Framework::RDBHandler::pkgId2string(pkgId));
        groupsMap_.insert(CheckPair(pkgId, temp));

        subGroupsMap_.insert(CheckStrMapPair(pkgId, CheckStrMap())); // Create empty sub map
    }

    void WriteHdf5Data::createRootHdf5FolderGroup(const std::string& name, const unsigned int& id)
    {
        hid_t temp = createRootGroup(name);
        groupsMap_.insert(CheckPair(id, temp));

        subGroupsMap_.insert(CheckStrMapPair(id, CheckStrMap())); // Create empty sub map
    }

    hid_t WriteHdf5Data::createNestedHdf5ObjectFolderGroup(hid_t grp
                                                          , const std::string& name
                                                          , WriteHdf5Data::CheckStrMap& checkStrMap)
    {
        hid_t grpId = createNestedGroup(name, grp);
        checkStrMap.insert(CheckStrPair(name, grpId));
        return grpId;
    }


    hid_t WriteHdf5Data::createNestedHdf5ObjectFolderGroup(hid_t grp
                                                          , const std::string& name
                                                          , const uint64_t id
                                                          , WriteHdf5Data::CheckMap& checkMap)
    {
        hid_t grpId = createNestedGroup(name, grp);
        checkMap.insert(CheckPair(id, grpId));
        return grpId;
    }

    void WriteHdf5Data::closeHdf5AllFolders()
    {
        // All open folder must be closed
        closeGroupTemplate(groupsMap_);
        for(auto it = subGroupsMap_.begin(); it != subGroupsMap_.end(); ++it)
            closeGroupTemplate(it->second);

        closeGroupTemplate(groupsObjectStateMap_);
        closeGroupTemplate(groupsEngine_);
        closeGroupTemplate(groupsWheel_);
        closeGroupTemplate(groupsWheelGroup_);
        closeGroupTemplate(groupsTrafficlight_);
        closeGroupTemplate(groupsSensorStatePos_);
    }

    void WriteHdf5Data::clearTableCreationMap()
    {
        tableCreationCheckMap_.clear();
    }

    void WriteHdf5Data::closeHeaderHdf5Group(hid_t groupId)
    {
        closeGroup(groupId);
    }

    void WriteHdf5Data::writeRdbMessage(const RDB_MSG_t& rdbMessage)
    {        
        if ( !rdbMessage.hdr.dataSize || !isFileOpen() )
            return;

        RDB_MSG_ENTRY_HDR_t* entry = (RDB_MSG_ENTRY_HDR_t*) (((char*) &rdbMessage) + rdbMessage.hdr.headerSize);
        uint32_t remainingBytes = rdbMessage.hdr.dataSize;

        // Write packages
        while (remainingBytes)
        {
            writeRdbMessageEntry(entry, rdbMessage);
            remainingBytes -= (entry->headerSize + entry->dataSize);
            if (remainingBytes)
                entry = (RDB_MSG_ENTRY_HDR_t*) ((((char*) entry) + entry->headerSize + entry->dataSize));
        }
    }

    void WriteHdf5Data::writeRdbMessageEntry(const RDB_MSG_ENTRY_HDR_t* const entryHdr, const RDB_MSG_t& rdbMessage)
    {
        if ( !entryHdr )
            return;

        int noElements = entryHdr->elementSize ? ( entryHdr->dataSize / entryHdr->elementSize ) : 0;
        char* data = (char*) entryHdr;
        data += entryHdr->headerSize;
        bool isExtended = entryHdr->flags & RDB_PKG_FLAG_EXTENDED;

        if (entryHdr->pkgId == RDB_PKG_ID_START_OF_FRAME)
            writeHeader(rdbMessage.hdr); // Write header information on START_OF_FRAME packages

        while ( noElements-- )
        {
            switch ( entryHdr->pkgId )
            {
            case RDB_PKG_ID_COORD_SYSTEM:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_COORD:
                writeCoordEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_COORD_t*) data);
                break;

            case RDB_PKG_ID_ROAD_POS:
                writeRoadPosEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_ROAD_POS_t*) data);
                break;

            case RDB_PKG_ID_LANE_INFO:
                writeLaneInfoEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_LANE_INFO_t*) data);
                break;

            case RDB_PKG_ID_ROADMARK:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_OBJECT_CFG:
                writeObjectCfgEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_OBJECT_CFG_t*) data);
                break;

            case RDB_PKG_ID_OBJECT_STATE:
                writeObjectStateEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_OBJECT_STATE_t*) data, isExtended);
                break;

            case RDB_PKG_ID_VEHICLE_SYSTEMS:
                writeVehicleSystemEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_VEHICLE_SYSTEMS_t*) data);
                break;

            case RDB_PKG_ID_VEHICLE_SETUP:
                writeVehicleSetupEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_VEHICLE_SETUP_t*) data);
                break;

            case RDB_PKG_ID_ENGINE:
                writeEngineEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_ENGINE_t*) data, isExtended);
                break;

            case RDB_PKG_ID_DRIVETRAIN:
                // TODO [BB]: No information stored atm - GOT DATA
                break;

            case RDB_PKG_ID_WHEEL:
                writeWheelEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_WHEEL_t*) data, isExtended);
                break;

            case RDB_PKG_ID_PED_ANIMATION:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_SENSOR_STATE:
                writeSensorStateEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_SENSOR_STATE_t*) data); // Call SensorState always before SensorObject, otherwise sensor ids get mixed up
                break;

            case RDB_PKG_ID_SENSOR_OBJECT:
                writeSensorObjectEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_SENSOR_OBJECT_t*) data);
                break;

            case RDB_PKG_ID_CAMERA:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_CONTACT_POINT:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_TRAFFIC_SIGN:
                // TODO [BB]: No information stored atm - GOT DATA
                break;

            case RDB_PKG_ID_ROAD_STATE:
                writeRoadStateEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_ROAD_STATE_t*) data);
                break;

            case RDB_PKG_ID_IMAGE:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_LIGHT_SOURCE:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_ENVIRONMENT:
                writeEnvironmentData(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_ENVIRONMENT_t*) data);
                break;

            case RDB_PKG_ID_TRIGGER:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_DRIVER_CTRL:
                writeDriverCtrlEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_DRIVER_CTRL_t*) data);
                break;

            case RDB_PKG_ID_TRAFFIC_LIGHT:
                writeTrafficLightEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_TRAFFIC_LIGHT_t*) data, isExtended);
                break;

            case RDB_PKG_ID_DRIVER_PERCEPTION:
                writeDriverPerceptionEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_DRIVER_PERCEPTION_t*) data);
                break;

            case RDB_PKG_ID_LIGHT_MAP:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_TONE_MAPPING:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_ROAD_QUERY:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_SCP:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_SYNC:
                writeSyncEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_SYNC_t*) data);
                break;

            case RDB_PKG_ID_TRAJECTORY:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_DYN_2_STEER:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_STEER_2_DYN:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_PROXY:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_MOTION_SYSTEM:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_OCCLUSION_MATRIX:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_FREESPACE:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_DYN_EL_SWITCH:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_DYN_EL_DOF:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_IG_FRAME:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_RT_PERFORMANCE:
                // TODO [BB]: No information stored atm - GOT DATA
                break;

            case RDB_PKG_ID_RAY:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_CUSTOM_SCORING:
                writeCustomScoringEntry(rdbMessage.hdr.simTime, rdbMessage.hdr.frameNo, *(RDB_CUSTOM_SCORING_t*) data);
                break;

            case RDB_PKG_ID_CUSTOM_OBJECT_CTRL_TRACK:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_CUSTOM_AUDI_FORUM:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_CUSTOM_OPTIX_START:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_CUSTOM_OPTIX_END:
                // TODO [BB]: No information stored atm
                break;

            case RDB_PKG_ID_CUSTOM_LOOK_AHEAD:
                // TODO [BB]: No information stored atm
                break;

            default:
                break;
            }

            data += entryHdr->elementSize;
         }
    }

    void WriteHdf5Data::writeHeader(const RDB_MSG_HDR_t& messageHeader)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeHeader()" << std::endl;

        if (groupsMap_.count(RdbToHdf5Writer::FAKE_HEADER_PKG_ID) == 0)
        {
            createRootHdf5FolderGroup("RDB_MSG_HDR", RdbToHdf5Writer::FAKE_HEADER_PKG_ID);

            createDataTable (  *hdf5RdbMessageHeader_
                             , messageHeader
                             , groupsMap_.find(RdbToHdf5Writer::FAKE_HEADER_PKG_ID)->second
                             , RdbToHdf5Writer::DATA_STR);

            isHeaderTableCreated_ = true;
        }
        else
        {
            appendDataTable(  *hdf5RdbMessageHeader_
                             , messageHeader
                             , groupsMap_.find(RdbToHdf5Writer::FAKE_HEADER_PKG_ID)->second
                             , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeObjectCfgEntry(const double simTime, const unsigned int simFrame, const RDB_OBJECT_CFG_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeObjectCfgData()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_OBJECT_CFG) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_OBJECT_CFG);

        uint64_t playerId = data.id;
        std::string playerIdStr = "Player_ID_" + toString(playerId);

        Hdf5RdbMessageObjectCfg::ENRICHED_RDB_OBJECT_CFG enrichedRdbObjectCfg;
        Hdf5RdbMessageObjectCfg::convertToModifiedStructure(data, simFrame, enrichedRdbObjectCfg);

        auto& subGroupMap = getGroupMapFromGroupsMap(subGroupsMap_, RDB_PKG_ID_OBJECT_CFG);
        if (subGroupMap.find(playerIdStr) == subGroupMap.end())
        {
            createNestedHdf5ObjectFolderGroup(groupsMap_.find(RDB_PKG_ID_OBJECT_CFG)->second
                                               , playerIdStr
                                               , subGroupMap);

            createDataTable( *hdf5RdbMessageObjectCfg_
                            , enrichedRdbObjectCfg
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbMessageObjectCfg_
                            , enrichedRdbObjectCfg
                             , subGroupMap.find(playerIdStr)->second
                             , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeCoordEntry(const double simTime, const unsigned int simFrame, const RDB_COORD_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeCoordData()" << std::endl;

        Hdf5RdbMessageCoord::ENRICHED_RDB_COORD enrichedCoord;
        Hdf5RdbMessageCoord::convertToModifiedStructure(data, simFrame, enrichedCoord);

        if (groupsMap_.count(RDB_PKG_ID_COORD) == 0)
        {
            createRootHdf5FolderGroup(RDB_PKG_ID_COORD);

            createDataTable( *hdf5RdbMessageCoord_
                            , enrichedCoord
                            , groupsMap_.find(RDB_PKG_ID_COORD)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbMessageCoord_
                            , enrichedCoord
                            , groupsMap_.find(RDB_PKG_ID_COORD)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeRoadPosEntry(const double simTime, const unsigned int simFrame, const RDB_ROAD_POS_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeRoadPosData()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_ROAD_POS) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_ROAD_POS);

        uint64_t playerId = data.playerId;
        std::string playerIdStr = "Player_ID_" + toString(playerId);

        Hdf5RdbMessageRoadPos::ENRICHED_RDB_ROAD_POS enrichedRdbRoadPos;
        Hdf5RdbMessageRoadPos::convertToModifiedStructure(data, simFrame, enrichedRdbRoadPos);

        auto& subGroupMap = getGroupMapFromGroupsMap(subGroupsMap_, RDB_PKG_ID_ROAD_POS);
        if (subGroupMap.find(playerIdStr) == subGroupMap.end())
        {
            createNestedHdf5ObjectFolderGroup(groupsMap_.find(RDB_PKG_ID_ROAD_POS)->second
                                               , playerIdStr
                                               , subGroupMap);

            createDataTable( *hdf5RdbMessageRoadPos_
                            , enrichedRdbRoadPos
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbMessageRoadPos_
                            , enrichedRdbRoadPos
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeVehicleSystemEntry(const double simTime, const unsigned int simFrame, const RDB_VEHICLE_SYSTEMS_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeVehicleSystemData()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_VEHICLE_SYSTEMS) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_VEHICLE_SYSTEMS);

        uint64_t playerId = data.playerId;
        std::string playerIdStr = "Player_ID_" + toString(playerId);

        // VEHICLE SYSTEMS
        Hdf5RdbMessageVehicleSystem::ENRICHED_RDB_VEHICLE_SYSTEMS enrichedVehicleSystems;
        Hdf5RdbMessageVehicleSystem::convertToModifiedStructure(data, simFrame, enrichedVehicleSystems);

        auto& subGroupMap = getGroupMapFromGroupsMap(subGroupsMap_, RDB_PKG_ID_VEHICLE_SYSTEMS);
        if (subGroupMap.find(playerIdStr) == subGroupMap.end())
        {
            createNestedHdf5ObjectFolderGroup(groupsMap_.find(RDB_PKG_ID_VEHICLE_SYSTEMS)->second
                                               , playerIdStr
                                               , subGroupMap);

            createDataTable(*hdf5RdbMessageVehicleSystem_
                            , enrichedVehicleSystems
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable(*hdf5RdbMessageVehicleSystem_
                            , enrichedVehicleSystems
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeVehicleSetupEntry(const double simTime, const unsigned int simFrame, const RDB_VEHICLE_SETUP_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeVehicleSetup()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_VEHICLE_SETUP) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_VEHICLE_SETUP);

        uint64_t playerId = data.playerId;
        std::string playerIdStr = "Player_ID_" + toString(playerId);

        // VEHICLE SYSTEMS
        Hdf5RdbMessageVehicleSetup::ENRICHED_RDB_VEHICLE_SETUP enrichedVehicleSetup;
        Hdf5RdbMessageVehicleSetup::convertToModifiedStructure(data, simFrame, enrichedVehicleSetup);

        auto& subGroupMap = getGroupMapFromGroupsMap(subGroupsMap_, RDB_PKG_ID_VEHICLE_SETUP);
        if (subGroupMap.find(playerIdStr) == subGroupMap.end())
        {
            createNestedHdf5ObjectFolderGroup(groupsMap_.find(RDB_PKG_ID_VEHICLE_SETUP)->second
                                               , playerIdStr
                                               , subGroupMap);

            createDataTable( *hdf5RdbMessageVehicleSetup_
                            , enrichedVehicleSetup
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbMessageVehicleSetup_
                            , enrichedVehicleSetup
                             , subGroupMap.find(playerIdStr)->second
                             , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeDriverCtrlEntry(const double simTime, const unsigned int simFrame, const RDB_DRIVER_CTRL_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeDriverCtrlEntry()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_DRIVER_CTRL) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_DRIVER_CTRL);

        uint64_t playerId = data.playerId;
        std::string playerIdStr = "Player_ID_" + toString(playerId);

        Hdf5RdbDriverCtrl::ENRICHED_RDB_DRIVER_CTRL enrichedRdbDriverCtrl;
        Hdf5RdbDriverCtrl::convertToModifiedStructure(data, simFrame, enrichedRdbDriverCtrl);

        auto& subGroupMap = getGroupMapFromGroupsMap(subGroupsMap_, RDB_PKG_ID_DRIVER_CTRL);
        if (subGroupMap.find(playerIdStr) == subGroupMap.end())
        {
            createNestedHdf5ObjectFolderGroup(groupsMap_.find(RDB_PKG_ID_DRIVER_CTRL)->second
                                               , playerIdStr
                                               , subGroupMap);

            createDataTable( *hdf5RdbDriverCtrl_
                            , enrichedRdbDriverCtrl
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbDriverCtrl_
                            , enrichedRdbDriverCtrl
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeDriverPerceptionEntry(const double simTime, const unsigned int simFrame, const RDB_DRIVER_PERCEPTION_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeDriverPerceptionEntry()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_DRIVER_PERCEPTION) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_DRIVER_PERCEPTION);

        uint64_t playerId = data.playerId;
        std::string playerIdStr = "Player_ID_" + toString(playerId);

        Hdf5RdbDriverPerception::ENRICHED_RDB_DRIVER_PERCEPTION enrichedRdbDriverPerception;
        Hdf5RdbDriverPerception::convertToModifiedStructure(data, simFrame, enrichedRdbDriverPerception);

        auto& subGroupMap = getGroupMapFromGroupsMap(subGroupsMap_, RDB_PKG_ID_DRIVER_PERCEPTION);
        if (subGroupMap.find(playerIdStr) == subGroupMap.end())
        {
            createNestedHdf5ObjectFolderGroup(groupsMap_.find(RDB_PKG_ID_DRIVER_PERCEPTION)->second
                                               , playerIdStr
                                               , subGroupMap);

            createDataTable( *hdf5RdbDriverPerception_
                            , enrichedRdbDriverPerception
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbDriverPerception_
                            , enrichedRdbDriverPerception
                             , subGroupMap.find(playerIdStr)->second
                             , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeEnvironmentData(const double simTime, const unsigned int simFrame, const RDB_ENVIRONMENT_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeEnvironmentData()" << std::endl;

        Hdf5RdbEnvironment::ENRICHED_RDB_ENVIRONMENT enrichedRdbEnvironment;
        Hdf5RdbEnvironment::convertToModifiedStructure(data, simFrame, enrichedRdbEnvironment);

        if (groupsMap_.count(RDB_PKG_ID_ENVIRONMENT) == 0)
        {
            createRootHdf5FolderGroup(RDB_PKG_ID_ENVIRONMENT);

            createDataTable( *hdf5RdbEnvironment_
                             , enrichedRdbEnvironment
                             , groupsMap_.find(RDB_PKG_ID_ENVIRONMENT)->second
                             , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbEnvironment_
                            , enrichedRdbEnvironment
                            , groupsMap_.find(RDB_PKG_ID_ENVIRONMENT)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeSensorObjectEntry(const double simTime, const unsigned int simFrame, const RDB_SENSOR_OBJECT_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeSensorObjectEntry()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_SENSOR_OBJECT) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_SENSOR_OBJECT);

        uint64_t playerId = data.id;
        std::string playerIdStr = "Player_ID_" + toString(playerId);

        Hdf5RdbSensorObject::ENRICHED_RDB_SENSOR_OBJECT enrichedRdbSensorObject;
        Hdf5RdbSensorObject::convertToModifiedStructure(data, simFrame, enrichedRdbSensorObject);

        auto& subGroupMap = getGroupMapFromGroupsMap(subGroupsMap_, RDB_PKG_ID_SENSOR_OBJECT);
        if (subGroupMap.find(playerIdStr) == subGroupMap.end())
        {
            createNestedHdf5ObjectFolderGroup(groupsMap_.find(RDB_PKG_ID_SENSOR_OBJECT)->second
                                               , playerIdStr
                                               , subGroupMap);

            createDataTable( *hdf5RdbSensorObject_
                            , enrichedRdbSensorObject
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbSensorObject_
                            , enrichedRdbSensorObject
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeSensorStateEntry(const double simTime, const unsigned int simFrame, const RDB_SENSOR_STATE_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeSensorStateEntry()" << std::endl;

        // SIMPLE SENSOR STATE
        Hdf5RdbSensorState::SIMPLE_RDB_SENSOR_STATE simpleSensorState;
        Hdf5RdbSensorState::convertToModifiedStructure(data, simFrame, simpleSensorState);

        if (groupsMap_.count(RDB_PKG_ID_SENSOR_STATE) == 0)
        {
            createRootHdf5FolderGroup(RDB_PKG_ID_SENSOR_STATE);

            createDataTable( *hdf5RdbSensorState_
                            , simpleSensorState
                            , groupsMap_.find(RDB_PKG_ID_SENSOR_STATE)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbSensorState_
                            , simpleSensorState
                            , groupsMap_.find(RDB_PKG_ID_SENSOR_STATE)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::updateSensorInfoFromSensorState(const RDB_MSG_t& rdbMessage, WriteHdf5Data::SensorInfo& sensorInfo)
    {
        if (verbose_) std::cout << "WriteHdf5Data::getSensorInfoFromSensorState()" << std::endl;

        unsigned int noElements = 0;

        RDB_SENSOR_STATE_t* data = reinterpret_cast<RDB_SENSOR_STATE_t*>(Framework::RDBHandler::getFirstEntry(&rdbMessage, RDB_PKG_ID_SENSOR_STATE, noElements, rdbMessage.entryHdr.flags));

        while (noElements)
        {
            // Update SensorInfo if necessary
            if (sensorInfo.playerId != data->hostId)
                sensorInfo.playerId = data->hostId;

            if (noElements--)
                ++data;
        }

    }

    void WriteHdf5Data::writeRoadStateEntry(const double simTime, const unsigned int simFrame, const RDB_ROAD_STATE_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeRoadStateData()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_ROAD_STATE) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_ROAD_STATE);

        uint64_t playerId = data.playerId;
        std::string playerIdStr = "Player_ID_" + toString(playerId);

        Hdf5RdbRoadState::ENRICHED_RDB_ROAD_STATE enrichedRdbRoadState;
        Hdf5RdbRoadState::convertToModifiedStructure(data, simFrame, enrichedRdbRoadState);

        auto& subGroupMap = getGroupMapFromGroupsMap(subGroupsMap_, RDB_PKG_ID_ROAD_STATE);
        if (subGroupMap.find(playerIdStr) == subGroupMap.end())
        {
            createNestedHdf5ObjectFolderGroup(groupsMap_.find(RDB_PKG_ID_ROAD_STATE)->second
                                               , playerIdStr
                                               , subGroupMap);

            createDataTable( *hdf5RdbRoadState_
                            , enrichedRdbRoadState
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbRoadState_
                            , enrichedRdbRoadState
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeLaneInfoEntry(const double simTime, const unsigned int simFrame, const RDB_LANE_INFO_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeLaneInfoEntry()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_LANE_INFO) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_LANE_INFO);

        uint64_t playerId = data.playerId;
        std::string playerIdStr = "Player_ID_" + toString(playerId);

        Hdf5RdbMessageLaneInfo::ENRICHED_RDB_LANE_INFO enrichedRdbLaneInfo;
        Hdf5RdbMessageLaneInfo::convertToModifiedStructure(data, simFrame, enrichedRdbLaneInfo);

        auto& subGroupMap = getGroupMapFromGroupsMap(subGroupsMap_, RDB_PKG_ID_LANE_INFO);
        if (subGroupMap.find(playerIdStr) == subGroupMap.end())
        {
            createNestedHdf5ObjectFolderGroup(groupsMap_.find(RDB_PKG_ID_LANE_INFO)->second
                                               , playerIdStr
                                               , subGroupMap);

            createDataTable( *hdf5RdbMessageLaneInfo_
                            , enrichedRdbLaneInfo
                            , subGroupMap.find(playerIdStr)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbMessageLaneInfo_
                            , enrichedRdbLaneInfo
                             , subGroupMap.find(playerIdStr)->second
                             , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeSyncEntry(const double simTime, const unsigned int simFrame, const RDB_SYNC_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeSyncEntry()" << std::endl;

        Hdf5RdbSync::ENRICHED_RDB_SYNC enrichedRdbSync;
        Hdf5RdbSync::convertToModifiedStructure(data, simFrame, enrichedRdbSync);

        if (groupsMap_.count(RDB_PKG_ID_SYNC) == 0)
        {
            createRootHdf5FolderGroup(RDB_PKG_ID_SYNC);

            createDataTable( *hdf5RdbSync_
                            , enrichedRdbSync
                            , groupsMap_.find(RDB_PKG_ID_SYNC)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbSync_
                            , enrichedRdbSync
                            , groupsMap_.find(RDB_PKG_ID_SYNC)->second
                            , RdbToHdf5Writer::DATA_STR);
        }
    }

    void WriteHdf5Data::writeCustomScoringEntry(const double simTime, const unsigned int simFrame, const RDB_CUSTOM_SCORING_t& data)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeCustomScoringEntry()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_CUSTOM_SCORING) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_CUSTOM_SCORING);

        uint64_t playerId = data.playerId;
        std::string playerIdStr = "Player_ID_" + toString(playerId);

        Hdf5RdbCustomScoring::ENRICHED_RDB_CUSTOM_SCORING enrichedRdbCustomScoring;
        Hdf5RdbCustomScoring::convertToModifiedStructure(data, simFrame, enrichedRdbCustomScoring);

        CheckVec* checkVec = getTableCreationCheckVec(RDB_PKG_ID_CUSTOM_SCORING);
        if (std::find(checkVec->begin(), checkVec->end(), playerId) == checkVec->end())
        {
            createDataTable( *hdf5RdbCustomScoring_
                            , enrichedRdbCustomScoring
                            , groupsMap_.find(RDB_PKG_ID_CUSTOM_SCORING)->second
                            , playerIdStr);

            checkVec->push_back(playerId);
        }
        else
        {
            appendDataTable( *hdf5RdbCustomScoring_
                            , enrichedRdbCustomScoring
                            , groupsMap_.find(RDB_PKG_ID_CUSTOM_SCORING)->second
                            , playerIdStr);
        }
    }

    void WriteHdf5Data::writeObjectStateEntry(const double simTime, const unsigned int simFrame, const RDB_OBJECT_STATE_t& data, const bool isExtended)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeObjectStateEntry()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_OBJECT_STATE) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_OBJECT_STATE);

        uint64_t playerId = data.base.id;
        std::string playerIdStr = "Player_ID_" + toString(playerId);

        Hdf5RdbMessageObjectStateBase::SIMPLE_RDB_OBJECT_STATE_BASE simpleObjectStateBase;
        Hdf5RdbMessageObjectStateBase::convertToModifiedStructure(data.base, simFrame, simpleObjectStateBase);

        if (groupsObjectStateMap_.count(playerIdStr) == 0)
        {
            createNestedHdf5ObjectFolderGroup(groupsMap_.find(RDB_PKG_ID_OBJECT_STATE)->second
                                               , playerIdStr
                                               , groupsObjectStateMap_);
            createDataTable(*hdf5RdbMessageObjectStateBase_
                                , simpleObjectStateBase
                                , groupsObjectStateMap_.find(playerIdStr)->second
                                , RdbToHdf5Writer::BASE_STR);
        }
        else
        {
            appendDataTable(*hdf5RdbMessageObjectStateBase_
                                , simpleObjectStateBase
                                , groupsObjectStateMap_.find(playerIdStr)->second
                                , RdbToHdf5Writer::BASE_STR);
        }


        if (isExtended)
        {
            Hdf5RdbMessageObjectStateExt::SIMPLE_RDB_OBJECT_STATE_EXTENDED simpleObjectStateExtended;
            Hdf5RdbMessageObjectStateExt::convertToModifiedStructure(data.ext, simFrame, simpleObjectStateExtended);

            CheckVec* checkVec = getTableCreationCheckVec(RDB_PKG_ID_OBJECT_STATE); // Used for ext package only
            if (std::find(checkVec->begin(), checkVec->end(), playerId) == checkVec->end())
            {
                createDataTable(*hdf5RdbMessageObjectStateExt_
                                  , simpleObjectStateExtended
                                  , groupsObjectStateMap_.find(playerIdStr)->second
                                  , RdbToHdf5Writer::EXT_STR);

                checkVec->push_back(playerId);
            }
            else
            {
                appendDataTable(*hdf5RdbMessageObjectStateExt_
                                , simpleObjectStateExtended
                                , groupsObjectStateMap_.find(playerIdStr)->second
                                , RdbToHdf5Writer::EXT_STR);
            }
        }
    }

    void WriteHdf5Data::writeEngineEntry(const double simTime, const unsigned int simFrame, const RDB_ENGINE_t& data, const bool isExtended)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeEngineEntry()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_ENGINE) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_ENGINE);

        uint64_t playerId = data.base.playerId;
        std::string playerIdStr = "Player_ID_" + toString(playerId);

        // ENGINE BASE
        Hdf5RdbMessageEngineBase::ENRICHED_RDB_ENGINE_BASE enrichedRdbEngineBase;
        Hdf5RdbMessageEngineBase::convertToModifiedStructure(data.base, simFrame, enrichedRdbEngineBase);

        if (groupsEngine_.count(playerIdStr) == 0)
        {
            createNestedHdf5ObjectFolderGroup( groupsMap_.find(RDB_PKG_ID_ENGINE)->second
                                               , playerIdStr
                                               , groupsEngine_);

            createDataTable( *hdf5RdbMessageEngineBase_
                                , enrichedRdbEngineBase
                                , groupsEngine_.find(playerIdStr)->second
                                , RdbToHdf5Writer::BASE_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbMessageEngineBase_
                                , enrichedRdbEngineBase
                                , groupsEngine_.find(playerIdStr)->second
                                , RdbToHdf5Writer::BASE_STR);
        }

        if (isExtended)
        {
            // ENGINE EXT
            Hdf5RdbMessageEngineExt::ENRICHED_RDB_ENGINE_EXT enrichedRdbEngineExt;
            Hdf5RdbMessageEngineExt::convertToModifiedStructure(data.ext, simFrame, enrichedRdbEngineExt);

            CheckVec* checkVec = getTableCreationCheckVec(RDB_PKG_ID_ENGINE); // Used for ext package only
            if (std::find(checkVec->begin(), checkVec->end(), playerId) == checkVec->end())
            {
                createDataTable( *hdf5RdbMessageEngineExt_
                                 , enrichedRdbEngineExt
                                 , groupsEngine_.find(playerIdStr)->second
                                 , RdbToHdf5Writer::EXT_STR);

                checkVec->push_back(playerId);
            }
            else
            {
                appendDataTable( *hdf5RdbMessageEngineExt_
                                 , enrichedRdbEngineExt
                                 , groupsEngine_.find(playerIdStr)->second
                                 , RdbToHdf5Writer::EXT_STR);
            }
        }
    }

    void WriteHdf5Data::writeWheelEntry(const double simTime, const unsigned int simFrame, const RDB_WHEEL_t& data, const bool isExtended)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeWheelEntry()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_WHEEL) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_WHEEL);

        uint64_t playerId = data.base.playerId;
        std::string playerIdStr = "Player_ID_" + toString(playerId);
        uint64_t wheelId = data.base.id; // TODO [BB] Maximum of 100 wheels per player
        std::string wheelIdStr = "Wheel_ID_" + toString(boost::numeric_cast<uint32_t>(wheelId));
        uint64_t wheelHdfId = (data.base.playerId * 100) + data.base.id; // TODO [BB] Maximum of 100 wheels per player

        // WHEEL BASE
        Hdf5RdbMessageWheelBase::ENRICHED_RDB_WHEEL_BASE enrichedWheelBase;
        Hdf5RdbMessageWheelBase::convertToModifiedStructure(data.base, simFrame, enrichedWheelBase);

        if (groupsWheel_.count(playerIdStr) == 0)
            createNestedHdf5ObjectFolderGroup( groupsMap_.find(RDB_PKG_ID_WHEEL)->second // WHEEL->Plx
                                , playerIdStr
                                , groupsWheel_);

        if (groupsWheelGroup_.count(wheelHdfId) == 0)
        {
            createNestedHdf5ObjectFolderGroup( groupsWheel_.find(playerIdStr)->second  // WHEEL->Plx->Whlx
                                , wheelIdStr
                                , wheelHdfId
                                , groupsWheelGroup_);

            createDataTable( *hdf5RdbMessageWheelBase_  // WHEEL->Plx->Whlx->base
                            , enrichedWheelBase
                            , groupsWheelGroup_.find(wheelHdfId)->second
                            , RdbToHdf5Writer::BASE_STR);
        }
        else
        {
            appendDataTable( *hdf5RdbMessageWheelBase_
                            , enrichedWheelBase
                            , groupsWheelGroup_.find(wheelHdfId)->second
                            , RdbToHdf5Writer::BASE_STR);
        }

        if (isExtended)
        {
            // WHEEL EXT
            Hdf5RdbMessageWheelExt::ENRICHED_RDB_WHEEL_EXT enrichedRdbWheelExt;
            Hdf5RdbMessageWheelExt::convertToModifiedStructure(data.ext, simFrame, enrichedRdbWheelExt);

            CheckVec* checkVec = getTableCreationCheckVec(RDB_PKG_ID_WHEEL); // Used for ext package only
            if (std::find(checkVec->begin(), checkVec->end(), playerId) == checkVec->end())
            {
                createDataTable( *hdf5RdbMessageWheelExt_
                                 , enrichedRdbWheelExt
                                 , groupsWheelGroup_.find(wheelHdfId)->second
                                 , RdbToHdf5Writer::EXT_STR);

                checkVec->push_back(wheelHdfId);
            }
            else
            {
                appendDataTable( *hdf5RdbMessageWheelExt_
                                 , enrichedRdbWheelExt
                                 , groupsWheelGroup_.find(wheelHdfId)->second
                                 , RdbToHdf5Writer::EXT_STR);
            }
        }
    }

    void WriteHdf5Data::writeTrafficLightEntry(const double simTime, const unsigned int simFrame, const RDB_TRAFFIC_LIGHT_t& data, const bool isExtended)
    {
        if (verbose_) std::cout << "WriteHdf5Data::writeTrafficLightData()" << std::endl;

        if (groupsMap_.count(RDB_PKG_ID_TRAFFIC_LIGHT) == 0)
            createRootHdf5FolderGroup(RDB_PKG_ID_TRAFFIC_LIGHT);

        uint64_t trafficLightId;
        std::string trafficLightIdStr;

        trafficLightId = data.base.id;
        trafficLightIdStr = "Traffic_Light_ID_" + toString(trafficLightId);

        //TRAFFIC LIGHT BASE
        Hdf5RdbTrafficLightBase::ENRICHED_RDB_TRAFFIC_LIGHT_BASE enrichedRdbTrafficLightBase;
        Hdf5RdbTrafficLightBase::convertToModifiedStructure(data.base, simFrame, enrichedRdbTrafficLightBase);

        if (groupsTrafficlight_.count(trafficLightIdStr) == 0)
        {
            createNestedHdf5ObjectFolderGroup( groupsMap_.find(RDB_PKG_ID_TRAFFIC_LIGHT)->second
                                               , trafficLightIdStr
                                               , groupsTrafficlight_);

            createDataTable( *hdf5RdbTrafficLightBase_
                            , enrichedRdbTrafficLightBase
                            , groupsTrafficlight_.find(trafficLightIdStr)->second
                            , RdbToHdf5Writer::BASE_STR);

        }
        else
        {
            appendDataTable( *hdf5RdbTrafficLightBase_
                                , enrichedRdbTrafficLightBase
                                , groupsTrafficlight_.find(trafficLightIdStr)->second
                                , RdbToHdf5Writer::BASE_STR);
        }

        //TRAFFIC LIGHT EXT
        if (isExtended)
        {
            Hdf5RdbTrafficLightExt::ENRICHED_RDB_TRAFFIC_LIGHT_EXT enrichedRdbTrafficLightExt;
            Hdf5RdbTrafficLightExt::convertToModifiedStructure(data.ext, simFrame, enrichedRdbTrafficLightExt);

            CheckVec* checkVec = getTableCreationCheckVec(RDB_PKG_ID_TRAFFIC_LIGHT); // Used for ext package only
            if (std::find(checkVec->begin(), checkVec->end(), trafficLightId) == checkVec->end())
            {
                createDataTable( *hdf5RdbTrafficLightExt_
                                 , enrichedRdbTrafficLightExt
                                 , groupsTrafficlight_.find(trafficLightIdStr)->second
                                 , RdbToHdf5Writer::EXT_STR);

                checkVec->push_back(trafficLightId);
            }
            else
            {
                appendDataTable( *hdf5RdbTrafficLightExt_
                                      , enrichedRdbTrafficLightExt
                                      , groupsTrafficlight_.find(trafficLightIdStr)->second
                                      , RdbToHdf5Writer::EXT_STR);
            }
        }
    }

    void WriteHdf5Data::setTableCreateAppend()
    {
        isHeaderTableCreated_ = false;
    }

    WriteHdf5Data::CheckVec* WriteHdf5Data::getTableCreationCheckVec(int64_t id)
    {
        auto it = tableCreationCheckMap_.find(id);
        RdbToHdf5Writer::WriteHdf5Data::CheckVec* checkVec = &(it->second);

        if (it == tableCreationCheckMap_.end())
        {
            auto ret = tableCreationCheckMap_.insert(CheckVecPair(id, CheckVec()));
            checkVec = &((ret.first)->second);
        }

        return checkVec;
    }
}
