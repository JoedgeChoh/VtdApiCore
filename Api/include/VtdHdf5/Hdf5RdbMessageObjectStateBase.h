#ifndef _RDB_HDF5_MESSAGE_RDB_OBJECT_STATE_BASE_H
#define _RDB_HDF5_MESSAGE_RDB_OBJECT_STATE_BASE_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageObjectStateBase
    {
        
        public:

        struct SIMPLE_RDB_OBJECT_STATE_BASE
        {
            uint32_t frameNumber;
            uint32_t id;
            uint8_t category;
            uint8_t type;
            uint16_t visMask;
            char name[RDB_SIZE_OBJECT_NAME];
            uint32_t parent;
            uint16_t cfgFlags;
            int16_t cfgModelId;

            // "pos" sub group RDB_COORD
            double   pos_x;       /**< x position                                                @unit m                                @version 0x0100 */
            double   pos_y;       /**< y position                                                @unit m                                @version 0x0100 */
            double   pos_z;       /**< z position                                                @unit m                                @version 0x0100 */
            float    pos_h;       /**< heading angle                                             @unit rad                              @version 0x0100 */
            float    pos_p;       /**< pitch angle                                               @unit rad                              @version 0x0100 */
            float    pos_r;       /**< roll angle                                                @unit rad                              @version 0x0100 */
            uint8_t  pos_flags;   /**< co-ordinate flags                                         @unit @link RDB_COORD_FLAG @endlink    @version 0x0100 */
            uint8_t  pos_type;    /**< co-ordinate system type identifier                        @unit @link RDB_COORD_TYPE @endlink    @version 0x0100 */
            uint16_t pos_system;  /**< unique ID of the corresponding (user) co-ordinate system  @unit _                                @version 0x0100 */

            // "geo" sub group RDB_GEOMETRY
            float geo_dimX;        /**< x dimension in object co-ordinates (length)                                               @unit m                                  @version 0x0100 */
            float geo_dimY;        /**< y dimension in object co-ordinates (width)                                                @unit m                                  @version 0x0100 */
            float geo_dimZ;        /**< z dimension in object co-ordinates (height)                                               @unit m                                  @version 0x0100 */
            float geo_offX;        /**< x distance from ref. point to center of geometry, object co-ordinate system               @unit m                                  @version 0x0100 */
            float geo_offY;        /**< y distance from ref. point to center of geometry, object co-ordinate system               @unit m                                  @version 0x0100 */
            float geo_offZ;        /**< z distance from ref. point to center of geometry, object co-ordinate system               @unit m                                  @version 0x0100 */

        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_OBJECT_STATE_BASE_HDF5 {   RDB_OBJECT_STATE_BASE_HDF5_FRAME_NUMBER,
                                            RDB_OBJECT_STATE_BASE_HDF5_ID,
                                            RDB_OBJECT_STATE_BASE_HDF5_CATEGORY,
                                            RDB_OBJECT_STATE_BASE_HDF5_TYPE,
                                            RDB_OBJECT_STATE_BASE_HDF5_VIS_MASK,
                                            RDB_OBJECT_STATE_BASE_HDF5_NAME,
                                            RDB_OBJECT_STATE_BASE_HDF5_PARENT,
                                            RDB_OBJECT_STATE_BASE_HDF5_CFG_FLAGS,
                                            RDB_OBJECT_STATE_BASE_HDF5_CFG_MODEL_ID,
                                            RDB_COORD_HDF5_X,
                                            RDB_COORD_HDF5_Y,
                                            RDB_COORD_HDF5_Z,
                                            RDB_COORD_HDF5_H,
                                            RDB_COORD_HDF5_P,
                                            RDB_COORD_HDF5_R,
                                            RDB_COORD_HDF5_FLAGS,
                                            RDB_COORD_HDF5_TYPE,
                                            RDB_COORD_HDF5_SYSTEM,
                                            RDB_GEOMETRY_HDF5_DIM_X,
                                            RDB_GEOMETRY_HDF5_DIM_Y,
                                            RDB_GEOMETRY_HDF5_DIM_Z,
                                            RDB_GEOMETRY_HDF5_OFF_X,
                                            RDB_GEOMETRY_HDF5_OFF_Y,
                                            RDB_GEOMETRY_HDF5_OFF_Z,
                                            RDB_OBJECT_STATE_BASE_HDF5_NDATA};

        
        Hdf5RdbMessageObjectStateBase();

        virtual ~Hdf5RdbMessageObjectStateBase();

        static void convertToModifiedStructure(const RDB_OBJECT_STATE_BASE_t& data, const uint32_t frameNumber, SIMPLE_RDB_OBJECT_STATE_BASE& modifiedData);

        void initData();

    public:

        size_t dstOffset_[RDB_OBJECT_STATE_BASE_HDF5_NDATA];
        size_t dstSizes_[RDB_OBJECT_STATE_BASE_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_OBJECT_STATE_BASE_HDF5_NDATA];
        hid_t fieldType_[RDB_OBJECT_STATE_BASE_HDF5_NDATA];
        // Initialize the field field_type
        hid_t stringType1_;
        size_t tableSize_;

    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];

    };
}

#endif
