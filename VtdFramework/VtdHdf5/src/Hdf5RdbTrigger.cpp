#include <VtdHdf5/Hdf5RdbTrigger.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbTrigger::Hdf5RdbTrigger () : tableSize_(RDB_TRIGGER_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbTrigger::~Hdf5RdbTrigger()
        {
        }

        void Hdf5RdbTrigger::initData()
        {
           dstSize_ = sizeof(RDB_TRIGGER_t);

           dstOffset_[RDB_TRIGGER_HDF5_DELAT_T] = HOFFSET(RDB_TRIGGER_t, deltaT);
           dstSizes_ [RDB_TRIGGER_HDF5_DELAT_T] = sizeof(RDB_TRIGGER_t::deltaT);
           fieldType_[RDB_TRIGGER_HDF5_DELAT_T] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_TRIGGER_HDF5_DELAT_T] = "deltaT";

           dstOffset_[RDB_TRIGGER_HDF5_FRAME_NO] = HOFFSET(RDB_TRIGGER_t, frameNo);
           dstSizes_ [RDB_TRIGGER_HDF5_FRAME_NO] = sizeof(RDB_TRIGGER_t::frameNo);
           fieldType_[RDB_TRIGGER_HDF5_FRAME_NO] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_TRIGGER_HDF5_FRAME_NO] = "frameNumber";

           dstOffset_[RDB_TRIGGER_HDF5_FEATURES] = HOFFSET(RDB_TRIGGER_t, features);
           dstSizes_ [RDB_TRIGGER_HDF5_FEATURES] = sizeof(RDB_TRIGGER_t::features);
           fieldType_[RDB_TRIGGER_HDF5_FEATURES] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_TRIGGER_HDF5_FEATURES] = "features";

           dstOffset_[RDB_TRIGGER_HDF5_SPARE0] = HOFFSET(RDB_TRIGGER_t, spare0);
           dstSizes_ [RDB_TRIGGER_HDF5_SPARE0] = sizeof(RDB_TRIGGER_t::spare0);
           fieldType_[RDB_TRIGGER_HDF5_SPARE0] = H5T_NATIVE_INT16;
           fieldNames_[RDB_TRIGGER_HDF5_SPARE0] = "spare0";
        }

}
