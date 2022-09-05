#ifndef _RDB_HDF5_MESSAGE_RDB_TRAFFIC_LIGHT_BASE_H
#define _RDB_HDF5_MESSAGE_RDB_TRAFFIC_LIGHT_BASE_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbTrafficLightBase
    {
        
    public:

        struct ENRICHED_RDB_TRAFFIC_LIGHT_BASE
        {
           uint32_t                  frameNumber;
           int32_t                   id;                             /**< unique ID of the traffic light                           @unit _                           @version 0x0100 */
           float                     state;                          /**< current state (normalized)                               @unit [0.0..1.0]                  @version 0x0100 */
           uint32_t                  stateMask;                      /**< current state mask (light mask, e.g. for gfx)            @unit _                           @version 0x0100 */
        };
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_TRAFFIC_LIGHT_BASE_HDF5 {  RDB_TRAFFIC_LIGHT_BASE_HDF5_FRAME_NUMBER,
                                            RDB_TRAFFIC_LIGHT_BASE_HDF5_ID,
                                            RDB_TRAFFIC_LIGHT_BASE_HDF5_STATE,
                                            RDB_TRAFFIC_LIGHT_BASE_HDF5_STATE_MASK,
                                            RDB_TRAFFIC_LIGHT_BASE_HDF5_NDATA};
        
        Hdf5RdbTrafficLightBase();

        virtual ~Hdf5RdbTrafficLightBase(){}

        void initData();

        static void convertToModifiedStructure(const RDB_TRAFFIC_LIGHT_BASE_t& data, const uint32_t frameNumber, ENRICHED_RDB_TRAFFIC_LIGHT_BASE& modifiedData);

    public:
        
        size_t dstOffset_[RDB_TRAFFIC_LIGHT_BASE_HDF5_NDATA];
        size_t dstSizes_[RDB_TRAFFIC_LIGHT_BASE_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_TRAFFIC_LIGHT_BASE_HDF5_NDATA];
        hid_t fieldType_[RDB_TRAFFIC_LIGHT_BASE_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
    };
}

#endif
