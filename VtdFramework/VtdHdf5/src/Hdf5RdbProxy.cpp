#include <VtdHdf5/Hdf5RdbProxy.h>

namespace RdbToHdf5Writer
{
        Hdf5_Rdb_Proxy::Hdf5_Rdb_Proxy() : tableSize_(RDB_PROXY_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5_Rdb_Proxy::~Hdf5_Rdb_Proxy()
        {
            // have to be close memory leak
            H5Tclose(uintArray32_);
        }

        void Hdf5_Rdb_Proxy::initData()
        {
           dimsUInt32_[0] = sizeof(RDB_PROXY_t::spare) / sizeof(uint32_t);
           uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);
      
           dstSize_ = sizeof(RDB_PROXY_t);

           dstOffset_[RDB_PROXY_HDF5_PROTOCOL] = HOFFSET(RDB_PROXY_t, protocol);
           dstSizes_ [RDB_PROXY_HDF5_PROTOCOL] = sizeof(RDB_PROXY_t::protocol);
           fieldType_[RDB_PROXY_HDF5_PROTOCOL] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_PROXY_HDF5_PROTOCOL] = "protocol";

           dstOffset_[RDB_PROXY_HDF5_PKG_ID] = HOFFSET(RDB_PROXY_t, pkgId);
           dstSizes_ [RDB_PROXY_HDF5_PKG_ID] = sizeof(RDB_PROXY_t::pkgId);
           fieldType_[RDB_PROXY_HDF5_PKG_ID] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_PROXY_HDF5_PKG_ID] = "pkgId";

           dstOffset_[RDB_PROXY_HDF5_SPARE] = HOFFSET(RDB_PROXY_t, spare);
           dstSizes_ [RDB_PROXY_HDF5_SPARE] = sizeof(RDB_PROXY_t::spare);
           fieldType_[RDB_PROXY_HDF5_SPARE] = uintArray32_;
           fieldNames_[RDB_PROXY_HDF5_SPARE] = "spare";

           dstOffset_[RDB_PROXY_HDF5_DATA_SIZE] = HOFFSET(RDB_PROXY_t, dataSize);
           dstSizes_ [RDB_PROXY_HDF5_DATA_SIZE] = sizeof(RDB_PROXY_t::dataSize);
           fieldType_[RDB_PROXY_HDF5_DATA_SIZE] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_PROXY_HDF5_DATA_SIZE] = "dataSize";
        }
}

