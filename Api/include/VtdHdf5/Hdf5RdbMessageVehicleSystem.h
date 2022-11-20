#ifndef _RDB_HDF5_MESSAGE_RDB_VEHICLE_SYSTEMS_H
#define _RDB_HDF5_MESSAGE_RDB_VEHICLE_SYSTEMS_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{

    class Hdf5RdbMessageVehicleSystem
    {
        
    public:

        struct ENRICHED_RDB_VEHICLE_SYSTEMS
        {
            uint32_t frameNumber;
            uint32_t playerId;                /**< ID of the player to which the data belongs                               @unit _                                        @version 0x0100 */
            uint32_t lightMask;               /**< mask of active light systems                                             @unit @link RDB_VEHICLE_LIGHT @endlink         @version 0x0100 */
            float    steering;                /**< front wheel steering angle (NOT: steering wheel angle)                   @unit rad                                      @version 0x0100 */
            float    steeringWheelTorque;     /**< torque at the steering wheel                                             @unit Nm                                       @version 0x0100 */
            uint8_t  accMask;                 /**< acc state mask                                                           @unit @link RDB_VEHICLE_ACC_FLAG @endlink      @version 0x010A */
            uint8_t  accSpeed;                /**< acc speed indication                                                     @unit km/h [0..255]                            @version 0x010A */
            uint8_t  batteryState;            /**< battery charge state                                                     @unit [0..255]                                 @version 0x010A */
            int8_t   batteryRate;             /**< battery discharge / charge rate                                          @unit [-127..127]                              @version 0x010A */
            uint16_t displayLightMask;        /**< lightmask for driver display (16 lights)                                 @unit @link RDB_VEHICLE_DISPLAY_LIGHT @endlink @version 0x010A */
            uint16_t fuelGauge;               /**< fuel gauge [0.0..1.0]                                                    @unit [0..65535] = [0.0..1.0]                  @version 0x0119 */
            uint32_t spare[5];                /**< spares for future use                                                    @unit _                                        @version 0x0100 */
        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_VEHICLE_SYSTEM_HDF5 {  RDB_VEHICLE_SYSTEM_HDF5_FRAME_NUMBER,
                                        RDB_VEHICLE_SYSTEM_HDF5_PLAYER_ID,
                                        RDB_VEHICLE_SYSTEM_HDF5_LIGHT_MASK,
                                        RDB_VEHICLE_SYSTEM_HDF5_STEERING,
                                        RDB_VEHICLE_SYSTEM_HDF5_STEERING_WHEEL_TORQUE,
                                        RDB_VEHICLE_SYSTEM_HDF5_ACC_MASK,
                                        RDB_VEHICLE_SYSTEM_HDF5_ACC_SPEED,
                                        RDB_VEHICLE_SYSTEM_HDF5_BATTERY_STATE,
                                        RDB_VEHICLE_SYSTEM_HDF5_BATTERY_RATE,
                                        RDB_VEHICLE_SYSTEM_HDF5_DISPLAY_LIGHT_MASK,
                                        RDB_VEHICLE_SYSTEM_HDF5_FUEL_GAUGE,
                                        RDB_VEHICLE_SYSTEM_HDF5_SPARE,
                                        RDB_VEHICLE_SYSTEM_HDF5_NDATA};
        
        Hdf5RdbMessageVehicleSystem();

        virtual ~Hdf5RdbMessageVehicleSystem();

        void initData();

        static void convertToModifiedStructure(const RDB_VEHICLE_SYSTEMS_t& data, const uint32_t frameNumber, ENRICHED_RDB_VEHICLE_SYSTEMS& modifiedData);

    public:
        
        hsize_t  dims_[1];
        size_t dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_NDATA];
        size_t dstSizes_[RDB_VEHICLE_SYSTEM_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_NDATA];
        hid_t fieldType_[RDB_VEHICLE_SYSTEM_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t unitArray_;

    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];

    };
}

#endif
