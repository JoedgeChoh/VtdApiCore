#ifndef _RDB_HDF5_MESSAGE_RDB_FUNCTION_H
#define _RDB_HDF5_MESSAGE_RDB_FUNCTION_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5_Rdb_Proxy
    {
        
    public:
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_PROXY_HDF5 {RDB_PROXY_HDF5_PROTOCOL, RDB_PROXY_HDF5_PKG_ID, RDB_PROXY_HDF5_SPARE
                             , RDB_PROXY_HDF5_DATA_SIZE, RDB_PROXY_HDF5_NDATA}; // proxy
        
        Hdf5_Rdb_Proxy();

        virtual ~Hdf5_Rdb_Proxy();

        void initData();

    public:
        
        size_t dstOffset_[RDB_PROXY_HDF5_NDATA];
        size_t dstSizes_[RDB_PROXY_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_PROXY_HDF5_NDATA];
        hid_t fieldType_[RDB_PROXY_HDF5_NDATA];
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
