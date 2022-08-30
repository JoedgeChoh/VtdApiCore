#include <VtdHdf5/Hdf5RdbRoadState.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbRoadState::Hdf5RdbRoadState() : tableSize_(RDB_ROAD_STATE_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbRoadState::~Hdf5RdbRoadState()
        {
            // have to be close memory leak
            H5Tclose(intArray32_);
        }

        void Hdf5RdbRoadState ::initData()
        {
           dimsInt32_[0] = sizeof(ENRICHED_RDB_ROAD_STATE::spare2) / sizeof(int32_t);
           intArray32_ = H5Tarray_create(H5T_NATIVE_INT32, 1, dimsInt32_);
            
           dstSize_ = sizeof(ENRICHED_RDB_ROAD_STATE);

           dstOffset_[RDB_ROAD_STATE_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_ROAD_STATE , frameNumber);
           dstSizes_ [RDB_ROAD_STATE_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_ROAD_STATE::frameNumber);
           fieldType_[RDB_ROAD_STATE_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_ROAD_STATE_HDF5_FRAME_NUMBER] = "frameNumber";

           dstOffset_[RDB_ROAD_STATE_HDF5_PLAYER_ID] = HOFFSET(ENRICHED_RDB_ROAD_STATE , playerId);
           dstSizes_ [RDB_ROAD_STATE_HDF5_PLAYER_ID] = sizeof(ENRICHED_RDB_ROAD_STATE::playerId);
           fieldType_[RDB_ROAD_STATE_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_ROAD_STATE_HDF5_PLAYER_ID] = "playerId";

           dstOffset_[RDB_ROAD_STATE_HDF5_WHEEL_ID] = HOFFSET(ENRICHED_RDB_ROAD_STATE , wheelId);
           dstSizes_ [RDB_ROAD_STATE_HDF5_WHEEL_ID] = sizeof(ENRICHED_RDB_ROAD_STATE::wheelId);
           fieldType_[RDB_ROAD_STATE_HDF5_WHEEL_ID] = H5T_NATIVE_INT8;
           fieldNames_[RDB_ROAD_STATE_HDF5_WHEEL_ID] = "wheelId";

           dstOffset_[RDB_ROAD_STATE_HDF5_SPARE0] = HOFFSET(ENRICHED_RDB_ROAD_STATE, spare0);
           dstSizes_ [RDB_ROAD_STATE_HDF5_SPARE0] = sizeof(ENRICHED_RDB_ROAD_STATE ::spare0);
           fieldType_[RDB_ROAD_STATE_HDF5_SPARE0] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_ROAD_STATE_HDF5_SPARE0] = "spare0";

           dstOffset_[RDB_ROAD_STATE_HDF5_SPARE1] = HOFFSET(ENRICHED_RDB_ROAD_STATE, spare1);
           dstSizes_ [RDB_ROAD_STATE_HDF5_SPARE1] = sizeof(ENRICHED_RDB_ROAD_STATE ::spare1);
           fieldType_[RDB_ROAD_STATE_HDF5_SPARE1] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_ROAD_STATE_HDF5_SPARE1] = "spare1";

           dstOffset_[RDB_ROAD_STATE_HDF5_ROAD_ID] = HOFFSET(ENRICHED_RDB_ROAD_STATE, roadId);
           dstSizes_ [RDB_ROAD_STATE_HDF5_ROAD_ID] = sizeof(ENRICHED_RDB_ROAD_STATE ::roadId);
           fieldType_[RDB_ROAD_STATE_HDF5_ROAD_ID] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_ROAD_STATE_HDF5_ROAD_ID] = "roadId";

           dstOffset_[RDB_ROAD_STATE_HDF5_DEFAULT_SPEED] = HOFFSET(ENRICHED_RDB_ROAD_STATE, defaultSpeed);
           dstSizes_ [RDB_ROAD_STATE_HDF5_DEFAULT_SPEED] = sizeof(ENRICHED_RDB_ROAD_STATE::defaultSpeed);
           fieldType_[RDB_ROAD_STATE_HDF5_DEFAULT_SPEED] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_ROAD_STATE_HDF5_DEFAULT_SPEED] = "defaultSpeed";

           dstOffset_[RDB_ROAD_STATE_HDF5_WATER_LEVEL] = HOFFSET(ENRICHED_RDB_ROAD_STATE, waterLevel);
           dstSizes_ [RDB_ROAD_STATE_HDF5_WATER_LEVEL] = sizeof(ENRICHED_RDB_ROAD_STATE::waterLevel);
           fieldType_[RDB_ROAD_STATE_HDF5_WATER_LEVEL] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_ROAD_STATE_HDF5_WATER_LEVEL] = "waterLevel";

           dstOffset_[RDB_ROAD_STATE_HDF5_EVENT_MASK] = HOFFSET(ENRICHED_RDB_ROAD_STATE, eventMask);
           dstSizes_ [RDB_ROAD_STATE_HDF5_EVENT_MASK] = sizeof(ENRICHED_RDB_ROAD_STATE::eventMask);
           fieldType_[RDB_ROAD_STATE_HDF5_EVENT_MASK] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_ROAD_STATE_HDF5_EVENT_MASK] = "eventMask";

           dstOffset_[RDB_ROAD_STATE_HDF5_DIST_TO_JUNC] = HOFFSET(ENRICHED_RDB_ROAD_STATE, distToJunc);
           dstSizes_ [RDB_ROAD_STATE_HDF5_DIST_TO_JUNC] = sizeof(ENRICHED_RDB_ROAD_STATE::distToJunc);
           fieldType_[RDB_ROAD_STATE_HDF5_DIST_TO_JUNC] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_ROAD_STATE_HDF5_DIST_TO_JUNC] = "distToJunc";

           dstOffset_[RDB_ROAD_STATE_HDF5_SPARE2] = HOFFSET(ENRICHED_RDB_ROAD_STATE , spare2);
           dstSizes_ [RDB_ROAD_STATE_HDF5_SPARE2] = sizeof(ENRICHED_RDB_ROAD_STATE ::spare2);
           fieldType_[RDB_ROAD_STATE_HDF5_SPARE2] = intArray32_;
           fieldNames_[RDB_ROAD_STATE_HDF5_SPARE2] = "spare2";

        }
        void Hdf5RdbRoadState::convertToModifiedStructure(const RDB_ROAD_STATE_t &data, const uint32_t frameNumber, Hdf5RdbRoadState::ENRICHED_RDB_ROAD_STATE &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.playerId = data.playerId;
            modifiedData.wheelId = data.wheelId;
            modifiedData.spare0 = data.spare0;
            modifiedData.spare1 = data.spare1;
            modifiedData.roadId = data.roadId;
            modifiedData.defaultSpeed = data.defaultSpeed;
            modifiedData.waterLevel = data.waterLevel;
            modifiedData.eventMask = data.eventMask;
            modifiedData.distToJunc = data.distToJunc;
            modifiedData.spare2[0] = data.spare2[0];
            modifiedData.spare2[1] = data.spare2[1];
            modifiedData.spare2[2] = data.spare2[2];
            modifiedData.spare2[3] = data.spare2[3];
            modifiedData.spare2[4] = data.spare2[4];
            modifiedData.spare2[5] = data.spare2[5];
            modifiedData.spare2[6] = data.spare2[6];
            modifiedData.spare2[7] = data.spare2[7];
            modifiedData.spare2[8] = data.spare2[8];
            modifiedData.spare2[9] = data.spare2[9];
            modifiedData.spare2[10] = data.spare2[10];
        }
}

