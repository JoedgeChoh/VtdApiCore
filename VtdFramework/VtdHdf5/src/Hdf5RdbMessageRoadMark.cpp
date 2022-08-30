#include <VtdHdf5/Hdf5RdbMessageRoadMark.h>

namespace RdbToHdf5Writer
{

        Hdf5RdbMessageRoadMark::Hdf5RdbMessageRoadMark() : tableSize_(RDB_ROAD_MARK_HDF5_NDATA)
        {
            this->initData();
        }

        void Hdf5RdbMessageRoadMark::initData()
        {
         dstSize_ = sizeof(RDB_ROADMARK_t);

            dstOffset_[RDB_ROAD_MARK_HDF5_PLAYER_ID] = HOFFSET(RDB_ROADMARK_t, playerId);
            dstSizes_ [RDB_ROAD_MARK_HDF5_PLAYER_ID] = sizeof(RDB_ROADMARK_t::playerId);
            fieldType_[RDB_ROAD_MARK_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_ROAD_MARK_HDF5_PLAYER_ID] = "playerId";

            dstOffset_[RDB_ROAD_MARK_HDF5_ID] = HOFFSET(RDB_ROADMARK_t, id);
            dstSizes_ [RDB_ROAD_MARK_HDF5_ID] = sizeof(RDB_ROADMARK_t::id);
            fieldType_[RDB_ROAD_MARK_HDF5_ID] = H5T_NATIVE_INT8;
            fieldNames_[RDB_ROAD_MARK_HDF5_ID] = "id";

            dstOffset_[RDB_ROAD_MARK_HDF5_PREV_ID] = HOFFSET(RDB_ROADMARK_t, prevId);
            dstSizes_ [RDB_ROAD_MARK_HDF5_PREV_ID] = sizeof(RDB_ROADMARK_t::prevId);
            fieldType_[RDB_ROAD_MARK_HDF5_PREV_ID] = H5T_NATIVE_INT8;
            fieldNames_[RDB_ROAD_MARK_HDF5_PREV_ID] = "prevId";

            dstOffset_[RDB_ROAD_MARK_HDF5_NEXT_ID] = HOFFSET(RDB_ROADMARK_t, nextId);
            dstSizes_ [RDB_ROAD_MARK_HDF5_NEXT_ID] = sizeof(RDB_ROADMARK_t::nextId);
            fieldType_[RDB_ROAD_MARK_HDF5_NEXT_ID] = H5T_NATIVE_INT8;
            fieldNames_[RDB_ROAD_MARK_HDF5_NEXT_ID] = "nextId";

            dstOffset_[RDB_ROAD_MARK_HDF5_LANE_ID] = HOFFSET(RDB_ROADMARK_t, laneId);
            dstSizes_ [RDB_ROAD_MARK_HDF5_LANE_ID] = sizeof(RDB_ROADMARK_t::laneId);
            fieldType_[RDB_ROAD_MARK_HDF5_LANE_ID] = H5T_NATIVE_INT8;
            fieldNames_[RDB_ROAD_MARK_HDF5_LANE_ID] = "laneId";

            dstOffset_[RDB_ROAD_MARK_HDF5_LATERAL_DIST] = HOFFSET(RDB_ROADMARK_t, lateralDist);
            dstSizes_ [RDB_ROAD_MARK_HDF5_LATERAL_DIST] = sizeof(RDB_ROADMARK_t::lateralDist);
            fieldType_[RDB_ROAD_MARK_HDF5_LATERAL_DIST] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_MARK_HDF5_LATERAL_DIST] = "lateralDist";

