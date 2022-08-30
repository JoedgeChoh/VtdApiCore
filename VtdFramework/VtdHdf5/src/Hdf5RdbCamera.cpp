#include <VtdHdf5/Hdf5RdbCamera.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbCamera::Hdf5RdbCamera () : tableSize_(RDB_CAMERA_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbCamera ::~Hdf5RdbCamera ()
        {
            // have to be close memory leak
            H5Tclose(uintArray32_);
        }

        void Hdf5RdbCamera ::initData()
        {
           dimsUInt32_[0] = sizeof(RDB_CAMERA_t::spare1) / sizeof(uint32_t);
           uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);
            
           dstSize_ = sizeof(RDB_CAMERA_t);

           dstOffset_[RDB_CAMERA_HDF5_ID] = HOFFSET(RDB_CAMERA_t, id);
           dstSizes_ [RDB_CAMERA_HDF5_ID] = sizeof(RDB_CAMERA_t::id);
           fieldType_[RDB_CAMERA_HDF5_ID] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_CAMERA_HDF5_ID] = "id";

           dstOffset_[RDB_CAMERA_HDF5_WIDTH] = HOFFSET(RDB_CAMERA_t, width);
           dstSizes_ [RDB_CAMERA_HDF5_WIDTH] = sizeof(RDB_CAMERA_t::width);
           fieldType_[RDB_CAMERA_HDF5_WIDTH] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_CAMERA_HDF5_WIDTH] = "width";

           dstOffset_[RDB_CAMERA_HDF5_WIDTH] = HOFFSET(RDB_CAMERA_t, height);
           dstSizes_ [RDB_CAMERA_HDF5_WIDTH] = sizeof(RDB_CAMERA_t::height);
           fieldType_[RDB_CAMERA_HDF5_WIDTH] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_CAMERA_HDF5_WIDTH] = "height";

           dstOffset_[RDB_CAMERA_HDF5_SPARE0] = HOFFSET(RDB_CAMERA_t, spare0);
           dstSizes_ [RDB_CAMERA_HDF5_SPARE0] = sizeof(RDB_CAMERA_t::spare0);
           fieldType_[RDB_CAMERA_HDF5_SPARE0] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_CAMERA_HDF5_SPARE0] = "spare0";

           dstOffset_[RDB_CAMERA_HDF5_CLIP_NEAR] = HOFFSET(RDB_CAMERA_t, clipNear);
           dstSizes_ [RDB_CAMERA_HDF5_CLIP_NEAR] = sizeof(RDB_CAMERA_t::clipNear);
           fieldType_[RDB_CAMERA_HDF5_CLIP_NEAR] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_CAMERA_HDF5_CLIP_NEAR] = "clipNear";

           dstOffset_[RDB_CAMERA_HDF5_CLIP_FAR] = HOFFSET(RDB_CAMERA_t, clipFar);
           dstSizes_ [RDB_CAMERA_HDF5_CLIP_FAR] = sizeof(RDB_CAMERA_t::clipFar);
           fieldType_[RDB_CAMERA_HDF5_CLIP_FAR] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_CAMERA_HDF5_CLIP_FAR] = "clipFar";

           dstOffset_[RDB_CAMERA_HDF5_FOCAL_X] = HOFFSET(RDB_CAMERA_t, focalX);
           dstSizes_ [RDB_CAMERA_HDF5_FOCAL_X] = sizeof(RDB_CAMERA_t::focalX);
           fieldType_[RDB_CAMERA_HDF5_FOCAL_X] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_CAMERA_HDF5_FOCAL_X] = "focalX";

           dstOffset_[RDB_CAMERA_HDF5_FOCAL_Y] = HOFFSET(RDB_CAMERA_t, focalY);
           dstSizes_ [RDB_CAMERA_HDF5_FOCAL_Y] = sizeof(RDB_CAMERA_t::focalY);
           fieldType_[RDB_CAMERA_HDF5_FOCAL_Y] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_CAMERA_HDF5_FOCAL_Y] = "focalY";

           dstOffset_[RDB_CAMERA_HDF5_PRINCIPAL_X] = HOFFSET(RDB_CAMERA_t, principalX);
           dstSizes_ [RDB_CAMERA_HDF5_PRINCIPAL_X] = sizeof(RDB_CAMERA_t::principalX);
           fieldType_[RDB_CAMERA_HDF5_PRINCIPAL_X] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_CAMERA_HDF5_PRINCIPAL_X] = "principalX";

           dstOffset_[RDB_CAMERA_HDF5_PRINCIPAL_Y] = HOFFSET(RDB_CAMERA_t, principalY);
           dstSizes_ [RDB_CAMERA_HDF5_PRINCIPAL_Y] = sizeof(RDB_CAMERA_t::principalY);
           fieldType_[RDB_CAMERA_HDF5_PRINCIPAL_Y] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_CAMERA_HDF5_PRINCIPAL_Y] = "principalY";

           dstOffset_[RDB_CAMERA_HDF5_SPARE1] = HOFFSET(RDB_CAMERA_t, spare1);
           dstSizes_ [RDB_CAMERA_HDF5_SPARE1] = sizeof(RDB_CAMERA_t::spare1);
           fieldType_[RDB_CAMERA_HDF5_SPARE1] = uintArray32_;
           fieldNames_[RDB_CAMERA_HDF5_SPARE1] = "spare1";
        }
}

