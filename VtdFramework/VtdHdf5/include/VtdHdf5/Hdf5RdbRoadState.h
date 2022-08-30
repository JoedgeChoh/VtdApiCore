#ifndef _RDB_HDF5_MESSAGE_RDB_ROAD_STATE_H
#define _RDB_HDF5_MESSAGE_RDB_ROAD_STATE_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbRoadState
    {
        
    public:

        struct ENRICHED_RDB_ROAD_STATE
        {
            uint32_t     frameNumber;
            uint32_t     playerId;        /**< ID of the player for which the state applies                            @unit _                              @version 0x0100 */
            int8_t       wheelId;         /**< unique ID of the player's wheel for which state is valid (-1 for all)   @unit @link RDB_WHEEL_ID @endlink    @version 0x0100 */
            uint8_t      spare0;          /**< yet another spare                                                       @unit _                              @version 0x0100 */
            uint16_t     spare1;          /**< yet another spare                                                       @unit _                              @version 0x0100 */
            uint32_t     roadId;          /**< unique ID of the road                                                   @unit _                              @version 0x0100 */
            float        defaultSpeed;    /**< default speed of the road                                               @unit m/s                            @version 0x0100 */
            float        waterLevel;      /**< rain level on road                                                      @unit [0.0..1.0]                     @version 0x0100 */
            uint32_t     eventMask;       /**< road events                                                             @unit @link RDB_ROAD_EVENT @endlink  @version 0x0100 */
            float        distToJunc;      /**< distance to next junction in driving direction                          @unit m                              @version 0x011F */
            int32_t      spare2[11];      /**< for future use                                                          @unit _                              @version 0x0100 */
        };
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum  RDB_ROAD_STATE_HDF5 { RDB_ROAD_STATE_HDF5_FRAME_NUMBER,
                                    RDB_ROAD_STATE_HDF5_PLAYER_ID,
                                    RDB_ROAD_STATE_HDF5_WHEEL_ID,
                                    RDB_ROAD_STATE_HDF5_SPARE0,
                                    RDB_ROAD_STATE_HDF5_SPARE1,
                                    RDB_ROAD_STATE_HDF5_ROAD_ID,
                                    RDB_ROAD_STATE_HDF5_DEFAULT_SPEED,
                                    RDB_ROAD_STATE_HDF5_WATER_LEVEL,
                                    RDB_ROAD_STATE_HDF5_EVENT_MASK,
                                    RDB_ROAD_STATE_HDF5_DIST_TO_JUNC,
                                    RDB_ROAD_STATE_HDF5_SPARE2,
                                    RDB_ROAD_STATE_HDF5_NDATA};

        Hdf5RdbRoadState();

        virtual ~Hdf5RdbRoadState();

        void initData();

        static void convertToModifiedStructure(const RDB_ROAD_STATE_t& data, const uint32_t frameNumber, ENRICHED_RDB_ROAD_STATE& modifiedData);

    public:
        
        size_t dstOffset_[RDB_ROAD_STATE_HDF5_NDATA];
        size_t dstSizes_[RDB_ROAD_STATE_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_ROAD_STATE_HDF5_NDATA];
        hid_t fieldType_[RDB_ROAD_STATE_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t intArray32_;
        hsize_t dimsInt32_[1];
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];

    };
}

#endif
