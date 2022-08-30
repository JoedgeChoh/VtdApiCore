#ifndef _RDB_HDF5_MESSAGE_RDB_TRAFFIC_LIGHT_PHASE_H
#define _RDB_HDF5_MESSAGE_RDB_TRAFFIC_LIGHT_PHASE_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbTrafficLightPhase
    {
        
    public:
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_TRAFFIC_LIGHT_PHASE_HDF5 {RDB_TRAFFIC_LIGHT_PHASE_HDF5_DURATION, RDB_TRAFFIC_LIGHT_PHASE_HDF5_TYPE, RDB_TRAFFIC_LIGHT_PHASE_HDF5_SPARE
                                           , RDB_TRAFFIC_LIGHT_PHASE_HDF5_NDATA}; //  // traffic light phase
        
        Hdf5RdbTrafficLightPhase();

        virtual ~Hdf5RdbTrafficLightPhase();

        void initData();

    public:
        
        size_t dstOffset_[RDB_TRAFFIC_LIGHT_PHASE_HDF5_NDATA];
        size_t dstSizes_[RDB_TRAFFIC_LIGHT_PHASE_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames[RDB_TRAFFIC_LIGHT_PHASE_HDF5_NDATA];
        hid_t fieldType_[RDB_TRAFFIC_LIGHT_PHASE_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t uintArray8;
        hsize_t dimsUInt8[1];
        
    private:
        uint32_t positionFrameId;
        char tableName[TABLE_NAME_SIZE];

    };
}

#endif
