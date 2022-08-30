#include <VtdHdf5/Hdf5RdbImage.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbImage::Hdf5RdbImage() : tableSize_(RDB_IMAGE_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbImage::~Hdf5RdbImage()
        {
            // have to be close memory leak
            H5Tclose(uintArray8_);
            H5Tclose(uintArray32_);
        }

        void Hdf5RdbImage::initData()
        {
            dimsUInt8_[0] = sizeof(RDB_IMAGE_t::color) / sizeof(uint8_t);
            dimsUInt32_[0] = sizeof(RDB_IMAGE_t::spare1) / sizeof(uint32_t);
            
            uintArray8_ = H5Tarray_create(H5T_NATIVE_UINT8, 1, dimsUInt8_);
            uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);
            
           dstSize_ = sizeof(RDB_IMAGE_t );

           dstOffset_[RDB_IMAGE_HDF5_ID] = HOFFSET(RDB_IMAGE_t , id);
           dstSizes_ [RDB_IMAGE_HDF5_ID] = sizeof(RDB_IMAGE_t::id);
           fieldType_[RDB_IMAGE_HDF5_ID] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_IMAGE_HDF5_ID] = "id";

           dstOffset_[RDB_IMAGE_HDF5_WIDTH] = HOFFSET(RDB_IMAGE_t, width);
           dstSizes_ [RDB_IMAGE_HDF5_WIDTH] = sizeof(RDB_IMAGE_t::width);
           fieldType_[RDB_IMAGE_HDF5_WIDTH] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_IMAGE_HDF5_WIDTH] = "width";

           dstOffset_[RDB_IMAGE_HDF5_HEIGHT] = HOFFSET(RDB_IMAGE_t, height);
           dstSizes_ [RDB_IMAGE_HDF5_HEIGHT] = sizeof(RDB_IMAGE_t::height);
           fieldType_[RDB_IMAGE_HDF5_HEIGHT] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_IMAGE_HDF5_HEIGHT] = "height";

           dstOffset_[RDB_IMAGE_HDF5_PIXEL_SIZE] = HOFFSET(RDB_IMAGE_t, pixelSize);
           dstSizes_ [RDB_IMAGE_HDF5_PIXEL_SIZE] = sizeof(RDB_IMAGE_t::pixelSize);
           fieldType_[RDB_IMAGE_HDF5_PIXEL_SIZE] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_IMAGE_HDF5_PIXEL_SIZE] = "pixelSize";


           dstOffset_[RDB_IMAGE_HDF5_PIXEL_FORMAT] = HOFFSET(RDB_IMAGE_t, pixelFormat);
           dstSizes_ [RDB_IMAGE_HDF5_PIXEL_FORMAT] = sizeof(RDB_IMAGE_t::pixelFormat);
           fieldType_[RDB_IMAGE_HDF5_PIXEL_FORMAT] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_IMAGE_HDF5_PIXEL_FORMAT] = "pixelFormat";

           dstOffset_[RDB_IMAGE_HDF5_CAMERA_ID] = HOFFSET(RDB_IMAGE_t , cameraId);
           dstSizes_ [RDB_IMAGE_HDF5_CAMERA_ID] = sizeof(RDB_IMAGE_t::cameraId);
           fieldType_[RDB_IMAGE_HDF5_CAMERA_ID] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_IMAGE_HDF5_CAMERA_ID] = "cameraId";

           dstOffset_[RDB_IMAGE_HDF5_IMG_SIZE] = HOFFSET(RDB_IMAGE_t, imgSize);
           dstSizes_ [RDB_IMAGE_HDF5_IMG_SIZE] = sizeof(RDB_IMAGE_t::imgSize);
           fieldType_[RDB_IMAGE_HDF5_IMG_SIZE] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_IMAGE_HDF5_IMG_SIZE] = "imgSize";

           dstOffset_[RDB_IMAGE_HDF5_COLOR] = HOFFSET(RDB_IMAGE_t, color);
           dstSizes_ [RDB_IMAGE_HDF5_COLOR] = sizeof(RDB_IMAGE_t::color);
           fieldType_[RDB_IMAGE_HDF5_COLOR] = uintArray8_;
           fieldNames_[RDB_IMAGE_HDF5_COLOR] = "color";

           dstOffset_[RDB_IMAGE_HDF5_SPARE1] = HOFFSET(RDB_IMAGE_t , spare1);
           dstSizes_ [RDB_IMAGE_HDF5_SPARE1] = sizeof(RDB_IMAGE_t::spare1);
           fieldType_[RDB_IMAGE_HDF5_SPARE1] = uintArray32_;
           fieldNames_[RDB_IMAGE_HDF5_SPARE1] = "spare1";
        }

}

