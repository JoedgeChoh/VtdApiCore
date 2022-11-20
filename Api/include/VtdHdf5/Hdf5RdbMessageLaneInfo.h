#ifndef _RDB_HDF5_MESSAGE_LANE_INFO_H
#define _RDB_HDF5_MESSAGE_LANE_INFO_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageLaneInfo
    {
        
    public:

        struct ENRICHED_RDB_LANE_INFO
        {
            uint32_t    frameNumber;
            uint16_t    roadId;                  /**< unique road ID                                                         @unit _                                @version 0x0100 */
            int8_t      id;                      /**< lane ID according to OpenDRIVE                                         @unit [-127..127]                      @version 0x0100 */
            uint8_t     neighborMask;            /**< existence mask for adjacent lanes                                      @unit @link RDB_LANE_EXISTS @endlink   @version 0x0100 */
            int8_t      leftLaneId;              /**< ID of lane left of current lane                                        @unit [-127..127]                      @version 0x0100 */
            int8_t      rightLaneId;             /**< ID of lane right of current lane                                       @unit [-127..127]                      @version 0x0100 */
            uint8_t     borderType;              /**< type of lane border                                                    @unit @link RDB_LANE_BORDER @endlink   @version 0x0100 */
            uint8_t     material;                /**< type of lane material                                                  @unit [0..255]                         @version 0x0100 */
            uint16_t    status;                  /**< status mask of lane                                                    @unit @link RDB_LANE_STATUS @endlink   @version 0x0100 */
            uint16_t    type;                    /**< enumerated lane type according to OpenDRIVE (0=none, 1=driving...)     @unit _                                @version 0x010D */
            float       width;                   /**< lane width                                                             @unit m                                @version 0x0100 */
            double      curvVert;                /**< vertical curvature in lane center                                      @unit 1/m                              @version 0x0100 */
            double      curvVertDot;             /**< change of vertical curvature in lane center                            @unit 1/m2                             @version 0x0100 */
            double      curvHor;                 /**< horizontal curvature in lane center                                    @unit 1/m                              @version 0x0100 */
            double      curvHorDot;              /**< change of horizontal curvature in lane center                          @unit 1/m2                             @version 0x0100 */
            uint32_t    playerId;                /**< id of the player to which this info belongs                            @unit _                                @version 0x0100 */
            uint32_t    spare1;                  /**< for future use                                                         @unit _                                @version 0x0100 */
        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_LANE_INFO {    RDB_LANE_INFO_FRAME_NUMBER,
                                RDB_LANE_INFO_ROAD_ID,
                                RDB_LANE_INFO_ID,
                                RDB_LANE_INFO_NEIGHBOR_MASK,
                                RDB_LANE_INFO_LEFT_LANE_ID,
                                RDB_LANE_INFO_RIGHT_LANE_ID,
                                RDB_LANE_INFO_BORDER_TYPE,
                                RDB_LANE_INFO_MATERIAL,
                                RDB_LANE_INFO_STATUS,
                                RDB_LANE_INFO_TYPE,
                                RDB_LANE_INFO_WIDTH,
                                RDB_LANE_INFO_CURV_VERT,
                                RDB_LANE_INFO_CURV_VERT_DOT,
                                RDB_LANE_INFO_CURV_HOR,
                                RDB_LANE_INFO_CURV_HOR_DOT,
                                RDB_LANE_INFO_PLAYER_ID,
                                RDB_LANE_INFO_SPARE1,
                                RDB_LANE_INFO_NDATA};
      
        Hdf5RdbMessageLaneInfo ();

        virtual ~Hdf5RdbMessageLaneInfo (){}

        void initData();

        static void convertToModifiedStructure(const RDB_LANE_INFO_t& data, const uint32_t frameNumber, ENRICHED_RDB_LANE_INFO& modifiedData);

    public:

        size_t dstOffset_[RDB_LANE_INFO_NDATA];
        size_t dstSizes_[RDB_LANE_INFO_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_LANE_INFO_NDATA];
        hid_t fieldType_[RDB_LANE_INFO_NDATA];

        size_t tableSize_;

    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
