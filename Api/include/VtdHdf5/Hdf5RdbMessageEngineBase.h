#ifndef _RDB_HDF5_MESSAGE_RDB_ENGINE_BASE_H
#define _RDB_HDF5_MESSAGE_RDB_ENGINE_BASE_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageEngineBase
    {
        
    public:

        struct ENRICHED_RDB_ENGINE_BASE
        {
            uint32_t frameNumber;
            uint32_t playerId;                    /**< unique ID of the player                          @unit _                         @version 0x0100 */
            float    rps;                         /**< current rotation speed                           @unit 1/s                       @version 0x0100 */
            float    load;                        /**< engine load (throttle position)                  @unit [0.0..1.0]                @version 0x0100 */
            uint32_t spare1[2];                   /**< reserved for future use                          @unit _                         @version 0x0100 */
        };

        static const size_t TABLE_NAME_SIZE = 32;
            
        enum RDB_ENGINE_BASE_HDF5 { RDB_ENGINE_BASE_HDF5_FRAME_NUMBER,
                                    RDB_ENGINE_BASE_HDF5_PLAYER_ID,
                                    RDB_ENGINE_BASE_HDF5_RPS,
                                    RDB_ENGINE_BASE_HDF5_LOAD,
                                    RDB_ENGINE_BASE_HDF5_SPARE1,
                                    RDB_ENGINE_BASE_HDF5_NDATA};
        
        Hdf5RdbMessageEngineBase();

        virtual ~Hdf5RdbMessageEngineBase();

        void initData();

        static void convertToModifiedStructure(const RDB_ENGINE_BASE_t& data, const uint32_t frameNumber, ENRICHED_RDB_ENGINE_BASE& modifiedData);

    public:
        
        hsize_t  dims[1];
        size_t dstOffset_[RDB_ENGINE_BASE_HDF5_NDATA];
        size_t dstSizes_[RDB_ENGINE_BASE_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_ENGINE_BASE_HDF5_NDATA];
        hid_t fieldType_[RDB_ENGINE_BASE_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t uintArray;

    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
