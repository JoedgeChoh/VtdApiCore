#include <VtdHdf5/Hdf5RdbMessageRoadPos.h>

namespace RdbToHdf5Writer
{

        Hdf5RdbMessageRoadPos::Hdf5RdbMessageRoadPos() : tableSize_(RDB_ROAD_POS_HDF5_NDATA)
        {
            this->initData();
        }

        void Hdf5RdbMessageRoadPos::initData()
        {
            dstSize_ = sizeof(ENRICHED_RDB_ROAD_POS);

            dstOffset_[RDB_ROAD_POS_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_ROAD_POS, frameNumber);
            dstSizes_ [RDB_ROAD_POS_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_ROAD_POS::frameNumber);
            fieldType_[RDB_ROAD_POS_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_ROAD_POS_HDF5_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_ROAD_POS_HDF5_PLAYER_ID] = HOFFSET(ENRICHED_RDB_ROAD_POS, playerId);
            dstSizes_ [RDB_ROAD_POS_HDF5_PLAYER_ID] = sizeof(ENRICHED_RDB_ROAD_POS::playerId);
            fieldType_[RDB_ROAD_POS_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_ROAD_POS_HDF5_PLAYER_ID] = "playerId";

            dstOffset_[RDB_ROAD_POS_HDF5_ROAD_ID] = HOFFSET(ENRICHED_RDB_ROAD_POS, roadId);
            dstSizes_ [RDB_ROAD_POS_HDF5_ROAD_ID] = sizeof(ENRICHED_RDB_ROAD_POS::roadId);
            fieldType_[RDB_ROAD_POS_HDF5_ROAD_ID] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_ROAD_POS_HDF5_ROAD_ID] = "roadId";

            dstOffset_[RDB_ROAD_POS_HDF5_LANE_ID] = HOFFSET(ENRICHED_RDB_ROAD_POS, laneId);
            dstSizes_ [RDB_ROAD_POS_HDF5_LANE_ID] = sizeof(ENRICHED_RDB_ROAD_POS::laneId);
            fieldType_[RDB_ROAD_POS_HDF5_LANE_ID] = H5T_NATIVE_INT8;
            fieldNames_[RDB_ROAD_POS_HDF5_LANE_ID] = "laneId";

