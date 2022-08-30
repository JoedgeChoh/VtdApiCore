#ifndef _RDB_HDF5_MESSAGE_HEADER_H
#define _RDB_HDF5_MESSAGE_HEADER_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>
#include <string>
#include <map>

#include "RDBHDF5lib.h"

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageHeader
    {

    public:

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_MSG_HDR_HDF5 { RDB_MSG_HDR_HDF5_MAGIC_NO, RDB_MSG_HDR_HDF5_VERSION, RDB_MSG_HDR_HDF5_HEADER_SIZE
                              , RDB_MSG_HDR_HDF5_DATA_SIZE, RDB_MSG_HDR_HDF5_FRAME_NO, RDB_MSG_HDR_HDF5_SIM_TIME
                              , RDB_MSG_HDR_HDF5_NDATA}; // Message header enumerator
      

        Hdf5RdbMessageHeader();

        virtual ~Hdf5RdbMessageHeader(){}

        void initData();

        Hdf5RdbMessageHeader* getHeader(){return this;}

    public:

        size_t dstOffset_[RDB_MSG_HDR_HDF5_NDATA];
        size_t dstSizes_[RDB_MSG_HDR_HDF5_NDATA];
        size_t dstSize_;
        size_t tableSize_;
        // Define field information
        const char* fieldNames_[RDB_MSG_HDR_HDF5_NDATA];
        hid_t fieldType_[RDB_MSG_HDR_HDF5_NDATA];

    protected:

        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
