#include <VtdHdf5/Hdf5RdbLightSourceExt.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbLightSourceExt::Hdf5RdbLightSourceExt () : tableSize_(RDB_LIGHT_SOURCE_EXT_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbLightSourceExt::~Hdf5RdbLightSourceExt()
        {
            // have to be close memory leak
            H5Tclose(intArray32_);
            H5Tclose(arrayFloat4_);
            H5Tclose(arrayFloat3_);
            H5Tclose(arrayFloat2_);
        }

        void Hdf5RdbLightSourceExt::initData()
        {
           dimsInt32_[0] = sizeof(RDB_LIGHT_SOURCE_EXT_t::spare1) / sizeof(int32_t);
           intArray32_ = H5Tarray_create(H5T_NATIVE_INT32, 1, dimsInt32_);
            
           dimsFloat2_[0] = sizeof(RDB_LIGHT_SOURCE_EXT_t::nearFar) / sizeof(float);
           arrayFloat2_ = H5Tarray_create(H5T_NATIVE_FLOAT, 1, dimsFloat2_);
           
           dimsFloat3_[0] = sizeof(RDB_LIGHT_SOURCE_EXT_t::atten) / sizeof(float);
           arrayFloat3_ = H5Tarray_create(H5T_NATIVE_FLOAT, 1, dimsFloat3_);
            
           dimsFloat4_[0] = sizeof(RDB_LIGHT_SOURCE_EXT_t::frustumLRBT) / sizeof(float);
           arrayFloat4_ = H5Tarray_create(H5T_NATIVE_FLOAT, 1, dimsFloat4_);
           
           dstSize_ = sizeof(RDB_LIGHT_SOURCE_EXT_t);

           dstOffset_[RDB_LIGHT_SOURCE_EXT_HDF5_NEAR_FAR] = HOFFSET(RDB_LIGHT_SOURCE_EXT_t , nearFar);
           dstSizes_ [RDB_LIGHT_SOURCE_EXT_HDF5_NEAR_FAR] = sizeof(RDB_LIGHT_SOURCE_EXT_t::nearFar);
           fieldType_[RDB_LIGHT_SOURCE_EXT_HDF5_NEAR_FAR] = arrayFloat2_;
           fieldNames_[RDB_LIGHT_SOURCE_EXT_HDF5_NEAR_FAR] = "nearFar";

           dstOffset_[RDB_LIGHT_SOURCE_EXT_HDF5_FRUSTUM_LRBT] = HOFFSET(RDB_LIGHT_SOURCE_EXT_t , frustumLRBT);
           dstSizes_ [RDB_LIGHT_SOURCE_EXT_HDF5_FRUSTUM_LRBT] = sizeof(RDB_LIGHT_SOURCE_EXT_t::frustumLRBT);
           fieldType_[RDB_LIGHT_SOURCE_EXT_HDF5_FRUSTUM_LRBT] = arrayFloat4_;
           fieldNames_[RDB_LIGHT_SOURCE_EXT_HDF5_FRUSTUM_LRBT] = "frustumLRBT";

           dstOffset_[RDB_LIGHT_SOURCE_EXT_HDF5_INTENSITY] = HOFFSET(RDB_LIGHT_SOURCE_EXT_t, intensity);
           dstSizes_ [RDB_LIGHT_SOURCE_EXT_HDF5_INTENSITY] = sizeof(RDB_LIGHT_SOURCE_EXT_t::intensity);
           fieldType_[RDB_LIGHT_SOURCE_EXT_HDF5_INTENSITY] = arrayFloat3_;
           fieldNames_[RDB_LIGHT_SOURCE_EXT_HDF5_INTENSITY] = "intensity";

           dstOffset_[RDB_LIGHT_SOURCE_EXT_HDF5_ATTEN] = HOFFSET(RDB_LIGHT_SOURCE_EXT_t, atten);
           dstSizes_ [RDB_LIGHT_SOURCE_EXT_HDF5_ATTEN] = sizeof(RDB_LIGHT_SOURCE_EXT_t::atten);
           fieldType_[RDB_LIGHT_SOURCE_EXT_HDF5_ATTEN] = arrayFloat3_;
           fieldNames_[RDB_LIGHT_SOURCE_EXT_HDF5_ATTEN] = "atten";

           dstOffset_[RDB_LIGHT_SOURCE_EXT_HDF5_SPARE1] = HOFFSET(RDB_LIGHT_SOURCE_EXT_t, spare1);
           dstSizes_ [RDB_LIGHT_SOURCE_EXT_HDF5_SPARE1] = sizeof(RDB_LIGHT_SOURCE_EXT_t::spare1);
           fieldType_[RDB_LIGHT_SOURCE_EXT_HDF5_SPARE1] = intArray32_;
           fieldNames_[RDB_LIGHT_SOURCE_EXT_HDF5_SPARE1] = "spare1";
        }

}

