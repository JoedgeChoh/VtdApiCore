#ifndef _RDB_HDF5_MESSAGE_ROAD_POS_H
#define _RDB_HDF5_MESSAGE_ROAD_POS_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageRoadPos
    {
        static const size_t TABLE_NAME_SIZE = 32;

     public:

        struct ENRICHED_RDB_ROAD_POS
        {
            uint32_t         frameNumber;
            uint32_t         playerId;           /**< id of the player to which road position belongs                        @unit _                                @version 0x0100 */
            uint16_t         roadId;             /**< unique road ID                                                         @unit _                                @version 0x0100 */
            int8_t           laneId;             /**< lane ID                                                                @unit _                                @version 0x0100 */
            uint8_t          flags;              /**< road position flags, further info                                      @unit @link RDB_ROAD_POS_FLAG @endlink @version 0x0100 */
            float            roadS;              /**< s-coordinate along road's reference line                               @unit m                                @version 0x0100 */
            float            roadT;              /**< t-coordinate perpendicular to road's reference line                    @unit m                                @version 0x0100 */
            float            laneOffset;         /**< offset from lane center in road co-ordinates                           @unit m                                @version 0x0100 */
            float            hdgRel;             /**< heading angle relative to lane tangent dir                             @unit rad                              @version 0x0100 */
            float            pitchRel;           /**< pitch angle relative to road tangent plane                             @unit rad                              @version 0x0100 */
            float            rollRel;            /**< roll angle relative to road tangent plane                              @unit rad                              @version 0x0100 */
            uint8_t          roadType;           /**< type of the road, corresponding to OpenDRIVE                           @unit @link RDB_ROAD_TYPE @endlink     @version 0x010A */
            uint8_t          spare1;             /**< for future use                                                         @unit _                                @version 0x010A */
            uint16_t         spare2;             /**< for future use                                                         @unit _                                @version 0x010A */
            float            pathS;              /**< longitudinal path co-ordinate                                          @unit _                                @version 0x010E */
        };
            
        enum RDB_ROAD_POS_HDF5 {    RDB_ROAD_POS_HDF5_FRAME_NUMBER,
                                    RDB_ROAD_POS_HDF5_PLAYER_ID,
                                    RDB_ROAD_POS_HDF5_ROAD_ID,
                                    RDB_ROAD_POS_HDF5_LANE_ID,
                                    RDB_ROAD_POS_HDF5_FLAGS,
                                    RDB_ROAD_POS_HDF5_ROAD_S,
                                    RDB_ROAD_POS_HDF5_ROAD_T,
                                    RDB_ROAD_POS_HDF5_LANE_OFFSET,
                                    RDB_ROAD_POS_HDF5_HDG_REL,
                                    RDB_ROAD_POS_HDF5_PITCH_REL,
                                    RDB_ROAD_POS_HDF5_ROLL_REL,
                                    RDB_ROAD_POS_HDF5_ROAD_TYPE,
                                    RDB_ROAD_POS_HDF5_SPARE1,
                                    RDB_ROAD_POS_HDF5_SPARE2,
                                    RDB_ROAD_POS_HDF5_PATH_S,
                                    RDB_ROAD_POS_HDF5_NDATA};
      
        Hdf5RdbMessageRoadPos();

        virtual ~Hdf5RdbMessageRoadPos(){}

        void initData();

        static void convertToModifiedStructure(const RDB_ROAD_POS_t& data, const uint32_t frameNumber, ENRICHED_RDB_ROAD_POS& modifiedData);

    public:

        size_t dstOffset_[RDB_ROAD_POS_HDF5_NDATA];
        size_t dstSizes_[RDB_ROAD_POS_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_ROAD_POS_HDF5_NDATA];
        hid_t fieldType_[RDB_ROAD_POS_HDF5_NDATA];

        size_t tableSize_;

    private:

        uint32_t positionFrameId;
        char tableName[TABLE_NAME_SIZE];

    };
}

#endif
