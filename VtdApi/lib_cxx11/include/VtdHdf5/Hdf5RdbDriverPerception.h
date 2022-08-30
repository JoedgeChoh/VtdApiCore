#ifndef _RDB_HDF5_MESSAGE_RDB_DRIVER_PERCEPTION_H
#define _RDB_HDF5_MESSAGE_RDB_DRIVER_PERCEPTION_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbDriverPerception
    {
        
    public:

        struct ENRICHED_RDB_DRIVER_PERCEPTION
        {
            uint32_t frameNumber;
            uint32_t playerId;         /**< unique player ID to which the controls apply         @unit _                                            @version 0x0100 */
            float    speedFromRules;   /**< speed from rules (i.e. road, signs etc.)             @unit m/s                                          @version 0x0100 */
            float    distToSpeed;      /**< distance to next speed from rules (-1.0 to disable)  @unit m                                            @version 0x0100 */
            float    spare0[4];        /**< just some spares                                     @unit _                                            @version 0x0100 */
            uint32_t flags;            /**< input flags (turn dir etc.)                          @unit @link RDB_DRIVER_PERCEPTION_FLAG @endlink    @version 0x0100 */
            uint32_t spare[4];         /**< some spares for future use                           @unit _                                            @version 0x0100 */
        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_DRIVER_PERCEPTION_HDF5 {   RDB_DRIVER_PERCEPTION_HDF5_FRAME_NUMBER,
                                            RDB_DRIVER_PERCEPTION_HDF5_PLAYER_ID,
                                            RDB_DRIVER_PERCEPTION_HDF5_SPEED_FROM_RULES,
                                            RDB_DRIVER_PERCEPTION_HDF5_DIST_TO_SPEED,
                                            RDB_DRIVER_PERCEPTION_HDF5_SPARE0,
                                            RDB_DRIVER_PERCEPTION_HDF5_FLAGS,
                                            RDB_DRIVER_PERCEPTION_HDF5_SPARE,
                                            RDB_DRIVER_PERCEPTION_HDF5_NDATA};

        Hdf5RdbDriverPerception();

        virtual ~Hdf5RdbDriverPerception();

        void initData();

        static void convertToModifiedStructure(const RDB_DRIVER_PERCEPTION_t& data, const uint32_t frameNumber, ENRICHED_RDB_DRIVER_PERCEPTION& modifiedData);

    public:
        
        size_t dstOffset_[RDB_DRIVER_PERCEPTION_HDF5_NDATA];
        size_t dstSizes_[RDB_DRIVER_PERCEPTION_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_DRIVER_PERCEPTION_HDF5_NDATA];
        hid_t fieldType_[RDB_DRIVER_PERCEPTION_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t uintArray32_, floatArray_;
        hsize_t dimsUInt32_[1], dimsFloat_[1];
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
