#ifndef _RDB_HDF5_MESSAGE_RDB_FUNCTION_H
#define _RDB_HDF5_MESSAGE_RDB_FUNCTION_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbFunction
    {
        
    public:
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_FUNCTION_HDF5 {RDB_FUNCTION_HDF5_ID, RDB_FUNCTION_HDF5_TYPE, RDB_FUNCTION_HDF5_DIMENSION
                                , RDB_FUNCTION_HDF5_SPARE, RDB_FUNCTION_HDF5_DATA_SIZE, RDB_FUNCTION_HDF5_SPARE1
                                , RDB_FUNCTION_HDF5_NDATA}; // function
        
        Hdf5RdbFunction();

        virtual ~Hdf5RdbFunction();

        void initData();

    public:
        
        size_t dstOffset_[RDB_FUNCTION_HDF5_NDATA];
        size_t dstSizes_[RDB_FUNCTION_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_FUNCTION_HDF5_NDATA];
        hid_t fieldType_[RDB_FUNCTION_HDF5_NDATA];
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
