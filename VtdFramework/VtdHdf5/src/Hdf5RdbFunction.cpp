#include <VtdHdf5/Hdf5RdbFunction.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbFunction ::Hdf5RdbFunction() : tableSize_(RDB_FUNCTION_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbFunction ::~Hdf5RdbFunction ()
        {
            // have to be close memory leak
            H5Tclose(uintArray32_);
        }

        void Hdf5RdbFunction ::initData()
        {
           dimsUInt32_[0] = sizeof(RDB_FUNCTION_t::spare1) / sizeof(uint32_t);
           uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);
      
           dstSize_ = sizeof(RDB_FUNCTION_t);

           dstOffset_[RDB_FUNCTION_HDF5_ID] = HOFFSET(RDB_FUNCTION_t, id);
           dstSizes_ [RDB_FUNCTION_HDF5_ID] = sizeof(RDB_FUNCTION_t::id);
           fieldType_[RDB_FUNCTION_HDF5_ID] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_FUNCTION_HDF5_ID] = "id";

           dstOffset_[RDB_FUNCTION_HDF5_TYPE] = HOFFSET(RDB_FUNCTION_t, type);
           dstSizes_ [RDB_FUNCTION_HDF5_TYPE] = sizeof(RDB_FUNCTION_t::type);
           fieldType_[RDB_FUNCTION_HDF5_TYPE] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_FUNCTION_HDF5_TYPE] = "type";

           dstOffset_[RDB_FUNCTION_HDF5_DIMENSION] = HOFFSET(RDB_FUNCTION_t, dimension);
           dstSizes_ [RDB_FUNCTION_HDF5_DIMENSION] = sizeof(RDB_FUNCTION_t::dimension);
           fieldType_[RDB_FUNCTION_HDF5_DIMENSION] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_FUNCTION_HDF5_DIMENSION] = "dimension";

           dstOffset_[RDB_FUNCTION_HDF5_SPARE] = HOFFSET(RDB_FUNCTION_t, spare);
           dstSizes_ [RDB_FUNCTION_HDF5_SPARE] = sizeof(RDB_FUNCTION_t::spare);
           fieldType_[RDB_FUNCTION_HDF5_SPARE] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_FUNCTION_HDF5_SPARE] = "spare";

           dstOffset_[RDB_FUNCTION_HDF5_DATA_SIZE] = HOFFSET(RDB_FUNCTION_t, dataSize);
           dstSizes_ [RDB_FUNCTION_HDF5_DATA_SIZE] = sizeof(RDB_FUNCTION_t::dataSize);
           fieldType_[RDB_FUNCTION_HDF5_DATA_SIZE] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_FUNCTION_HDF5_DATA_SIZE] = "dataSize";

           dstOffset_[RDB_FUNCTION_HDF5_SPARE1] = HOFFSET(RDB_FUNCTION_t, spare1);
           dstSizes_ [RDB_FUNCTION_HDF5_SPARE1] = sizeof(RDB_FUNCTION_t::spare1);
           fieldType_[RDB_FUNCTION_HDF5_SPARE1] = uintArray32_;
           fieldNames_[RDB_FUNCTION_HDF5_SPARE1] = "spare1";
        }

}

