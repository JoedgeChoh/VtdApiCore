#ifndef _RDB_HDF5_MESSAGE_RDB_TRAFFIC_LIGHT_EXT_H
#define _RDB_HDF5_MESSAGE_RDB_TRAFFIC_LIGHT_EXT_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbTrafficLightExt
    {
        
    public:

        struct ENRICHED_RDB_TRAFFIC_LIGHT_EXT
        {
           uint32_t                  frameNumber;
           int32_t                   ctrlId;                         /**< ID of the traffic light's controller                     @unit _                           @version 0x0100 */
           float                     cycleTime;                      /**< duration of a complete cycle of all phases               @unit s                           @version 0x0100 */
           uint16_t                  noPhases;                       /**< number of phases provided by this traffic light          @unit _                           @version 0x0100 */
           uint32_t                  dataSize;                       /**< total size of phase data following the package           @unit _                           @version 0x0100 */
        };
                
        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_TRAFFIC_LIGHT_EXT_HDF5 {   RDB_TRAFFIC_LIGHT_EXT_HDF5_FRAME_NUMBER,
                                            RDB_TRAFFIC_LIGHT_EXT_HDF5_CTRL_ID,
                                            RDB_TRAFFIC_LIGHT_EXT_HDF5_CYCLE_TIME,
                                            RDB_TRAFFIC_LIGHT_EXT_HDF5_NO_PHASE,
                                            RDB_TRAFFIC_LIGHT_EXT_HDF5_DATA_SIZE,
                                            RDB_TRAFFIC_LIGHT_EXT_HDF5_NDATA};

        Hdf5RdbTrafficLightExt();

        virtual ~Hdf5RdbTrafficLightExt(){}

        void initData();

        static void convertToModifiedStructure(const RDB_TRAFFIC_LIGHT_EXT_t& data, const uint32_t frameNumber, ENRICHED_RDB_TRAFFIC_LIGHT_EXT& modifiedData);

    public:
        
        size_t dstOffset_[RDB_TRAFFIC_LIGHT_EXT_HDF5_NDATA];
        size_t dstSizes_[RDB_TRAFFIC_LIGHT_EXT_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_TRAFFIC_LIGHT_EXT_HDF5_NDATA];
        hid_t fieldType_[RDB_TRAFFIC_LIGHT_EXT_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
    };
}

#endif
