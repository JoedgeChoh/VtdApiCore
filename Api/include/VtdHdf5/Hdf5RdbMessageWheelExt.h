#ifndef _RDB_HDF5_MESSAGE_RDB_WHEEL_EXT_H
#define _RDB_HDF5_MESSAGE_RDB_WHEEL_EXT_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageWheelExt
    {
        
    public:
        
        struct ENRICHED_RDB_WHEEL_EXT
        {
            uint32_t frameNumber;
            float    vAngular;                    /**< angular velocity                                 @unit rad/s                     @version 0x0100 */
            float    forceZ;                      /**< wheel contact force                              @unit N                         @version 0x0100 */
            float    forceLat;                    /**< lateral force                                    @unit N                         @version 0x0100 */
            float    forceLong;                   /**< longitudinal force                               @unit N                         @version 0x0100 */
            float    forceTireWheelXYZ[3];        /**< force of tire on wheel                           @unit N                         @version 0x0100 */
            float    radiusDynamic;               /**< dynamic tire radius                              @unit m                         @version 0x0100 */
            float    brakePressure;               /**< brake pressure at wheel                          @unit Pa                        @version 0x0100 */
            float    torqueDriveShaft;            /**< torque at drive shaft                            @unit Nm                        @version 0x0100 */
            float    damperSpeed;                 /**< speed of damper                                  @unit m/s                       @version 0x0100 */
            uint32_t spare2[4];                   /**< reserved for future use                          @unit _                         @version 0x0100 */
        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_WHEEL_EXT_HDF5 {   RDB_WHEEL_EXT_HDF5_FRAME_NUMBER,
                                    RDB_WHEEL_EXT_HDF5_V_ANGULAR,
                                    RDB_WHEEL_EXT_HDF5_FORCE_Z,
                                    RDB_WHEEL_EXT_HDF5_FORCE_LAT,
                                    RDB_WHEEL_EXT_HDF5_FORCE_LONG,
                                    RDB_WHEEL_EXT_HDF5_FORCE_TIRE_WHEEL_XYZ,
                                    RDB_WHEEL_EXT_HDF5_RADIUS_DYNAMIC,
                                    RDB_WHEEL_EXT_HDF5_BRAKE_PRESSURE,
                                    RDB_WHEEL_EXT_HDF5_TORQUE_DRIVE_SHARF,
                                    RDB_WHEEL_EXT_HDF5_DAMPER_SPEED,
                                    RDB_WHEEL_EXT_HDF5_SPARE2,
                                    RDB_WHEEL_EXT_HDF5_NDATA};
        
        Hdf5RdbMessageWheelExt();

        virtual ~Hdf5RdbMessageWheelExt();

        void initData();

        static void convertToModifiedStructure(const RDB_WHEEL_EXT_t& data, const uint32_t frameNumber, ENRICHED_RDB_WHEEL_EXT& modifiedData);

    public:
        
        size_t dstOffset_[RDB_WHEEL_EXT_HDF5_NDATA];
        size_t dstSizes_[RDB_WHEEL_EXT_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_WHEEL_EXT_HDF5_NDATA];
        hid_t fieldType_[RDB_WHEEL_EXT_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t floatArray_, uintArray32_;
        hsize_t  dimsFloat_[1], dimsUInt32_[1];
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];

    };
}

#endif
