#ifndef _RDB_HDF5_MESSAGE_RDB_CONTACT_POINT_H
#define _RDB_HDF5_MESSAGE_RDB_CONTACT_POINT_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbContactPoint
    {
        
    public:
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum  RDB_CONTACT_POINT_HDF5 {  RDB_CONTACT_POINT_HDF5_ID,  RDB_CONTACT_POINT_HDF5_FLAGS,  RDB_CONTACT_POINT_HDF5_FRICTION
                                        ,  RDB_CONTACT_POINT_HDF5_PLAYER_ID,  RDB_CONTACT_POINT_HDF5_SPARE1, RDB_CONTACT_POINT_HDF5_NDATA}; // contact_point
        
        Hdf5RdbContactPoint();

        virtual ~Hdf5RdbContactPoint() {}

        void initData();

    public:
        
        size_t dstOffset_[RDB_CONTACT_POINT_HDF5_NDATA];
        size_t dstSizes_[RDB_CONTACT_POINT_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_CONTACT_POINT_HDF5_NDATA];
        hid_t fieldType_[RDB_CONTACT_POINT_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;

    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
