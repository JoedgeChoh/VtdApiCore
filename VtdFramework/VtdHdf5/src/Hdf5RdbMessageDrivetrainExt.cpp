#include <VtdHdf5/Hdf5RdbMessageDrivetrainExt.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessageDrivetrainExt::Hdf5RdbMessageDrivetrainExt() : tableSize_(RDB_DRIVETRAIN_EXT_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbMessageDrivetrainExt::~Hdf5RdbMessageDrivetrainExt()
        {
            // have to be close memory leak
            H5Tclose(uintArray_);
        }

        void Hdf5RdbMessageDrivetrainExt::initData()
        {
            dims_[0] = sizeof(RDB_DRIVETRAIN_EXT_t::spare1) / sizeof(uint32_t);
            
            uintArray_ = H5Tarray_create (H5T_NATIVE_UINT32, 1, dims_);
            
            dstSize_ = sizeof(RDB_DRIVETRAIN_EXT_t);

            dstOffset_[RDB_DRIVETRAIN_EXT_HDF5_TORQUE_GEAR_BOX_IN] = HOFFSET(RDB_DRIVETRAIN_EXT_t, torqueGearBoxIn);
            dstSizes_ [RDB_DRIVETRAIN_EXT_HDF5_TORQUE_GEAR_BOX_IN] = sizeof(RDB_DRIVETRAIN_EXT_t::torqueGearBoxIn);
            fieldType_[RDB_DRIVETRAIN_EXT_HDF5_TORQUE_GEAR_BOX_IN] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_DRIVETRAIN_EXT_HDF5_TORQUE_GEAR_BOX_IN] = "torqueGearBoxIn";

            dstOffset_[RDB_DRIVETRAIN_EXT_HDF5_TORQUE_CENTRE_DIFF_OUT] = HOFFSET(RDB_DRIVETRAIN_EXT_t, torqueCenterDiffOut);
            dstSizes_ [RDB_DRIVETRAIN_EXT_HDF5_TORQUE_CENTRE_DIFF_OUT] = sizeof(RDB_DRIVETRAIN_EXT_t::torqueCenterDiffOut);
            fieldType_[RDB_DRIVETRAIN_EXT_HDF5_TORQUE_CENTRE_DIFF_OUT] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_DRIVETRAIN_EXT_HDF5_TORQUE_CENTRE_DIFF_OUT] = "torqueCenterDiffOut";

            dstOffset_[RDB_DRIVETRAIN_EXT_HDF5_TORQUE_SHAFT] = HOFFSET(RDB_DRIVETRAIN_EXT_t, torqueShaft);
            dstSizes_ [RDB_DRIVETRAIN_EXT_HDF5_TORQUE_SHAFT] = sizeof(RDB_DRIVETRAIN_EXT_t::torqueShaft);
            fieldType_[RDB_DRIVETRAIN_EXT_HDF5_TORQUE_SHAFT] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_DRIVETRAIN_EXT_HDF5_TORQUE_SHAFT] = "torqueShaft";

            dstOffset_[RDB_DRIVETRAIN_EXT_HDF5_SPARE1] = HOFFSET(RDB_DRIVETRAIN_EXT_t, spare1);
            dstSizes_ [RDB_DRIVETRAIN_EXT_HDF5_SPARE1] = sizeof(RDB_DRIVETRAIN_EXT_t::spare1);
            fieldType_[RDB_DRIVETRAIN_EXT_HDF5_SPARE1] = uintArray_;
            fieldNames_[RDB_DRIVETRAIN_EXT_HDF5_SPARE1] = "spare1";
        }

}

