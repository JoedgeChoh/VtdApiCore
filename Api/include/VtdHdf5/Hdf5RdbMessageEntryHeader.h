#ifndef _RDB_HDF5_MESSAGE_ENTRY_HEADER_H
#define _RDB_HDF5_MESSAGE_ENTRY_HEADER_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageEntryHeader
    {
        
    public:

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_MSG_ENTRY_HDR_HDF5 { RDB_MSG_ENTRY_HDR_HDF5_HEADER_SIZE, RDB_MSG_ENTRY_HDR_HDF5_DATA_SIZE, RDB_MSG_ENTRY_HDR_HDF5_ELEMENT_SIZE
                                    , RDB_MSG_ENTRY_HDR_HDF5_PKG_ID, RDB_MSG_ENTRY_HDR_HDF5_FLAGS, RDB_MSG_ENTRY_HDR_HDF5_NDATA}; // Message header entry enumerator
      
        Hdf5RdbMessageEntryHeader();

        virtual ~Hdf5RdbMessageEntryHeader() {}

        void initData();

        void writeData(const RDB_MSG_t& RDBMessage);

    public:

        size_t dstOffset_[RDB_MSG_ENTRY_HDR_HDF5_NDATA];
        size_t dstSizes_[RDB_MSG_ENTRY_HDR_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_MSG_ENTRY_HDR_HDF5_NDATA];
        hid_t fieldType_[RDB_MSG_ENTRY_HDR_HDF5_NDATA];
        size_t tableSize_;

    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
