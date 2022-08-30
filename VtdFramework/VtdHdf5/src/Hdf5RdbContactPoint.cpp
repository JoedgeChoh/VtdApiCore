#include <VtdHdf5/Hdf5RdbContactPoint.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbContactPoint::Hdf5RdbContactPoint() : tableSize_(RDB_CONTACT_POINT_HDF5_NDATA)
        {
            this->initData();
        }

        void Hdf5RdbContactPoint::initData()
        {
            dstSize_ = sizeof(RDB_CONTACT_POINT_t);

            dstOffset_[RDB_CONTACT_POINT_HDF5_ID] = HOFFSET(RDB_CONTACT_POINT_t, id);
            dstSizes_ [RDB_CONTACT_POINT_HDF5_ID] = sizeof(RDB_CONTACT_POINT_t::id);
            fieldType_[RDB_CONTACT_POINT_HDF5_ID] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_CONTACT_POINT_HDF5_ID] = "id";


            dstOffset_[RDB_CONTACT_POINT_HDF5_FLAGS] = HOFFSET(RDB_CONTACT_POINT_t, flags);
            dstSizes_ [RDB_CONTACT_POINT_HDF5_FLAGS] = sizeof(RDB_CONTACT_POINT_t::flags);
            fieldType_[RDB_CONTACT_POINT_HDF5_FLAGS] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_CONTACT_POINT_HDF5_FLAGS] = "flags";

            dstOffset_[RDB_CONTACT_POINT_HDF5_FRICTION] = HOFFSET(RDB_CONTACT_POINT_t, friction);
            dstSizes_ [RDB_CONTACT_POINT_HDF5_FRICTION] = sizeof(RDB_CONTACT_POINT_t::friction);
            fieldType_[RDB_CONTACT_POINT_HDF5_FRICTION] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_CONTACT_POINT_HDF5_FRICTION] = "friction";

            dstOffset_[RDB_CONTACT_POINT_HDF5_PLAYER_ID] = HOFFSET(RDB_CONTACT_POINT_t, playerId);
            dstSizes_ [RDB_CONTACT_POINT_HDF5_PLAYER_ID] = sizeof(RDB_CONTACT_POINT_t::playerId);
            fieldType_[RDB_CONTACT_POINT_HDF5_PLAYER_ID] = H5T_NATIVE_INT32;
            fieldNames_[RDB_CONTACT_POINT_HDF5_PLAYER_ID] = "playerId";

            dstOffset_[RDB_CONTACT_POINT_HDF5_PLAYER_ID] = HOFFSET(RDB_CONTACT_POINT_t, spare1);
            dstSizes_ [RDB_CONTACT_POINT_HDF5_PLAYER_ID] = sizeof(RDB_CONTACT_POINT_t::spare1);
            fieldType_[RDB_CONTACT_POINT_HDF5_PLAYER_ID] = H5T_NATIVE_INT32;
            fieldNames_[RDB_CONTACT_POINT_HDF5_PLAYER_ID] = "spare1";
       }

}

