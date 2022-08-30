#ifndef _RDB_HDF5_MESSAGE_RDB_ENVIRONMENT_H
#define _RDB_HDF5_MESSAGE_RDB_ENVIRONMENT_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbEnvironment
    {
        
    public:

        struct ENRICHED_RDB_ENVIRONMENT
        {
            uint32_t       frameNumber;
            float          visibility;            /**< visibility range                                                        @unit m                                  @version 0x0100 */
            uint32_t       timeOfDay;             /**< time of day at sim start                                                @unit s                                  @version 0x0100 */
            float          brightness;            /**< brightness of ambient light                                             @unit [0.0..1.0]                         @version 0x0100 */
            uint8_t        precipitation;         /**< intensity of precipitation                                              @unit [0..255]                           @version 0x0100 */
            uint8_t        cloudState;            /**< cloud state                                                             @unit @link RDB_ENV_CLOUD_STATE @endlink @version 0x0100 */
            uint16_t       flags;                 /**< a series of environment flags                                           @unit @link RDB_ENV_FLAG        @endlink @version 0x0100 */
            float          temperature;           /**< ambient temperature                                                     @unit [deg]                              @version 0x0119 */
            uint8_t        day;                   /**< date - day                                                              @unit [-]                                @version 0x011F */
            uint8_t        month;                 /**< date - month                                                            @unit [-]                                @version 0x011F */
            uint16_t       year;                  /**< date - year                                                             @unit [-]                                @version 0x011F */
            int16_t        timeZoneMinutesWest;   /**< time zone, minutes west, relative to Greenwich                          @unit [-]                                @version 0x011F */
            uint16_t       spare2;                /**< yet another spare                                                       @unit _                                  @version 0x0100 */
            float          frictionScale;         /**< friction scale value                                                    @unit _                                  @version 0x0122 */
            uint32_t       spare1[4];             /**< yet another spare                                                       @unit _                                  @version 0x0100 */
        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_ENVIRONMENT_HDF5 { RDB_ENVIRONMENT_HDF5_FRAME_NUMBER,
                                    RDB_ENVIRONMENT_HDF5_VISIBILITY,
                                    RDB_ENVIRONMENT_HDF5_TIME_OF_DATA,
                                    RDB_ENVIRONMENT_HDF5_BRIGHTNESS,
                                    RDB_ENVIRONMENT_HDF5_PRECIPITATION,
                                    RDB_ENVIRONMENT_HDF5_CLOUD_STATE,
                                    RDB_ENVIRONMENT_HDF5_FLAGS,
                                    RDB_ENVIRONMENT_HDF5_TEMPERATURE,
                                    RDB_ENVIRONMENT_HDF5_DAY,
                                    RDB_ENVIRONMENT_HDF5_MONTH,
                                    RDB_ENVIRONMENT_HDF5_YEAR,
                                    RDB_ENVIRONMENT_HDF5_TIME_ZONE_MINUTE_WEST,
                                    RDB_ENVIRONMENT_HDF5_SPARE2,
                                    RDB_ENVIRONMENT_HDF5_SPARE1,
                                    RDB_ENVIRONMENT_HDF5_NDATA};
        
        Hdf5RdbEnvironment();

        virtual ~Hdf5RdbEnvironment();

        void initData();

        static void convertToModifiedStructure(const RDB_ENVIRONMENT_t& data, const uint32_t frameNumber, ENRICHED_RDB_ENVIRONMENT& modifiedData);

    public:
        
        size_t dstOffset_[RDB_ENVIRONMENT_HDF5_NDATA];
        size_t dstSizes_[RDB_ENVIRONMENT_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_ENVIRONMENT_HDF5_NDATA];
        hid_t fieldType_[RDB_ENVIRONMENT_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t uintArray32_;
        hsize_t dimsUInt32_[1];
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
