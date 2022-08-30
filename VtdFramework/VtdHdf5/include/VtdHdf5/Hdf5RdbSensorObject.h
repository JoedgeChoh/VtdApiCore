#ifndef _RDB_HDF5_MESSAGE_RDB_SENSOR_OBJECT_H
#define _RDB_HDF5_MESSAGE_RDB_SENSOR_OBJECT_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>


namespace RdbToHdf5Writer
{
    class Hdf5RdbSensorObject
    {
        
    public:

        struct ENRICHED_RDB_SENSOR_OBJECT
        {
            uint32_t    frameNumber;
            uint8_t     category;     /**< object category                                                                @unit @link RDB_OBJECT_CATEGORY    @endlink  @version 0x0100 */
            uint8_t     type;         /**< object type                                                                    @unit @link RDB_OBJECT_TYPE        @endlink  @version 0x0100 */
            uint16_t    flags;        /**< sensor object flags                                                            @unit @link RDB_SENSOR_OBJECT_FLAG @endlink  @version 0x0100 */
            uint32_t    id;           /**< id of the object                                                               @unit _                                      @version 0x0100 */
            uint32_t    sensorId;     /**< id of the detecting sensor                                                     @unit _                                      @version 0x0100 */
            double      dist;         /**< distance between object and referring device                                   @unit m                                      @version 0x0100 */
            double      sensorPos_x;       /**< x position                                                @unit m                                @version 0x0100 */
            double      sensorPos_y;       /**< y position                                                @unit m                                @version 0x0100 */
            double      sensorPos_z;       /**< z position                                                @unit m                                @version 0x0100 */
            float       sensorPos_h;       /**< heading angle                                             @unit rad                              @version 0x0100 */
            float       sensorPos_p;       /**< pitch angle                                               @unit rad                              @version 0x0100 */
            float       sensorPos_r;       /**< roll angle                                                @unit rad                              @version 0x0100 */
            uint8_t     sensorPos_flags;   /**< co-ordinate flags                                         @unit @link RDB_COORD_FLAG @endlink    @version 0x0100 */
            uint8_t     sensorPos_type;    /**< co-ordinate system type identifier                        @unit @link RDB_COORD_TYPE @endlink    @version 0x0100 */
            uint16_t    sensorPos_system;  /**< unique ID of the corresponding (user) co-ordinate system  @unit _                                @version 0x0100 */
            int8_t      occlusion;    /**< degree of occlusion for viewer (-1 = not valid, 0..127 = 0..100% occlusion)    @unit [-1, 0..127]                           @version 0x0100 */
            int8_t      deltaLanePos; /**< for future use                                                                 @unit _                                      @version 0x011F */
            uint8_t     spare0[2];    /**< for future use                                                                 @unit _                                      @version 0x0100 */
            uint32_t    spare[3];     /**< for future use                                                                 @unit _                                      @version 0x0100 */
        };
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_SENSOR_OBJECT_HDF5 {   RDB_SENSOR_OBJECT_HDF5_FRAME_NUMBER,
                                        RDB_SENSOR_OBJECT_HDF5_CATEGORY,
                                        RDB_SENSOR_OBJECT_HDF5_TYPE,
                                        RDB_SENSOR_OBJECT_HDF5_FLAGS,
                                        RDB_SENSOR_OBJECT_HDF5_ID,
                                        RDB_SENSOR_OBJECT_HDF5_SENSOR_ID,
                                        RDB_SENSOR_OBJECT_HDF5_DIST,
                                        RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_X,
                                        RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_Y,
                                        RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_Z,
                                        RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_H,
                                        RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_P,
                                        RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_R,
                                        RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_FLAGS,
                                        RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_TYPE,
                                        RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_SYSTEM,
                                        RDB_SENSOR_OBJECT_HDF5_OCCLUSION,
                                        RDB_SENSOR_OBJECT_HDF5_DELTA_LANE_POS,
                                        RDB_SENSOR_OBJECT_HDF5_SPARE0,
                                        RDB_SENSOR_OBJECT_HDF5_SPARE,
                                        RDB_SENSOR_OBJECT_HDF5_NDATA};

        Hdf5RdbSensorObject();

        virtual ~Hdf5RdbSensorObject();

        void initData();

        static void convertToModifiedStructure(const RDB_SENSOR_OBJECT_t& data, const uint32_t frameNumber, ENRICHED_RDB_SENSOR_OBJECT& modifiedData);

    public:
        
        size_t dstOffset_[RDB_SENSOR_OBJECT_HDF5_NDATA];
        size_t dstSizes_[RDB_SENSOR_OBJECT_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_SENSOR_OBJECT_HDF5_NDATA];
        hid_t fieldType_[RDB_SENSOR_OBJECT_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t uintArray32_, uintArray8_;
        hsize_t dimsUInt32_[1], dimsUInt8_[1];
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