            dstOffset_[RDB_ROAD_POS_HDF5_FLAGS] = HOFFSET(ENRICHED_RDB_ROAD_POS, flags);
            dstSizes_ [RDB_ROAD_POS_HDF5_FLAGS] = sizeof(ENRICHED_RDB_ROAD_POS::flags);
            fieldType_[RDB_ROAD_POS_HDF5_FLAGS] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_ROAD_POS_HDF5_FLAGS] = "flags";

            dstOffset_[RDB_ROAD_POS_HDF5_ROAD_S] = HOFFSET(ENRICHED_RDB_ROAD_POS, roadS);
            dstSizes_ [RDB_ROAD_POS_HDF5_ROAD_S] = sizeof(ENRICHED_RDB_ROAD_POS::roadS);
            fieldType_[RDB_ROAD_POS_HDF5_ROAD_S] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_POS_HDF5_ROAD_S] = "roadS";

            dstOffset_[RDB_ROAD_POS_HDF5_ROAD_T] = HOFFSET(ENRICHED_RDB_ROAD_POS, roadT);
            dstSizes_ [RDB_ROAD_POS_HDF5_ROAD_T] = sizeof(ENRICHED_RDB_ROAD_POS::roadT);
            fieldType_[RDB_ROAD_POS_HDF5_ROAD_T] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_POS_HDF5_ROAD_T] = "roadT";

            dstOffset_[RDB_ROAD_POS_HDF5_LANE_OFFSET] = HOFFSET(ENRICHED_RDB_ROAD_POS, laneOffset);
            dstSizes_ [RDB_ROAD_POS_HDF5_LANE_OFFSET] = sizeof(ENRICHED_RDB_ROAD_POS::laneOffset);
            fieldType_[RDB_ROAD_POS_HDF5_LANE_OFFSET] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_POS_HDF5_LANE_OFFSET] = "laneOffset";

            dstOffset_[RDB_ROAD_POS_HDF5_HDG_REL] = HOFFSET(ENRICHED_RDB_ROAD_POS, hdgRel);
            dstSizes_ [RDB_ROAD_POS_HDF5_HDG_REL] = sizeof(ENRICHED_RDB_ROAD_POS::hdgRel);
            fieldType_[RDB_ROAD_POS_HDF5_HDG_REL] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_POS_HDF5_HDG_REL] = "hdgRel";

            dstOffset_[RDB_ROAD_POS_HDF5_PITCH_REL] = HOFFSET(ENRICHED_RDB_ROAD_POS, pitchRel);
            dstSizes_ [RDB_ROAD_POS_HDF5_PITCH_REL] = sizeof(ENRICHED_RDB_ROAD_POS::pitchRel);
            fieldType_[RDB_ROAD_POS_HDF5_PITCH_REL] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_POS_HDF5_PITCH_REL] = "pitchRel";

            dstOffset_[RDB_ROAD_POS_HDF5_ROLL_REL] = HOFFSET(ENRICHED_RDB_ROAD_POS, rollRel);
            dstSizes_ [RDB_ROAD_POS_HDF5_ROLL_REL] = sizeof(ENRICHED_RDB_ROAD_POS::rollRel);
            fieldType_[RDB_ROAD_POS_HDF5_ROLL_REL] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_POS_HDF5_ROLL_REL] = "rollRel";

            dstOffset_[RDB_ROAD_POS_HDF5_ROLL_REL] = HOFFSET(ENRICHED_RDB_ROAD_POS, rollRel);
            dstSizes_ [RDB_ROAD_POS_HDF5_ROLL_REL] = sizeof(ENRICHED_RDB_ROAD_POS::rollRel);
            fieldType_[RDB_ROAD_POS_HDF5_ROLL_REL] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_POS_HDF5_ROLL_REL] = "rollRel";

            dstOffset_[RDB_ROAD_POS_HDF5_ROAD_TYPE] = HOFFSET(ENRICHED_RDB_ROAD_POS, roadType);
            dstSizes_ [RDB_ROAD_POS_HDF5_ROAD_TYPE] = sizeof(ENRICHED_RDB_ROAD_POS::roadType);
            fieldType_[RDB_ROAD_POS_HDF5_ROAD_TYPE] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_ROAD_POS_HDF5_ROAD_TYPE] = "roadType";

            dstOffset_[RDB_ROAD_POS_HDF5_SPARE1] = HOFFSET(ENRICHED_RDB_ROAD_POS, spare1);
            dstSizes_ [RDB_ROAD_POS_HDF5_SPARE1] = sizeof(ENRICHED_RDB_ROAD_POS::spare1);
            fieldType_[RDB_ROAD_POS_HDF5_SPARE1] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_ROAD_POS_HDF5_SPARE1] = "spare1";

            dstOffset_[RDB_ROAD_POS_HDF5_SPARE2] = HOFFSET(ENRICHED_RDB_ROAD_POS, spare2);
            dstSizes_ [RDB_ROAD_POS_HDF5_SPARE2] = sizeof(ENRICHED_RDB_ROAD_POS::spare2);
            fieldType_[RDB_ROAD_POS_HDF5_SPARE2] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_ROAD_POS_HDF5_SPARE2] = "spare2";

            dstOffset_[RDB_ROAD_POS_HDF5_PATH_S] = HOFFSET(ENRICHED_RDB_ROAD_POS, pathS);
            dstSizes_ [RDB_ROAD_POS_HDF5_PATH_S] = sizeof(ENRICHED_RDB_ROAD_POS::pathS);
            fieldType_[RDB_ROAD_POS_HDF5_PATH_S] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_POS_HDF5_PATH_S] = "pathS";
        }

        void Hdf5RdbMessageRoadPos::convertToModifiedStructure(const RDB_ROAD_POS_t &data, const uint32_t frameNumber, Hdf5RdbMessageRoadPos::ENRICHED_RDB_ROAD_POS &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.playerId = data.playerId;
            modifiedData.roadId = data.roadId;
            modifiedData.laneId = data.laneId;
            modifiedData.flags = data.flags;
            modifiedData.roadS = data.roadS;
            modifiedData.roadT = data.roadT;
            modifiedData.laneOffset = data.laneOffset;
            modifiedData.hdgRel = data.hdgRel;
            modifiedData.pitchRel = data.pitchRel;
            modifiedData.rollRel = data.rollRel;
            modifiedData.roadType = data.roadType;
            modifiedData.spare1 = data.spare1;
            modifiedData.spare2 = data.spare2;
            modifiedData.pathS = data.pathS;
        }
}

