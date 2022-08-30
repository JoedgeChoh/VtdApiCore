#ifndef _RDB_HDF5_MESSAGE_RDB_SENSOR_STATE_H
#define _RDB_HDF5_MESSAGE_RDB_SENSOR_STATE_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbSensorState
    {
        
    public:

        struct SIMPLE_RDB_SENSOR_STATE
        {
            uint32_t    frameNumber;
            uint32_t    id;
            uint8_t     type;
            uint8_t     hostCategory;
            uint16_t    spare0;
            uint32_t    hostId;
            char        name[RDB_SIZE_OBJECT_NAME];
            float       fovHV[2];
            float       clipNF[2];
            float       fovOffHV[2];
            int32_t     spare[2];

            double   pos_x;       /**< x position                                                @unit m                                @version 0x0100 */
            double   pos_y;       /**< y position                                                @unit m                                @version 0x0100 */
            double   pos_z;       /**< z position                                                @unit m                                @version 0x0100 */
            float    pos_h;       /**< heading angle                                             @unit rad                              @version 0x0100 */
            float    pos_p;       /**< pitch angle                                               @unit rad                              @version 0x0100 */
            float    pos_r;       /**< roll angle                                                @unit rad                              @version 0x0100 */
            uint8_t  pos_flags;   /**< co-ordinate flags                                         @unit @link RDB_SENSOR_STATE_POS_FLAG @endlink    @version 0x0100 */
            uint8_t  pos_type;    /**< co-ordinate system type identifier                        @unit @link RDB_SENSOR_STATE_POS_TYPE @endlink    @version 0x0100 */
            uint16_t pos_system;  /**< unique ID of the corresponding (user) co-ordinate system  @unit _                                @version 0x0100 */


            double   originCoordSys_x;       /**< x position                                                @unit m                                @version 0x0100 */
            double   originCoordSys_y;       /**< y position                                                @unit m                                @version 0x0100 */
            double   originCoordSys_z;       /**< z position                                                @unit m                                @version 0x0100 */
            float    originCoordSys_h;       /**< heading angle                                             @unit rad                              @version 0x0100 */
            float    originCoordSys_p;       /**< pitch angle                                               @unit rad                              @version 0x0100 */
            float    originCoordSys_r;       /**< roll angle                                                @unit rad                              @version 0x0100 */
            uint8_t  originCoordSys_flags;   /**< co-ordinate flags                                         @unit @link RDB_SENSOR_STATE_POS_FLAG @endlink    @version 0x0100 */
            uint8_t  originCoordSys_type;    /**< co-ordinate system type identifier                        @unit @link RDB_SENSOR_STATE_POS_TYPE @endlink    @version 0x0100 */
            uint16_t originCoordSys_system;  /**< unique ID of the corresponding (user) co-ordinate system  @unit _                                @version 0x0100 */

        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_SENSOR_STATE_HDF5 {RDB_SENSOR_STATE_HDF5_FRAME_NUMBER,
                                    RDB_SENSOR_STATE_HDF5_ID,
                                    RDB_SENSOR_STATE_HDF5_TYPE,
                                    RDB_SENSOR_STATE_HDF5_HOST_CATEGORY,
                                    RDB_SENSOR_STATE_HDF5_SPARE0,
                                    RDB_SENSOR_STATE_HDF5_HOST_ID,
                                    RDB_SENSOR_STATE_HDF5_NAME,
                                    RDB_SENSOR_STATE_HDF5_FOV_HV,
                                    RDB_SENSOR_STATE_HDF5_CLIP_NF,
                                    RDB_SENSOR_STATE_HDF5_FOV_OFF_HV,
                                    RDB_SENSOR_STATE_HDF5_SPARE,
                                    RDB_SENSOR_STATE_POS_HDF5_X,
                                    RDB_SENSOR_STATE_POS_HDF5_Y,
                                    RDB_SENSOR_STATE_POS_HDF5_Z,
                                    RDB_SENSOR_STATE_POS_HDF5_H,
                                    RDB_SENSOR_STATE_POS_HDF5_P,
                                    RDB_SENSOR_STATE_POS_HDF5_R,
                                    RDB_SENSOR_STATE_POS_HDF5_FLAGS,
                                    RDB_SENSOR_STATE_POS_HDF5_TYPE,
                                    RDB_SENSOR_STATE_POS_HDF5_SYSTEM,
                                    RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_X,
                                    RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_Y,
                                    RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_Z,
                                    RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_H,
                                    RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_P,
                                    RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_R,
                                    RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_FLAGS,
                                    RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_TYPE,
                                    RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_SYSTEM,
                                    RDB_SENSOR_STATE_HDF5_NDATA}; // sensor state

        Hdf5RdbSensorState();

        virtual ~Hdf5RdbSensorState();

        void initData();

        static void convertToModifiedStructure(const RDB_SENSOR_STATE_t& data, const uint32_t frameNumber, SIMPLE_RDB_SENSOR_STATE& modifiedData);

    public:
        
        size_t dstOffset_[RDB_SENSOR_STATE_HDF5_NDATA];
        size_t dstSizes_[RDB_SENSOR_STATE_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_SENSOR_STATE_HDF5_NDATA];
        hid_t fieldType_[RDB_SENSOR_STATE_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t floatArray_, intArray32_, stringType_;
        hsize_t dimsInt32_[1], dimsFloat_[1];
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
