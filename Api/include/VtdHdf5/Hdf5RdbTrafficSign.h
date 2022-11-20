#ifndef _RDB_HDF5_MESSAGE_RDB_TRAFFIC_SIGN_H
#define _RDB_HDF5_MESSAGE_RDB_TRAFFIC_SIGN_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbTrafficSign
    {
        
    public:
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum  RDB_TRAFFIC_SIGN_HDF5 {  RDB_TRAFFIC_SIGN_ID, RDB_TRAFFIC_SIGN_PLAYER_ID, RDB_TRAFFIC_SIGN_ROAD_DIST
                                       , RDB_TRAFFIC_SIGN_TYPE, RDB_TRAFFIC_SIGN_SUB_TYPE, RDB_TRAFFIC_SIGN_VALUE
                                       , RDB_TRAFFIC_SIGN_STATE, RDB_TRAFFIC_SIGN_READABILITY, RDB_TRAFFIC_SIGN_OCCLUSION
                                       , RDB_TRAFFIC_SIGN_SPARE0, RDB_TRAFFIC_SIGN_ADD_ON_ID, RDB_TRAFFIC_SIGN_MIN_LANE
                                       , RDB_TRAFFIC_SIGN_MAX_LANE, RDB_TRAFFIC_SIGN_SPARE, RDB_TRAFFIC_SIGN_NDATA}; // traffic sign
        
        Hdf5RdbTrafficSign();

        virtual ~Hdf5RdbTrafficSign(){}

        void initData();

    public:
        
        size_t dstOffset_[RDB_TRAFFIC_SIGN_NDATA];
        size_t dstSizes_[RDB_TRAFFIC_SIGN_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames[RDB_TRAFFIC_SIGN_NDATA];
        hid_t fieldType_[RDB_TRAFFIC_SIGN_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        
    private:

        uint32_t positionFrameId;
        char tableName[TABLE_NAME_SIZE];
    };
}

#endif
