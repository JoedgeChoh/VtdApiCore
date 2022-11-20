#ifndef _RDB_HDF5_MESSAGE_RDB_ROADMARK_H
#define _RDB_HDF5_MESSAGE_RDB_ROADMARK_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageRoadMark
    {
        
    public:

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_ROAD_MARK_HDF5 { RDB_ROAD_MARK_HDF5_PLAYER_ID, RDB_ROAD_MARK_HDF5_ID, RDB_ROAD_MARK_HDF5_PREV_ID
                                , RDB_ROAD_MARK_HDF5_NEXT_ID, RDB_ROAD_MARK_HDF5_LANE_ID, RDB_ROAD_MARK_HDF5_LATERAL_DIST
                                , RDB_ROAD_MARK_HDF5_YAW_REL, RDB_ROAD_MARK_HDF5_CURV_HOR, RDB_ROAD_MARK_HDF5_CURV_HOR_DOT
                                , RDB_ROAD_MARK_HDF5_START_DX, RDB_ROAD_MARK_HDF5_PREVIEW_DX, RDB_ROAD_MARK_HDF5_WIDTH
                                , RDB_ROAD_MARK_HDF5_HEIGHT, RDB_ROAD_MARK_HDF5_CURV_VERT, RDB_ROAD_MARK_HDF5_CURV_VERT_DOT
                                , RDB_ROAD_MARK_HDF5_TYPE, RDB_ROAD_MARK_HDF5_COLOR, RDB_ROAD_MARK_HDF5_NO_DATA_POINTS
                                , RDB_ROAD_MARK_HDF5_ROAD_ID, RDB_ROAD_MARK_HDF5_SPARE1, RDB_ROAD_MARK_HDF5_NDATA}; // Road mark
      
        Hdf5RdbMessageRoadMark();

        virtual ~Hdf5RdbMessageRoadMark(){}

        void initData();

    public:

        size_t dstOffset_[RDB_ROAD_MARK_HDF5_NDATA];
        size_t dstSizes_[RDB_ROAD_MARK_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_ROAD_MARK_HDF5_NDATA];
        hid_t fieldType_[RDB_ROAD_MARK_HDF5_NDATA];

        size_t tableSize_;

    private:

        uint32_t positionFrameId;
        char tableName[TABLE_NAME_SIZE];

    };
}

#endif
