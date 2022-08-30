#ifndef _RDB_HDF5_MESSAGE_RDB_SYNC_H
#define _RDB_HDF5_MESSAGE_RDB_SYNC_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbSync
    {
        
    public:

        struct ENRICHED_RDB_SYNC
        {
            uint32_t frameNumber;
            uint32_t mask;          /**< mask of required sync sources which are fulfilled by this sender            @unit _                        @version 0x0100 */
            uint32_t cmdMask;       /**< mask of commands included in the sync message                               @unit RDB_SYNC_CMD             @version 0x010E */
            double   systemTime;    /**< system time                                                                 @unit s                        @version 0x0118 */
        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_SYNC_HDF5 {    RDB_SYNC_HDF5_FRAME_NUMBER,
                                RDB_SYNC_HDF5_MASK,
                                RDB_SYNC_HDF5_CMD_MASK,
                                RDB_SYNC_HDF5_SYSTEM_TIME,
                                RDB_SYNC_HDF5_NDATA};

        Hdf5RdbSync();

        virtual ~Hdf5RdbSync(){}

        void initData();

        static void convertToModifiedStructure(const RDB_SYNC_t& data, const uint32_t frameNumber, ENRICHED_RDB_SYNC& modifiedData);

    public:
        
        size_t dstOffset_[RDB_SYNC_HDF5_NDATA];
        size_t dstSizes_[RDB_SYNC_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_SYNC_HDF5_NDATA];
        hid_t fieldType_[RDB_SYNC_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;

    };
}

#endif
