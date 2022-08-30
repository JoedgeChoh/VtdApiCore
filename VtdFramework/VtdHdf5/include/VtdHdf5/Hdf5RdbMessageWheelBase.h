#ifndef _RDB_HDF5_MESSAGE_RDB_WHEEL_BASE_H
#define _RDB_HDF5_MESSAGE_RDB_WHEEL_BASE_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{

    class Hdf5RdbMessageWheelBase
    {
        
    public:

        struct ENRICHED_RDB_WHEEL_BASE
        {
            uint32_t frameNumber;
            uint32_t playerId;                    /**< ID of the player to which the wheel belongs      @unit _                             @version 0x0100 */
            uint8_t  id;                          /**< ID of the wheel within the player                @unit @link RDB_WHEEL_ID @endlink   @version 0x0100 */
            uint8_t  flags;                       /**< wheel status flags (e.g. for sound )             @unit @link RDB_WHEEL_FLAG @endlink @version 0x0114 */
            uint8_t  spare0[2];                   /**< reserved for future use                          @unit _                             @version 0x0100 */
            float    radiusStatic;                /**< static tire radius                               @unit m                             @version 0x0100 */
            float    springCompression;           /**< compression of spring                            @unit m                             @version 0x0100 */
            float    rotAngle;                    /**< angle of rotation                                @unit rad                           @version 0x0100 */
            float    slip;                        /**< slip factor [0.0..1.0]                           @unit _                             @version 0x0100 */
            float    steeringAngle;               /**< steering angle                                   @unit rad                           @version 0x0100 */
            uint32_t spare1[4];                   /**< reserved for future use                          @unit _                             @version 0x0100 */
        };
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_WHEEL_BASE_HDF5 {  RDB_WHEEL_BASE_HDF5_FRAME_NUMBER,
                                    RDB_WHEEL_BASE_HDF5_PLAYER_ID,
                                    RDB_WHEEL_BASE_HDF5_ID,
                                    RDB_WHEEL_BASE_HDF5_FLAGS,
                                    RDB_WHEEL_BASE_HDF5_SPARE0,
                                    RDB_WHEEL_BASE_HDF5_RADIUS_STATIC,
                                    RDB_WHEEL_BASE_HDF5_SPRING_COMPRESSION,
                                    RDB_WHEEL_BASE_HDF5_ROT_ANGLE,
                                    RDB_WHEEL_BASE_HDF5_SLIP,
                                    RDB_WHEEL_BASE_HDF5_STEERING_ANGLE,
                                    RDB_WHEEL_BASE_HDF5_SPARE1,
                                    RDB_WHEEL_BASE_HDF5_NDATA};
        
        Hdf5RdbMessageWheelBase();

        virtual ~Hdf5RdbMessageWheelBase();

        void initData();

        static void convertToModifiedStructure(const RDB_WHEEL_BASE_t& data, const uint32_t frameNumber, ENRICHED_RDB_WHEEL_BASE& modifiedData);

    public:
        
        size_t dstOffset_[RDB_WHEEL_BASE_HDF5_NDATA];
        size_t dstSizes_[RDB_WHEEL_BASE_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_WHEEL_BASE_HDF5_NDATA];
        hid_t fieldType_[RDB_WHEEL_BASE_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t uintArray8_, uintArray32_;
        hsize_t  dimsUInt8_[1], dimsUInt32_[1];
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];

    };
}

#endif
