#ifndef _RDB_HDF5_MESSAGE_RDB_IG_FRAME_H
#define _RDB_HDF5_MESSAGE_RDB_IG_FRAME_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbIgFrame
    {
        
    public:
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_IG_FRAME_HDF5 {RDB_IG_FRAME_HDF5_DELTA_T, RDB_IG_FRAME_HDF5_FRAME_NO, RDB_IG_FRAME_HDF5_SPARE
                                , RDB_IG_FRAME_HDF5_NDATA}; // ig frame
        
        Hdf5RdbIgFrame();

        virtual ~Hdf5RdbIgFrame();

        void initData();

    public:
        
        size_t dstOffset_[RDB_IG_FRAME_HDF5_NDATA];
        size_t dstSizes_[RDB_IG_FRAME_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_IG_FRAME_HDF5_NDATA];
        hid_t fieldType_[RDB_IG_FRAME_HDF5_NDATA];
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
