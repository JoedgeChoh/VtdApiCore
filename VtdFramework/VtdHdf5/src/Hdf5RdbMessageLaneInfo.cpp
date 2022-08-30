#include <VtdHdf5/Hdf5RdbMessageLaneInfo.h>

namespace RdbToHdf5Writer
{

        Hdf5RdbMessageLaneInfo::Hdf5RdbMessageLaneInfo() : tableSize_(RDB_LANE_INFO_NDATA)
        {
            this->initData();
        }

        void Hdf5RdbMessageLaneInfo::initData()
        {
            dstSize_ = sizeof(ENRICHED_RDB_LANE_INFO);

            dstOffset_[RDB_LANE_INFO_FRAME_NUMBER] = HOFFSET(  ENRICHED_RDB_LANE_INFO, frameNumber);
            dstSizes_ [RDB_LANE_INFO_FRAME_NUMBER] = sizeof(ENRICHED_RDB_LANE_INFO::frameNumber);
            fieldType_[RDB_LANE_INFO_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_LANE_INFO_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_LANE_INFO_ROAD_ID] = HOFFSET(  ENRICHED_RDB_LANE_INFO, roadId);
            dstSizes_ [RDB_LANE_INFO_ROAD_ID] = sizeof(ENRICHED_RDB_LANE_INFO::roadId);
            fieldType_[RDB_LANE_INFO_ROAD_ID] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_LANE_INFO_ROAD_ID] = "roadId";

            dstOffset_[RDB_LANE_INFO_ID] = HOFFSET(  ENRICHED_RDB_LANE_INFO, id);
            dstSizes_ [RDB_LANE_INFO_ID] = sizeof(ENRICHED_RDB_LANE_INFO::id);
            fieldType_[RDB_LANE_INFO_ID] = H5T_NATIVE_INT8;
            fieldNames_[RDB_LANE_INFO_ID] = "id";

