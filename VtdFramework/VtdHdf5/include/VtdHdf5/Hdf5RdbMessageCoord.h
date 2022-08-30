#ifndef _RDB_HDF5_MESSAGE_COORD_H
#define _RDB_HDF5_MESSAGE_COORD_H

#include <VtdToolkit/viRDBIcd.h>
#include "RDBHDF5lib.h"
#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageCoord
    {

    public:

        struct ENRICHED_RDB_COORD
        {
            uint32_t frameNumber;
            double   x;       /**< x position                                                @unit m                                @version 0x0100 */
            double   y;       /**< y position                                                @unit m                                @version 0x0100 */
            double   z;       /**< z position                                                @unit m                                @version 0x0100 */
            float    h;       /**< heading angle                                             @unit rad                              @version 0x0100 */
            float    p;       /**< pitch angle                                               @unit rad                              @version 0x0100 */
            float    r;       /**< roll angle                                                @unit rad                              @version 0x0100 */
            uint8_t  flags;   /**< co-ordinate flags                                         @unit @link RDB_COORD_FLAG @endlink    @version 0x0100 */
            uint8_t  type;    /**< co-ordinate system type identifier                        @unit @link RDB_COORD_TYPE @endlink    @version 0x0100 */
            uint16_t system;  /**< unique ID of the corresponding (user) co-ordinate system  @unit _                                @version 0x0100 */
        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum     RDB_COORD_HDF5 {   RDB_COORD_HDF5_FRAME_NUMBER,
                                    RDB_COORD_HDF5_X,
                                    RDB_COORD_HDF5_Y,
                                    RDB_COORD_HDF5_Z,
                                    RDB_COORD_HDF5_H,
                                    RDB_COORD_HDF5_P,
                                    RDB_COORD_HDF5_R,
                                    RDB_COORD_HDF5_FLAGS,
                                    RDB_COORD_HDF5_TYPE,
                                    RDB_COORD_HDF5_SYSTEM,
                                    RDB_COORD_HDF5_NDATA};

        Hdf5RdbMessageCoord();

        virtual ~Hdf5RdbMessageCoord(){}

        void initData();

        static void convertToModifiedStructure(const RDB_COORD_t& data, const uint32_t frameNumber, ENRICHED_RDB_COORD& modifiedData);

    public:

        size_t dstOffset_[RDB_COORD_HDF5_NDATA];
        size_t dstSizes_[RDB_COORD_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_COORD_HDF5_NDATA];
        hid_t fieldType_[RDB_COORD_HDF5_NDATA];
        size_t tableSize_;

    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
