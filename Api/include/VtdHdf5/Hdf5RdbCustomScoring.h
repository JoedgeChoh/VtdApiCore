#ifndef _RDB_HDF5_MESSAGE_RDB_CUSTOM_SCORING_H
#define _RDB_HDF5_MESSAGE_RDB_CUSTOM_SCORING_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbCustomScoring
    {
        
    public:

        struct ENRICHED_RDB_CUSTOM_SCORING
        {
            uint32_t frameNumber;
            uint32_t playerId;         /**< unique player ID                                     @unit _                                    @version 0x0100 */
            float    pathS;            /**< path position (negative if no path is available)     @unit m                                    @version 0x0100 */
            float    roadS;            /**< road position (negative if no road is available)     @unit m                                    @version 0x0100 */
            float    fuelCurrent;      /**< current fuel consumption                             @unit l/100km                              @version 0x0100 */
            float    fuelAverage;      /**< average fuel consumption                             @unit l/100km                              @version 0x0100 */
            uint32_t stateFlags;       /**< arbitrary state information                          @unit @link RDB_SCORING_FLAG @endlink      @version 0x0100 */
            float    slip;             /**< slip factor [0.0..1.0]                               @unit _                                    @version 0x0100 */
            uint32_t spare[4];         /**< we'll certainly have some more ideas....             @unit _                                    @version 0x0100 */
        };

        static const size_t TABLE_NAME_SIZE = 32;
        
        enum RDB_CUSTOM_SCORING_HDF5 {  RDB_CUSTOM_SCORING_HDF5_FRAME_NUMBER,
                                        RDB_CUSTOM_SCORING_HDF5_PLAYER_ID,
                                        RDB_CUSTOM_SCORING_HDF5_PATH_S,
                                        RDB_CUSTOM_SCORING_HDF5_ROAD_S,
                                        RDB_CUSTOM_SCORING_HDF5_FUEL_CURRENT,
                                        RDB_CUSTOM_SCORING_HDF5_FUEL_AVERAGE,
                                        RDB_CUSTOM_SCORING_HDF5_STATE_FLAGS,
                                        RDB_CUSTOM_SCORING_HDF5_SLIP,
                                        RDB_CUSTOM_SCORING_HDF5_SPARE,
                                        RDB_CUSTOM_SCORING_HDF5_NDATA};
        
        Hdf5RdbCustomScoring();

        virtual ~Hdf5RdbCustomScoring();

        void initData();

        static void convertToModifiedStructure(const RDB_CUSTOM_SCORING_t& data, const uint32_t frameNumber, ENRICHED_RDB_CUSTOM_SCORING& modifiedData);

    public:
        
        size_t dstOffset_[RDB_CUSTOM_SCORING_HDF5_NDATA];
        size_t dstSizes_[RDB_CUSTOM_SCORING_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_CUSTOM_SCORING_HDF5_NDATA];
        hid_t fieldType_[RDB_CUSTOM_SCORING_HDF5_NDATA];
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
