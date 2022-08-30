#include <VtdHdf5/Hdf5RdbMotionSystem.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbMotionSystem::Hdf5RdbMotionSystem () : tableSize_(RDB_MOTION_SYSTEM_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbMotionSystem::~Hdf5RdbMotionSystem()
        {
            // have to be close memory leak
            H5Tclose(uintArray32_);
            H5Tclose(uintArray8_);
        }

        void Hdf5RdbMotionSystem::initData()
        {
           dimsUInt32_[0] = sizeof(RDB_MOTION_SYSTEM_t::spare1) / sizeof(uint32_t);
           uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);
           
           dimsUInt8_[0] = sizeof(RDB_MOTION_SYSTEM_t::spare) / sizeof(uint8_t);
           uintArray8_ = H5Tarray_create(H5T_NATIVE_UINT8, 1, dimsUInt8_);
      
           dstSize_ = sizeof(RDB_MOTION_SYSTEM_t);

           dstOffset_[RDB_MOTION_SYSTEM_HDF5_PLAYER_ID] = HOFFSET(RDB_MOTION_SYSTEM_t, playerId);
           dstSizes_ [RDB_MOTION_SYSTEM_HDF5_PLAYER_ID] = sizeof(RDB_MOTION_SYSTEM_t::playerId);
           fieldType_[RDB_MOTION_SYSTEM_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_MOTION_SYSTEM_HDF5_PLAYER_ID] = "playerId";

           dstOffset_[RDB_MOTION_SYSTEM_HDF5_FLAGS] = HOFFSET(RDB_MOTION_SYSTEM_t, flags);
           dstSizes_ [RDB_MOTION_SYSTEM_HDF5_FLAGS] = sizeof(RDB_MOTION_SYSTEM_t::flags);
           fieldType_[RDB_MOTION_SYSTEM_HDF5_FLAGS] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_MOTION_SYSTEM_HDF5_FLAGS] = "flags";

           dstOffset_[RDB_MOTION_SYSTEM_HDF5_SUB_SYSTEM] = HOFFSET(RDB_MOTION_SYSTEM_t, subSystem);
           dstSizes_ [RDB_MOTION_SYSTEM_HDF5_SUB_SYSTEM] = sizeof(RDB_MOTION_SYSTEM_t::subSystem);
           fieldType_[RDB_MOTION_SYSTEM_HDF5_SUB_SYSTEM] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_MOTION_SYSTEM_HDF5_SUB_SYSTEM] = "subSystem";

           dstOffset_[RDB_MOTION_SYSTEM_HDF5_SPARE] = HOFFSET(RDB_MOTION_SYSTEM_t, spare);
           dstSizes_ [RDB_MOTION_SYSTEM_HDF5_SPARE] = sizeof(RDB_MOTION_SYSTEM_t::spare);
           fieldType_[RDB_MOTION_SYSTEM_HDF5_SPARE] = uintArray8_;
           fieldNames_[RDB_MOTION_SYSTEM_HDF5_SPARE] = "spare";

           dstOffset_[RDB_MOTION_SYSTEM_HDF5_SPARE1] = HOFFSET(RDB_MOTION_SYSTEM_t, spare1);
           dstSizes_ [RDB_MOTION_SYSTEM_HDF5_SPARE1] = sizeof(RDB_MOTION_SYSTEM_t::spare1);
           fieldType_[RDB_MOTION_SYSTEM_HDF5_SPARE1] = uintArray32_;
           fieldNames_[RDB_MOTION_SYSTEM_HDF5_SPARE1] = "spare1";
        }
}

