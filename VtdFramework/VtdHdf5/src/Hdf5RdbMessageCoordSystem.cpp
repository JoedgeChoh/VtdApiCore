#include <VtdHdf5/Hdf5RdbMessageCoordSystem.h>

namespace RdbToHdf5Writer
{

        Hdf5RdbMessageCoordSystem::Hdf5RdbMessageCoordSystem() : tableSize_(RDB_COORD_SYSTEM_NDATA)
        {
            this->initData();
        }

        void Hdf5RdbMessageCoordSystem::initData()
        {
            dstSize_ = sizeof( RDB_COORD_SYSTEM_t);

            dstOffset_[RDB_COORD_SYSTEM_HDF5_ID] = HOFFSET( RDB_COORD_SYSTEM_t, id);
            dstSizes_ [RDB_COORD_SYSTEM_HDF5_ID] = sizeof(RDB_COORD_SYSTEM_t::id);
            fieldType_[RDB_COORD_SYSTEM_HDF5_ID] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_COORD_SYSTEM_HDF5_ID] = "id";

            dstOffset_[RDB_COORD_SYSTEM_HDF5_SPARE] = HOFFSET(RDB_COORD_SYSTEM_t, spare);
            dstSizes_ [RDB_COORD_SYSTEM_HDF5_SPARE] = sizeof(RDB_COORD_SYSTEM_t::spare);
            fieldType_[RDB_COORD_SYSTEM_HDF5_SPARE] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_COORD_SYSTEM_HDF5_SPARE] = "spare";
        }

}

