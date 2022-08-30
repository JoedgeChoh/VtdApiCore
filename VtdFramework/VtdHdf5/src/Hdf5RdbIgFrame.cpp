#include <VtdHdf5/Hdf5RdbIgFrame.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbIgFrame::Hdf5RdbIgFrame () : tableSize_(RDB_IG_FRAME_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbIgFrame::~Hdf5RdbIgFrame()
        {
            // have to be close memory leak
            H5Tclose(uintArray32_);
        }

        void Hdf5RdbIgFrame::initData()
        {
           dimsUInt32_[0] = sizeof(RDB_IG_FRAME_t::spare) / sizeof(uint32_t);
           uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);

           dstSize_ = sizeof(RDB_IG_FRAME_t);

           dstOffset_[RDB_IG_FRAME_HDF5_DELTA_T] = HOFFSET(RDB_IG_FRAME_t, deltaT);
           dstSizes_ [RDB_IG_FRAME_HDF5_DELTA_T] = sizeof(RDB_IG_FRAME_t::deltaT);
           fieldType_[RDB_IG_FRAME_HDF5_DELTA_T] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_IG_FRAME_HDF5_DELTA_T] = "deltaT";

           dstOffset_[RDB_IG_FRAME_HDF5_FRAME_NO] = HOFFSET(RDB_IG_FRAME_t, frameNo);
           dstSizes_ [RDB_IG_FRAME_HDF5_FRAME_NO] = sizeof(RDB_IG_FRAME_t::frameNo);
           fieldType_[RDB_IG_FRAME_HDF5_FRAME_NO] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_IG_FRAME_HDF5_FRAME_NO] = "frameNumber";

           dstOffset_[RDB_IG_FRAME_HDF5_SPARE] = HOFFSET(RDB_IG_FRAME_t, spare);
           dstSizes_ [RDB_IG_FRAME_HDF5_SPARE] = sizeof(RDB_IG_FRAME_t::spare);
           fieldType_[RDB_IG_FRAME_HDF5_SPARE] = uintArray32_;
           fieldNames_[RDB_IG_FRAME_HDF5_SPARE] = "spare";
        }
}

