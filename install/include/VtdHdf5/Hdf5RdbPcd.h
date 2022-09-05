#ifndef _RDB_HDF5_MESSAGE_RDB_CAMERA_H
#define _RDB_HDF5_MESSAGE_RDB_CAMERA_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>


namespace RdbToHdf5Writer
{
    class Hdf5_Rdb_Pcd
    {

    public:
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum  RDB_CAMERA_HDF5 { RDB_CAMERA_HDF5_ID, RDB_CAMERA_HDF5_WIDTH, RDB_CAMERA_HDF5_HEIGHT
                                , RDB_CAMERA_HDF5_SPARE0, RDB_CAMERA_HDF5_CLIP_NEAR, RDB_CAMERA_HDF5_CLIP_FAR
                                , RDB_CAMERA_HDF5_FOCAL_X, RDB_CAMERA_HDF5_FOCAL_Y, RDB_CAMERA_HDF5_PRINCIPAL_X
                                , RDB_CAMERA_HDF5_PRINCIPAL_Y, RDB_CAMERA_HDF5_SPARE1, RDB_CAMERA_HDF5_NDATA}; // camera
        
        Hdf5_Rdb_Pcd ();

        virtual ~Hdf5_Rdb_Pcd ();

        void initData();

    public:
        
        size_t dstOffset_[RDB_CAMERA_HDF5_NDATA];
        size_t dstSizes_[RDB_CAMERA_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_CAMERA_HDF5_NDATA];
        hid_t fieldType_[RDB_CAMERA_HDF5_NDATA];
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