            dstOffset_[RDB_LANE_INFO_NEIGHBOR_MASK] = HOFFSET(  ENRICHED_RDB_LANE_INFO, neighborMask);
            dstSizes_ [RDB_LANE_INFO_NEIGHBOR_MASK] = sizeof(ENRICHED_RDB_LANE_INFO::neighborMask);
            fieldType_[RDB_LANE_INFO_NEIGHBOR_MASK] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_LANE_INFO_NEIGHBOR_MASK] = "neighborMask";

            dstOffset_[RDB_LANE_INFO_LEFT_LANE_ID] = HOFFSET(  ENRICHED_RDB_LANE_INFO, leftLaneId);
            dstSizes_ [RDB_LANE_INFO_LEFT_LANE_ID] = sizeof(ENRICHED_RDB_LANE_INFO::leftLaneId);
            fieldType_[RDB_LANE_INFO_LEFT_LANE_ID] = H5T_NATIVE_INT8;
            fieldNames_[RDB_LANE_INFO_LEFT_LANE_ID] = "leftLaneId";

            dstOffset_[RDB_LANE_INFO_RIGHT_LANE_ID] = HOFFSET(  ENRICHED_RDB_LANE_INFO, rightLaneId);
            dstSizes_ [RDB_LANE_INFO_RIGHT_LANE_ID] = sizeof(ENRICHED_RDB_LANE_INFO::rightLaneId);
            fieldType_[RDB_LANE_INFO_RIGHT_LANE_ID] = H5T_NATIVE_INT8;
            fieldNames_[RDB_LANE_INFO_RIGHT_LANE_ID] = "rightLaneId";

            dstOffset_[RDB_LANE_INFO_BORDER_TYPE] = HOFFSET(  ENRICHED_RDB_LANE_INFO, borderType);
            dstSizes_ [RDB_LANE_INFO_BORDER_TYPE] = sizeof(ENRICHED_RDB_LANE_INFO::borderType);
            fieldType_[RDB_LANE_INFO_BORDER_TYPE] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_LANE_INFO_BORDER_TYPE] = "borderType";

            dstOffset_[RDB_LANE_INFO_MATERIAL] = HOFFSET(  ENRICHED_RDB_LANE_INFO, material);
            dstSizes_ [RDB_LANE_INFO_MATERIAL] = sizeof(ENRICHED_RDB_LANE_INFO::material);
            fieldType_[RDB_LANE_INFO_MATERIAL] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_LANE_INFO_MATERIAL] = "material";

            dstOffset_[RDB_LANE_INFO_STATUS] = HOFFSET(  ENRICHED_RDB_LANE_INFO, status);
            dstSizes_ [RDB_LANE_INFO_STATUS] = sizeof(ENRICHED_RDB_LANE_INFO::status);
            fieldType_[RDB_LANE_INFO_STATUS] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_LANE_INFO_STATUS] = "status";

            dstOffset_[RDB_LANE_INFO_TYPE] = HOFFSET(  ENRICHED_RDB_LANE_INFO, type);
            dstSizes_ [RDB_LANE_INFO_TYPE] = sizeof(ENRICHED_RDB_LANE_INFO::type);
            fieldType_[RDB_LANE_INFO_TYPE] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_LANE_INFO_TYPE] = "type";

            dstOffset_[RDB_LANE_INFO_WIDTH] = HOFFSET(  ENRICHED_RDB_LANE_INFO, width);
            dstSizes_ [RDB_LANE_INFO_WIDTH] = sizeof(ENRICHED_RDB_LANE_INFO::width);
            fieldType_[RDB_LANE_INFO_WIDTH] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_LANE_INFO_WIDTH] = "width";

            dstOffset_[RDB_LANE_INFO_CURV_VERT] = HOFFSET(  ENRICHED_RDB_LANE_INFO, curvVert);
            dstSizes_ [RDB_LANE_INFO_CURV_VERT] = sizeof(ENRICHED_RDB_LANE_INFO::curvVert);
            fieldType_[RDB_LANE_INFO_CURV_VERT] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_LANE_INFO_CURV_VERT] = "curvVert";

            dstOffset_[RDB_LANE_INFO_CURV_VERT_DOT] = HOFFSET(  ENRICHED_RDB_LANE_INFO, curvVertDot);
            dstSizes_ [RDB_LANE_INFO_CURV_VERT_DOT] = sizeof(ENRICHED_RDB_LANE_INFO::curvVertDot);
            fieldType_[RDB_LANE_INFO_CURV_VERT_DOT] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_LANE_INFO_CURV_VERT_DOT] = "curvVertDot";

            dstOffset_[RDB_LANE_INFO_CURV_HOR] = HOFFSET(  ENRICHED_RDB_LANE_INFO, curvHor);
            dstSizes_ [RDB_LANE_INFO_CURV_HOR] = sizeof(ENRICHED_RDB_LANE_INFO::curvHor);
            fieldType_[RDB_LANE_INFO_CURV_HOR] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_LANE_INFO_CURV_HOR] = "curvHor";

            dstOffset_[RDB_LANE_INFO_CURV_HOR_DOT] = HOFFSET(  ENRICHED_RDB_LANE_INFO, curvHorDot);
            dstSizes_ [RDB_LANE_INFO_CURV_HOR_DOT] = sizeof(ENRICHED_RDB_LANE_INFO::curvHorDot);
            fieldType_[RDB_LANE_INFO_CURV_HOR_DOT] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_LANE_INFO_CURV_HOR_DOT] = "curvHorDot";

            dstOffset_[RDB_LANE_INFO_PLAYER_ID] = HOFFSET(  ENRICHED_RDB_LANE_INFO, playerId);
            dstSizes_ [RDB_LANE_INFO_PLAYER_ID] = sizeof(ENRICHED_RDB_LANE_INFO::playerId);
            fieldType_[RDB_LANE_INFO_PLAYER_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_LANE_INFO_PLAYER_ID] = "playerId";

            dstOffset_[RDB_LANE_INFO_SPARE1] = HOFFSET(  ENRICHED_RDB_LANE_INFO, spare1);
            dstSizes_ [RDB_LANE_INFO_SPARE1] = sizeof(ENRICHED_RDB_LANE_INFO::spare1);
            fieldType_[RDB_LANE_INFO_SPARE1] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_LANE_INFO_SPARE1] = "spare1";
        }

        void Hdf5RdbMessageLaneInfo::convertToModifiedStructure(const RDB_LANE_INFO_t &data, const uint32_t frameNumber, Hdf5RdbMessageLaneInfo::ENRICHED_RDB_LANE_INFO &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.roadId = data.roadId;
            modifiedData.id = data.id;
            modifiedData.neighborMask = data.neighborMask;
            modifiedData.leftLaneId = data.leftLaneId;
            modifiedData.rightLaneId = data.rightLaneId;
            modifiedData.borderType = data.borderType;
            modifiedData.material = data.material;
            modifiedData.status = data.status;
            modifiedData.type = data.type;
            modifiedData.width = data.width;
            modifiedData.curvVert = data.curvVert;
            modifiedData.curvVertDot = data.curvVertDot;
            modifiedData.curvHor = data.curvHor;
            modifiedData.curvHorDot = data.curvHorDot;
            modifiedData.playerId = data.playerId;
            modifiedData.spare1 = data.spare1;
        }
}

