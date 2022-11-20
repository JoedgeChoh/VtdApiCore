#ifndef _RDB_HDF5_MESSAGE_RDB_OBJECT_STATE_EXT_H
#define _RDB_HDF5_MESSAGE_RDB_OBJECT_STATE_EXT_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageObjectStateExt
    {
        
        public:

        struct SIMPLE_RDB_OBJECT_STATE_EXTENDED
        {
            uint32_t frameNumber;
            float traveledDist;
            uint32_t spare[3];

            // "speed" sub group RDB_COORD
            double   speed_x;       /**< x position                                                @unit m                                @version 0x0100 */
            double   speed_y;       /**< y position                                                @unit m                                @version 0x0100 */
            double   speed_z;       /**< z position                                                @unit m                                @version 0x0100 */
            float    speed_h;       /**< heading angle                                             @unit rad                              @version 0x0100 */
            float    speed_p;       /**< pitch angle                                               @unit rad                              @version 0x0100 */
            float    speed_r;       /**< roll angle                                                @unit rad                              @version 0x0100 */
            uint8_t  speed_flags;   /**< co-ordinate flags                                         @unit @link RDB_OBJECT_STATE_EXT_SPEED_FLAG @endlink    @version 0x0100 */
            uint8_t  speed_type;    /**< co-ordinate system type identifier                        @unit @link RDB_OBJECT_STATE_EXT_SPEED_TYPE @endlink    @version 0x0100 */
            uint16_t speed_system;  /**< unique ID of the corresponding (user) co-ordinate system  @unit _                                @version 0x0100 */

            // "accel" sub group RDB_COORD
            double   accel_x;       /**< x position                                                @unit m                                @version 0x0100 */
            double   accel_y;       /**< y position                                                @unit m                                @version 0x0100 */
            double   accel_z;       /**< z position                                                @unit m                                @version 0x0100 */
            float    accel_h;       /**< heading angle                                             @unit rad                              @version 0x0100 */
            float    accel_p;       /**< pitch angle                                               @unit rad                              @version 0x0100 */
            float    accel_r;       /**< roll angle                                                @unit rad                              @version 0x0100 */
            uint8_t  accel_flags;   /**< co-ordinate flags                                         @unit @link RDB_OBJECT_STATE_EXT_SPEED_FLAG @endlink    @version 0x0100 */
            uint8_t  accel_type;    /**< co-ordinate system type identifier                        @unit @link RDB_OBJECT_STATE_EXT_SPEED_TYPE @endlink    @version 0x0100 */
            uint16_t accel_system;  /**< unique ID of the corresponding (user) co-ordinate system  @unit _                                @version 0x0100 */

        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_OBJECT_STATE_EXT_HDF5 {RDB_OBJECT_STATE_EXT_HDF5_FRAME_NUMBER,
                                        RDB_OBJECT_STATE_EXT_HDF5_TRAVEL_DIST,
                                        RDB_OBJECT_STATE_EXT_HDF5_SPARE,
                                        RDB_OBJECT_STATE_EXT_SPEED_HDF5_X,
                                        RDB_OBJECT_STATE_EXT_SPEED_HDF5_Y,
                                        RDB_OBJECT_STATE_EXT_SPEED_HDF5_Z,
                                        RDB_OBJECT_STATE_EXT_SPEED_HDF5_H,
                                        RDB_OBJECT_STATE_EXT_SPEED_HDF5_P,
                                        RDB_OBJECT_STATE_EXT_SPEED_HDF5_R,
                                        RDB_OBJECT_STATE_EXT_SPEED_HDF5_FLAGS,
                                        RDB_OBJECT_STATE_EXT_SPEED_HDF5_TYPE,
                                        RDB_OBJECT_STATE_EXT_SPEED_HDF5_SYSTEM,
                                        RDB_OBJECT_STATE_EXT_ACCEL_HDF5_X,
                                        RDB_OBJECT_STATE_EXT_ACCEL_HDF5_Y,
                                        RDB_OBJECT_STATE_EXT_ACCEL_HDF5_Z,
                                        RDB_OBJECT_STATE_EXT_ACCEL_HDF5_H,
                                        RDB_OBJECT_STATE_EXT_ACCEL_HDF5_P,
                                        RDB_OBJECT_STATE_EXT_ACCEL_HDF5_R,
                                        RDB_OBJECT_STATE_EXT_ACCEL_HDF5_FLAGS,
                                        RDB_OBJECT_STATE_EXT_ACCEL_HDF5_TYPE,
                                        RDB_OBJECT_STATE_EXT_ACCEL_HDF5_SYSTEM,
                                        RDB_OBJECT_STATE_EXT_HDF5_NDATA};

        /**
        *	Constructor
        */        
        Hdf5RdbMessageObjectStateExt();

        virtual ~Hdf5RdbMessageObjectStateExt();

        static void convertToModifiedStructure(const RDB_OBJECT_STATE_EXT_t& data, const uint32_t frameNumber, SIMPLE_RDB_OBJECT_STATE_EXTENDED& modifiedData);

        void initData();

    public:
        
        hsize_t  dims_[1];
        size_t dstOffset_[RDB_OBJECT_STATE_EXT_HDF5_NDATA];
        size_t dstSizes_[RDB_OBJECT_STATE_EXT_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_OBJECT_STATE_EXT_HDF5_NDATA];
        hid_t fieldType_[RDB_OBJECT_STATE_EXT_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t unitArray_;

    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];

    };
}

#endif
