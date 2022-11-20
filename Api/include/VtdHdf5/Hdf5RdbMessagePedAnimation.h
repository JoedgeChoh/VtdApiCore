#ifndef _RDB_HDF5_MESSAGE_RDB_PED_ANIMATION_H
#define _RDB_HDF5_MESSAGE_RDB_PED_ANIMATION_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessagePedAnimation
    {
        
    public:

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_PED_ANIMATION_HDF5 { RDB_PED_ANIMATION_HDF5_PLAYER_ID, RDB_PED_ANIMATION_HDF5_SPARE, RDB_PED_ANIMATION_HDF5_NO_COORDINATES
                                    , RDB_PED_ANIMATION_HDF5_DATA_SIZE, RDB_PED_ANIMATION_HDF5_NDATA}; // pad animation
        
        Hdf5RdbMessagePedAnimation();

        virtual ~Hdf5RdbMessagePedAnimation();

        void initData();

    public:
        
        size_t dstOffset_[RDB_PED_ANIMATION_HDF5_NDATA];
        size_t dstSizes_[RDB_PED_ANIMATION_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_PED_ANIMATION_HDF5_NDATA];
        hid_t fieldType_[RDB_PED_ANIMATION_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t uintArray32_;
        hsize_t dimsUInt32_[1];
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];

    };
}

#endif
