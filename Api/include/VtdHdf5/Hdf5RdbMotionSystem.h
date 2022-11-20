#ifndef _RDB_HDF5_MESSAGE_RDB_MOTION_SYSTEM_H
#define _RDB_HDF5_MESSAGE_RDB_MOTION_SYSTEM_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMotionSystem
    {
        
    public:
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_MOTION_SYSTEM_HDF5 {RDB_MOTION_SYSTEM_HDF5_PLAYER_ID, RDB_MOTION_SYSTEM_HDF5_FLAGS, RDB_MOTION_SYSTEM_HDF5_SUB_SYSTEM
                                     , RDB_MOTION_SYSTEM_HDF5_SPARE1, RDB_MOTION_SYSTEM_HDF5_SPARE, RDB_MOTION_SYSTEM_HDF5_NDATA}; // motion system
        
        Hdf5RdbMotionSystem();

        virtual ~Hdf5RdbMotionSystem();

        void initData();

    public:
        
        size_t dstOffset_[RDB_MOTION_SYSTEM_HDF5_NDATA];
        size_t dstSizes_[RDB_MOTION_SYSTEM_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_MOTION_SYSTEM_HDF5_NDATA];
        hid_t fieldType_[RDB_MOTION_SYSTEM_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t uintArray32_, uintArray8_;
        hsize_t dimsUInt32_[1], dimsUInt8_[1];
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
