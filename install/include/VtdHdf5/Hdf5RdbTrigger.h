#ifndef _RDB_HDF5_MESSAGE_RDB_TRIGGER_H
#define _RDB_HDF5_MESSAGE_RDB_TRIGGER_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbTrigger
    {
        
    public:

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_TRIGGER_HDF5 { RDB_TRIGGER_HDF5_DELAT_T, RDB_TRIGGER_HDF5_FRAME_NO, RDB_TRIGGER_HDF5_FEATURES
                              , RDB_TRIGGER_HDF5_SPARE0, RDB_TRIGGER_HDF5_NDATA}; // trigger
        
        Hdf5RdbTrigger();

        virtual ~Hdf5RdbTrigger();

        void initData();


    public:
        
        size_t dstOffset_[RDB_TRIGGER_HDF5_NDATA];
        size_t dstSizes_[RDB_TRIGGER_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_TRIGGER_HDF5_NDATA];
        hid_t fieldType_[RDB_TRIGGER_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;

    };
}

#endif
