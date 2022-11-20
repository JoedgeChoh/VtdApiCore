#ifndef _RDB_HDF5_MESSAGE_RDB_DRIVER_CTRL_H
#define _RDB_HDF5_MESSAGE_RDB_DRIVER_CTRL_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbDriverCtrl
    {
        
    public:

        struct ENRICHED_RDB_DRIVER_CTRL
        {
            uint32_t frameNumber;
            uint32_t playerId;         /**< unique player ID to which the controls apply         @unit _                                        @version 0x0100 */
            float    steeringWheel;    /**< steering wheel angle                                 @unit rad                                      @version 0x0100 */
            float    steeringSpeed;    /**< steering speed                                       @unit rad/s                                    @version 0x0100 */
            float    throttlePedal;    /**< throttle pedal position                              @unit [0.0..1.0]                               @version 0x0100 */
            float    brakePedal;       /**< brake pedal position                                 @unit [0.0..1.0]                               @version 0x0100 */
            float    clutchPedal;      /**< clutch pedal position                                @unit [0.0..1.0]                               @version 0x0100 */
            float    accelTgt;         /**< desired acceleration                                 @unit m/s2                                     @version 0x0100 */
            float    steeringTgt;      /**< desired steering angle at wheels                     @unit rad                                      @version 0x0100 */        /* TODO: maybe this should become the turn rate */
            double   curvatureTgt;     /**< desired resulting curvature of the lateral motion    @unit 1/m                                      @version 0x0100 */
            float    steeringTorque;   /**< torque at steering wheel                             @unit Nm                                       @version 0x0100 */
            float    engineTorqueTgt;  /**< target engine torque                                 @unit Nm                                       @version 0x0100 */
            float    speedTgt;         /**< target speed                                         @unit m/s                                      @version 0x0100 */
            uint8_t  gear;             /**< desired gear box position                            @unit @link RDB_GEAR_BOX_POS          @endlink @version 0x0100 */
            uint8_t  sourceId;         /**< unique number of the source providing this input     @unit @link RDB_DRIVER_SOURCE         @endlink @version 0x010E */
            uint8_t  spare0[2];        /**< some spares for future use                           @unit _                                        @version 0x0100 */
            uint32_t validityFlags;    /**< flags which of the above inputs are valid            @unit @link RDB_DRIVER_INPUT_VALIDITY @endlink @version 0x0100 */
            uint32_t flags;            /**< input flags (indicator etc.)                         @unit @link RDB_DRIVER_FLAG           @endlink @version 0x0100 */
            uint32_t mockupInput0;     /**< flags resulting from mockup buttons, part 1          @unit @link RDB_MOCKUP_INPUT0         @endlink @version 0x010A */
            uint32_t mockupInput1;     /**< flags resulting from mockup buttons, part 2          @unit @link RDB_MOCKUP_INPUT1         @endlink @version 0x010A */
            uint32_t mockupInput2;     /**< flags resulting from mockup buttons, part 3          @unit @link RDB_MOCKUP_INPUT2         @endlink @version 0x010A */
            uint32_t spare;            /**< some spare  for future use                           @unit _                                        @version 0x010A */
        };
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_DRIVER_CTRL_HDF5 { RDB_DRIVER_CTRL_HDF5_FRAME_NUMBER,
                                    RDB_DRIVER_CTRL_HDF5_PLAYER_ID,
                                    RDB_DRIVER_CTRL_HDF5_STEERING_WHEEL,
                                    RDB_DRIVER_CTRL_HDF5_STEERING_SPEED,
                                    RDB_DRIVER_CTRL_HDF5_THROTTLE_PEDAL,
                                    RDB_DRIVER_CTRL_HDF5_BRAKE_PEDAL,
                                    RDB_DRIVER_CTRL_HDF5_CLUTCH_PEDAL,
                                    RDB_DRIVER_CTRL_HDF5_ACCEL_TGT,
                                    RDB_DRIVER_CTRL_HDF5_STEERING_TGT,
                                    RDB_DRIVER_CTRL_HDF5_CURVATURE_TGT,
                                    RDB_DRIVER_CTRL_HDF5_STEERING_TORQUE,
                                    RDB_DRIVER_CTRL_HDF5_ENGINE_TORQUE_TGT,
                                    RDB_DRIVER_CTRL_HDF5_SPEED_TGT,
                                    RDB_DRIVER_CTRL_HDF5_GEAR,
                                    RDB_DRIVER_CTRL_HDF5_SOURCE_ID,
                                    RDB_DRIVER_CTRL_HDF5_SPARE0,
                                    RDB_DRIVER_CTRL_HDF5_VALIDITY_FLAGS,
                                    RDB_DRIVER_CTRL_HDF5_FLAGS,
                                    RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_0,
                                    RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_1,
                                    RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_2,
                                    RDB_DRIVER_CTRL_HDF5_SPARE,
                                    RDB_DRIVER_CTRL_HDF5_NDATA};

        Hdf5RdbDriverCtrl();

        virtual ~Hdf5RdbDriverCtrl();

        void initData();

        static void convertToModifiedStructure(const RDB_DRIVER_CTRL_t& data, const uint32_t frameNumber, ENRICHED_RDB_DRIVER_CTRL& modifiedData);

    public:
        
        size_t dstOffset_[RDB_DRIVER_CTRL_HDF5_NDATA];
        size_t dstSizes_[RDB_DRIVER_CTRL_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_DRIVER_CTRL_HDF5_NDATA];
        hid_t fieldType_[RDB_DRIVER_CTRL_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t uintArray8_;
        hsize_t dimsUInt8_[1];
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
