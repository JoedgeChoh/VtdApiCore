#include <VtdHdf5/Hdf5RdbMessagePedAnimation.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessagePedAnimation::Hdf5RdbMessagePedAnimation() : tableSize_(RDB_PED_ANIMATION_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbMessagePedAnimation::~Hdf5RdbMessagePedAnimation()
        {
            // have to be close memory leak
            H5Tclose(uintArray32_);
        }

        void Hdf5RdbMessagePedAnimation::initData()
        {
            dimsUInt32_[0] = sizeof(RDB_PED_ANIMATION_t::spare) / sizeof(uint32_t);
            
            uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);

            dstSize_ = sizeof(RDB_PED_ANIMATION_t);

            dstOffset_[RDB_PED_ANIMATION_HDF5_PLAYER_ID] = HOFFSET(RDB_PED_ANIMATION_t, playerId);
            dstSizes_ [RDB_PED_ANIMATION_HDF5_PLAYER_ID] = sizeof(RDB_PED_ANIMATION_t::playerId);
            fieldType_[RDB_PED_ANIMATION_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_PED_ANIMATION_HDF5_PLAYER_ID] = "playerId";

            dstOffset_[RDB_PED_ANIMATION_HDF5_SPARE] = HOFFSET(RDB_PED_ANIMATION_t, spare);
            dstSizes_ [RDB_PED_ANIMATION_HDF5_SPARE] = sizeof(RDB_PED_ANIMATION_t::spare);
            fieldType_[RDB_PED_ANIMATION_HDF5_SPARE] = uintArray32_;
            fieldNames_[RDB_PED_ANIMATION_HDF5_SPARE] = "spare";

            dstOffset_[RDB_PED_ANIMATION_HDF5_NO_COORDINATES] = HOFFSET(RDB_PED_ANIMATION_t, noCoords);
            dstSizes_ [RDB_PED_ANIMATION_HDF5_NO_COORDINATES] = sizeof(RDB_PED_ANIMATION_t::noCoords);
            fieldType_[RDB_PED_ANIMATION_HDF5_NO_COORDINATES] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_PED_ANIMATION_HDF5_NO_COORDINATES] = "noCoords";

            dstOffset_[RDB_PED_ANIMATION_HDF5_DATA_SIZE] = HOFFSET(RDB_PED_ANIMATION_t, dataSize);
            dstSizes_ [RDB_PED_ANIMATION_HDF5_DATA_SIZE] = sizeof(RDB_PED_ANIMATION_t::dataSize);
            fieldType_[RDB_PED_ANIMATION_HDF5_DATA_SIZE] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_PED_ANIMATION_HDF5_DATA_SIZE] = "dataSize";
        }
}

