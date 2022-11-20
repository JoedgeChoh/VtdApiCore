#ifndef _RDB_HDF5_MESSAGE_COORD_SYSTEM_H
#define _RDB_HDF5_MESSAGE_COORD_SYSTEM_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageCoordSystem
    {
        
        public:

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_COORD_SYSTEM_HDF5 { RDB_COORD_SYSTEM_HDF5_ID, RDB_COORD_SYSTEM_HDF5_SPARE, RDB_COORD_SYSTEM_NDATA}; // Coordinate system
      
        Hdf5RdbMessageCoordSystem();

        virtual ~Hdf5RdbMessageCoordSystem(){}

        void initData();

    public:

        size_t dstOffset_[RDB_COORD_SYSTEM_NDATA];
        size_t dstSizes_[RDB_COORD_SYSTEM_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_COORD_SYSTEM_NDATA];
        hid_t fieldType_[RDB_COORD_SYSTEM_NDATA];

        size_t tableSize_;

    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
