#include <VtdHdf5/Hdf5RdbTrafficLightPhase.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbTrafficLightPhase::Hdf5RdbTrafficLightPhase() : tableSize_(RDB_TRAFFIC_LIGHT_PHASE_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbTrafficLightPhase::~Hdf5RdbTrafficLightPhase()
        {
            // have to be close memory leak
            H5Tclose(uintArray8);
        }

        void Hdf5RdbTrafficLightPhase::initData()
        {
           dimsUInt8[0] = sizeof(RDB_TRAFFIC_LIGHT_PHASE_t::spare) / sizeof(uint8_t);
           uintArray8 = H5Tarray_create(H5T_NATIVE_UINT8, 1, dimsUInt8);

           dstSize_ = sizeof(RDB_TRAFFIC_LIGHT_PHASE_t);

           dstOffset_[RDB_TRAFFIC_LIGHT_PHASE_HDF5_DURATION] = HOFFSET(RDB_TRAFFIC_LIGHT_PHASE_t, duration);
           dstSizes_ [RDB_TRAFFIC_LIGHT_PHASE_HDF5_DURATION] = sizeof(RDB_TRAFFIC_LIGHT_PHASE_t::duration);
           fieldType_[RDB_TRAFFIC_LIGHT_PHASE_HDF5_DURATION] = H5T_NATIVE_FLOAT;
           fieldNames[RDB_TRAFFIC_LIGHT_PHASE_HDF5_DURATION] = "duration";

           dstOffset_[RDB_TRAFFIC_LIGHT_PHASE_HDF5_TYPE] = HOFFSET(RDB_TRAFFIC_LIGHT_PHASE_t, type);
           dstSizes_ [RDB_TRAFFIC_LIGHT_PHASE_HDF5_TYPE] = sizeof(RDB_TRAFFIC_LIGHT_PHASE_t::type);
           fieldType_[RDB_TRAFFIC_LIGHT_PHASE_HDF5_TYPE] = H5T_NATIVE_UINT8;
           fieldNames[RDB_TRAFFIC_LIGHT_PHASE_HDF5_TYPE] = "type";

           dstOffset_[RDB_TRAFFIC_LIGHT_PHASE_HDF5_SPARE] = HOFFSET(RDB_TRAFFIC_LIGHT_PHASE_t, spare);
           dstSizes_ [RDB_TRAFFIC_LIGHT_PHASE_HDF5_SPARE] = sizeof(RDB_TRAFFIC_LIGHT_PHASE_t::spare);
           fieldType_[RDB_TRAFFIC_LIGHT_PHASE_HDF5_SPARE] = uintArray8;
           fieldNames[RDB_TRAFFIC_LIGHT_PHASE_HDF5_SPARE] = "spare";
        }
}

