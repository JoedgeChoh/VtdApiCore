#ifndef _RDB_HDF5_MESSAGE_RDB_LIGHT_SOURCE_BASE_H
#define _RDB_HDF5_MESSAGE_RDB_LIGHT_SOURCE_BASE_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbLightSourceBase
    {
        
    public:
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum  RDB_LIGHT_SOURCE_BASE_HDF5 {RDB_LIGHT_SOURCE_BASE_HDF5_ID, RDB_LIGHT_SOURCE_BASE_HDF5_TEMPLATE_ID, RDB_LIGHT_SOURCE_BASE_HDF5_STATE
                                          , RDB_LIGHT_SOURCE_BASE_HDF5_PLAYER_ID, RDB_LIGHT_SOURCE_BASE_HDF5_FLAGS, RDB_LIGHT_SOURCE_BASE_HDF5_SPARE0
                                          , RDB_LIGHT_SOURCE_BASE_HDF5_SPARE1, RDB_LIGHT_SOURCE_BASE_HDF5_NDATA}; // light source base
        
        Hdf5RdbLightSourceBase();

        virtual ~Hdf5RdbLightSourceBase();

        void initData();

    public:
        
        size_t dstOffset_[RDB_LIGHT_SOURCE_BASE_HDF5_NDATA];
        size_t dstSizes_[RDB_LIGHT_SOURCE_BASE_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_LIGHT_SOURCE_BASE_HDF5_NDATA];
        hid_t fieldType_[RDB_LIGHT_SOURCE_BASE_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t intArray32_;
        hsize_t dimsInt32_[1];
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