            dstOffset_[RDB_ROAD_MARK_HDF5_YAW_REL] = HOFFSET(RDB_ROADMARK_t, yawRel);
            dstSizes_ [RDB_ROAD_MARK_HDF5_YAW_REL] = sizeof(RDB_ROADMARK_t::yawRel);
            fieldType_[RDB_ROAD_MARK_HDF5_YAW_REL] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_MARK_HDF5_YAW_REL] = "yawRel";

            dstOffset_[RDB_ROAD_MARK_HDF5_CURV_HOR] = HOFFSET(RDB_ROADMARK_t, curvHor);
            dstSizes_ [RDB_ROAD_MARK_HDF5_CURV_HOR] = sizeof(RDB_ROADMARK_t::curvHor);
            fieldType_[RDB_ROAD_MARK_HDF5_CURV_HOR] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_ROAD_MARK_HDF5_CURV_HOR] = "curvHor";

            dstOffset_[RDB_ROAD_MARK_HDF5_CURV_HOR_DOT] = HOFFSET(RDB_ROADMARK_t, curvHorDot);
            dstSizes_ [RDB_ROAD_MARK_HDF5_CURV_HOR_DOT] = sizeof(RDB_ROADMARK_t::curvHorDot);
            fieldType_[RDB_ROAD_MARK_HDF5_CURV_HOR_DOT] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_ROAD_MARK_HDF5_CURV_HOR_DOT] = "curvHorDot";

            dstOffset_[RDB_ROAD_MARK_HDF5_START_DX] = HOFFSET(RDB_ROADMARK_t, startDx);
            dstSizes_ [RDB_ROAD_MARK_HDF5_START_DX] = sizeof(RDB_ROADMARK_t::startDx);
            fieldType_[RDB_ROAD_MARK_HDF5_START_DX] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_MARK_HDF5_START_DX] = "startDx";

            dstOffset_[RDB_ROAD_MARK_HDF5_PREVIEW_DX]= HOFFSET(RDB_ROADMARK_t, previewDx);
            dstSizes_ [RDB_ROAD_MARK_HDF5_PREVIEW_DX] = sizeof(RDB_ROADMARK_t::previewDx);
            fieldType_[RDB_ROAD_MARK_HDF5_PREVIEW_DX] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_MARK_HDF5_PREVIEW_DX] = "previewDx";

            dstOffset_[RDB_ROAD_MARK_HDF5_WIDTH]= HOFFSET(RDB_ROADMARK_t, width);
            dstSizes_ [RDB_ROAD_MARK_HDF5_WIDTH] = sizeof(RDB_ROADMARK_t::width);
            fieldType_[RDB_ROAD_MARK_HDF5_WIDTH] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_MARK_HDF5_WIDTH] = "width";

            dstOffset_[RDB_ROAD_MARK_HDF5_HEIGHT]= HOFFSET(RDB_ROADMARK_t, height);
            dstSizes_ [RDB_ROAD_MARK_HDF5_HEIGHT] = sizeof(RDB_ROADMARK_t::height);
            fieldType_[RDB_ROAD_MARK_HDF5_HEIGHT] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ROAD_MARK_HDF5_HEIGHT] = "height";

            dstOffset_[RDB_ROAD_MARK_HDF5_CURV_VERT]= HOFFSET(RDB_ROADMARK_t, curvVert);
            dstSizes_ [RDB_ROAD_MARK_HDF5_CURV_VERT] = sizeof(RDB_ROADMARK_t::curvVert);
            fieldType_[RDB_ROAD_MARK_HDF5_CURV_VERT] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_ROAD_MARK_HDF5_CURV_VERT] = "curvVert";

            dstOffset_[RDB_ROAD_MARK_HDF5_CURV_VERT_DOT]= HOFFSET(RDB_ROADMARK_t, curvVertDot);
            dstSizes_ [RDB_ROAD_MARK_HDF5_CURV_VERT_DOT] = sizeof(RDB_ROADMARK_t::curvVertDot);
            fieldType_[RDB_ROAD_MARK_HDF5_CURV_VERT_DOT] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_ROAD_MARK_HDF5_CURV_VERT_DOT] = "curvVertDot";

            dstOffset_[RDB_ROAD_MARK_HDF5_TYPE]= HOFFSET(RDB_ROADMARK_t, type);
            dstSizes_ [RDB_ROAD_MARK_HDF5_TYPE] = sizeof(RDB_ROADMARK_t::type);
            fieldType_[RDB_ROAD_MARK_HDF5_TYPE] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_ROAD_MARK_HDF5_TYPE] = "type";

            dstOffset_[RDB_ROAD_MARK_HDF5_COLOR]= HOFFSET(RDB_ROADMARK_t, color);
            dstSizes_ [RDB_ROAD_MARK_HDF5_COLOR] = sizeof(RDB_ROADMARK_t::color);
            fieldType_[RDB_ROAD_MARK_HDF5_COLOR] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_ROAD_MARK_HDF5_COLOR] = "color";

            dstOffset_[RDB_ROAD_MARK_HDF5_NO_DATA_POINTS]= HOFFSET(RDB_ROADMARK_t, noDataPoints);
            dstSizes_ [RDB_ROAD_MARK_HDF5_NO_DATA_POINTS] = sizeof(RDB_ROADMARK_t::noDataPoints);
            fieldType_[RDB_ROAD_MARK_HDF5_NO_DATA_POINTS] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_ROAD_MARK_HDF5_NO_DATA_POINTS] = "noDataPoints";

            dstOffset_[RDB_ROAD_MARK_HDF5_ROAD_ID]= HOFFSET(RDB_ROADMARK_t, roadId);
            dstSizes_ [RDB_ROAD_MARK_HDF5_ROAD_ID] = sizeof(RDB_ROADMARK_t::roadId);
            fieldType_[RDB_ROAD_MARK_HDF5_ROAD_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_ROAD_MARK_HDF5_ROAD_ID] = "roadId";

            dstOffset_[RDB_ROAD_MARK_HDF5_SPARE1]= HOFFSET(RDB_ROADMARK_t, spare1);
            dstSizes_ [RDB_ROAD_MARK_HDF5_SPARE1] = sizeof(RDB_ROADMARK_t::spare1);
            fieldType_[RDB_ROAD_MARK_HDF5_SPARE1] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_ROAD_MARK_HDF5_SPARE1] = "spare1";
        }

}

