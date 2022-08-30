#ifndef _RDB_HDF5_MESSAGE_GEOMETRY_H
#define _RDB_HDF5_MESSAGE_GEOMETRY_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageGeometry
    {

    public:

        struct ENRICHED_RDB_GEOMETRY
        {
            uint32_t frameNumber;
            float dimX;        /**< x dimension in object co-ordinates (length)                                               @unit m                                  @version 0x0100 */
            float dimY;        /**< y dimension in object co-ordinates (width)                                                @unit m                                  @version 0x0100 */
            float dimZ;        /**< z dimension in object co-ordinates (height)                                               @unit m                                  @version 0x0100 */
            float offX;        /**< x distance from ref. point to center of geometry, object co-ordinate system               @unit m                                  @version 0x0100 */
            float offY;        /**< y distance from ref. point to center of geometry, object co-ordinate system               @unit m                                  @version 0x0100 */
            float offZ;        /**< z distance from ref. point to center of geometry, object co-ordinate system               @unit m                                  @version 0x0100 */
        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_GEOMETRY_HDF5 {    RDB_GEOMETRY_HDF5_DIM_FRAME_NUMBER,
                                    RDB_GEOMETRY_HDF5_DIM_X,
                                    RDB_GEOMETRY_HDF5_DIM_Y,
                                    RDB_GEOMETRY_HDF5_DIM_Z,
                                    RDB_GEOMETRY_HDF5_OFF_X,
                                    RDB_GEOMETRY_HDF5_OFF_Y,
                                    RDB_GEOMETRY_HDF5_OFF_Z,
                                    RDB_GEOMETRY_HDF5_NDATA};
      
        Hdf5RdbMessageGeometry();

        virtual ~Hdf5RdbMessageGeometry(){}

        void initData();

    public:

        size_t dstOffset_[RDB_GEOMETRY_HDF5_NDATA];
        size_t dstSizes_[RDB_GEOMETRY_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_GEOMETRY_HDF5_NDATA];
        hid_t fieldType_[RDB_GEOMETRY_HDF5_NDATA];

        size_t tableSize_;

    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
