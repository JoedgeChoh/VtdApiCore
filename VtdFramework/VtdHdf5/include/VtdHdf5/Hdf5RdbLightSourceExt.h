#ifndef _RDB_HDF5_MESSAGE_RDB_LIGHT_SOURCE_EXT_H
#define _RDB_HDF5_MESSAGE_RDB_LIGHT_SOURCE_EXT_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbLightSourceExt
    {
        
    public:
        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_LIGHT_SOURCE_EXT_HDF5 { RDB_LIGHT_SOURCE_EXT_HDF5_NEAR_FAR,  RDB_LIGHT_SOURCE_EXT_HDF5_FRUSTUM_LRBT,  RDB_LIGHT_SOURCE_EXT_HDF5_INTENSITY
                                       , RDB_LIGHT_SOURCE_EXT_HDF5_ATTEN,  RDB_LIGHT_SOURCE_EXT_HDF5_SPARE1, RDB_LIGHT_SOURCE_EXT_HDF5_NDATA}; // light source ext
        
        Hdf5RdbLightSourceExt();

        virtual ~Hdf5RdbLightSourceExt();

        void initData();

    public:
        
        size_t dstOffset_[RDB_LIGHT_SOURCE_EXT_HDF5_NDATA];
        size_t dstSizes_[RDB_LIGHT_SOURCE_EXT_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_LIGHT_SOURCE_EXT_HDF5_NDATA];
        hid_t fieldType_[RDB_LIGHT_SOURCE_EXT_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t intArray32_, arrayFloat2_, arrayFloat3_, arrayFloat4_;
        hsize_t dimsInt32_[1], dimsFloat2_[1], dimsFloat3_[1], dimsFloat4_[1];
        
    private:

        uint32_t positionFrameId;
        char tableName[TABLE_NAME_SIZE];
    };
}

#endif
