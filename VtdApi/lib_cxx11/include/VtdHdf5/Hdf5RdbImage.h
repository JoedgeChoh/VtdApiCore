#ifndef _RDB_HDF5_MESSAGE_RDB_IMAGE_H
#define _RDB_HDF5_MESSAGE_RDB_IMAGE_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbImage
    {
        
    public:
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum  RDB_IMAGE_HDF5 {RDB_IMAGE_HDF5_ID, RDB_IMAGE_HDF5_WIDTH, RDB_IMAGE_HDF5_HEIGHT
                              , RDB_IMAGE_HDF5_PIXEL_SIZE, RDB_IMAGE_HDF5_PIXEL_FORMAT, RDB_IMAGE_HDF5_CAMERA_ID
                              , RDB_IMAGE_HDF5_IMG_SIZE, RDB_IMAGE_HDF5_COLOR, RDB_IMAGE_HDF5_SPARE1, RDB_IMAGE_HDF5_NDATA}; // image
        
        Hdf5RdbImage();

        virtual ~Hdf5RdbImage ();

        void initData();

    public:
        
        size_t dstOffset_[RDB_IMAGE_HDF5_NDATA];
        size_t dstSizes_[RDB_IMAGE_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_IMAGE_HDF5_NDATA];
        hid_t fieldType_[RDB_IMAGE_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t uintArray8_, uintArray32_;
        hsize_t  dimsUInt8_[1], dimsUInt32_[1];
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
