#include <VtdHdf5/Hdf5RdbLightSourceBase.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbLightSourceBase::Hdf5RdbLightSourceBase () : tableSize_(RDB_LIGHT_SOURCE_BASE_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbLightSourceBase::~Hdf5RdbLightSourceBase()
        {
            // have to be close memory leak
            H5Tclose(intArray32_);
        }

        void Hdf5RdbLightSourceBase::initData()
        {
            dimsInt32_[0] = sizeof(RDB_LIGHT_SOURCE_BASE_t::spare1) / sizeof(int32_t);
  
            intArray32_ = H5Tarray_create(H5T_NATIVE_INT32, 1, dimsInt32_);
            
           dstSize_ = sizeof(RDB_LIGHT_SOURCE_BASE_t);

           dstOffset_[RDB_LIGHT_SOURCE_BASE_HDF5_ID] = HOFFSET(RDB_LIGHT_SOURCE_BASE_t , id);
           dstSizes_ [RDB_LIGHT_SOURCE_BASE_HDF5_ID] = sizeof(RDB_LIGHT_SOURCE_BASE_t::id);
           fieldType_[RDB_LIGHT_SOURCE_BASE_HDF5_ID] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_LIGHT_SOURCE_BASE_HDF5_ID] = "id";

           dstOffset_[RDB_LIGHT_SOURCE_BASE_HDF5_TEMPLATE_ID] = HOFFSET(RDB_LIGHT_SOURCE_BASE_t, templateId);
           dstSizes_ [RDB_LIGHT_SOURCE_BASE_HDF5_TEMPLATE_ID] = sizeof(RDB_LIGHT_SOURCE_BASE_t::templateId);
           fieldType_[RDB_LIGHT_SOURCE_BASE_HDF5_TEMPLATE_ID] = H5T_NATIVE_INT8;
           fieldNames_[RDB_LIGHT_SOURCE_BASE_HDF5_TEMPLATE_ID] = "templateId";

           dstOffset_[RDB_LIGHT_SOURCE_BASE_HDF5_STATE] = HOFFSET(RDB_LIGHT_SOURCE_BASE_t, state);
           dstSizes_ [RDB_LIGHT_SOURCE_BASE_HDF5_STATE] = sizeof(RDB_LIGHT_SOURCE_BASE_t::state);
           fieldType_[RDB_LIGHT_SOURCE_BASE_HDF5_STATE] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_LIGHT_SOURCE_BASE_HDF5_STATE] = "state";

           dstOffset_[RDB_LIGHT_SOURCE_BASE_HDF5_PLAYER_ID] = HOFFSET(RDB_LIGHT_SOURCE_BASE_t , playerId);
           dstSizes_ [RDB_LIGHT_SOURCE_BASE_HDF5_PLAYER_ID] = sizeof(RDB_LIGHT_SOURCE_BASE_t::playerId);
           fieldType_[RDB_LIGHT_SOURCE_BASE_HDF5_PLAYER_ID] = H5T_NATIVE_INT32;
           fieldNames_[RDB_LIGHT_SOURCE_BASE_HDF5_PLAYER_ID] = "playerId";

           dstOffset_[RDB_LIGHT_SOURCE_BASE_HDF5_FLAGS] = HOFFSET(RDB_LIGHT_SOURCE_BASE_t, flags);
           dstSizes_ [RDB_LIGHT_SOURCE_BASE_HDF5_FLAGS] = sizeof(RDB_LIGHT_SOURCE_BASE_t::flags);
           fieldType_[RDB_LIGHT_SOURCE_BASE_HDF5_FLAGS] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_LIGHT_SOURCE_BASE_HDF5_FLAGS] = "flags";

           dstOffset_[RDB_LIGHT_SOURCE_BASE_HDF5_SPARE0] = HOFFSET(RDB_LIGHT_SOURCE_BASE_t, spare0);
           dstSizes_ [RDB_LIGHT_SOURCE_BASE_HDF5_SPARE0] = sizeof(RDB_LIGHT_SOURCE_BASE_t::spare0);
           fieldType_[RDB_LIGHT_SOURCE_BASE_HDF5_SPARE0] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_LIGHT_SOURCE_BASE_HDF5_SPARE0] = "spare0";

           dstOffset_[RDB_LIGHT_SOURCE_BASE_HDF5_SPARE1] = HOFFSET(RDB_LIGHT_SOURCE_BASE_t , spare1);
           dstSizes_ [RDB_LIGHT_SOURCE_BASE_HDF5_SPARE1] = sizeof(RDB_LIGHT_SOURCE_BASE_t::spare1);
           fieldType_[RDB_LIGHT_SOURCE_BASE_HDF5_SPARE1] = intArray32_;
           fieldNames_[RDB_LIGHT_SOURCE_BASE_HDF5_SPARE1] = "spare1";
        }

}

