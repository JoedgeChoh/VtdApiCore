#include <VtdHdf5/Hdf5RdbMessageDrivetrainBase.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessageDrivetrainBase::Hdf5RdbMessageDrivetrainBase() : tableSize_(RDB_DRIVETRAIN_BASE_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbMessageDrivetrainBase::~Hdf5RdbMessageDrivetrainBase()
        {
            // have to be close memory leak
            H5Tclose(uintArray_);
        }

        void Hdf5RdbMessageDrivetrainBase::initData()
        {
            dims_[0] = sizeof(RDB_DRIVETRAIN_BASE_t::spare1) / sizeof(uint32_t);
            
            uintArray_ = H5Tarray_create (H5T_NATIVE_UINT32, 1, dims_);
            
            dstSize_ = sizeof(RDB_DRIVETRAIN_BASE_t);

            dstOffset_[RDB_DRIVETRAIN_BASE_HDF5_PLAYER_ID] = HOFFSET(RDB_DRIVETRAIN_BASE_t, playerId);
            dstSizes_ [RDB_DRIVETRAIN_BASE_HDF5_PLAYER_ID] = sizeof(RDB_DRIVETRAIN_BASE_t::playerId);
            fieldType_[RDB_DRIVETRAIN_BASE_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_DRIVETRAIN_BASE_HDF5_PLAYER_ID] = "playerId";

            dstOffset_[RDB_DRIVETRAIN_BASE_HDF5_GEAR_BOX_TYPE] = HOFFSET(RDB_DRIVETRAIN_BASE_t, gearBoxType);
            dstSizes_ [RDB_DRIVETRAIN_BASE_HDF5_GEAR_BOX_TYPE] = sizeof(RDB_DRIVETRAIN_BASE_t::gearBoxType);
            fieldType_[RDB_DRIVETRAIN_BASE_HDF5_GEAR_BOX_TYPE] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_DRIVETRAIN_BASE_HDF5_GEAR_BOX_TYPE] = "gearBoxType";

            dstOffset_[RDB_DRIVETRAIN_BASE_HDF5_DRIVE_TRAIN_TYPE] = HOFFSET(RDB_DRIVETRAIN_BASE_t, driveTrainType);
            dstSizes_ [RDB_DRIVETRAIN_BASE_HDF5_DRIVE_TRAIN_TYPE] = sizeof(RDB_DRIVETRAIN_BASE_t::driveTrainType);
            fieldType_[RDB_DRIVETRAIN_BASE_HDF5_DRIVE_TRAIN_TYPE] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_DRIVETRAIN_BASE_HDF5_DRIVE_TRAIN_TYPE] = "driveTrainType";

            dstOffset_[RDB_DRIVETRAIN_BASE_HDF5_GEAR] = HOFFSET(RDB_DRIVETRAIN_BASE_t, gear);
            dstSizes_ [RDB_DRIVETRAIN_BASE_HDF5_GEAR] = sizeof(RDB_DRIVETRAIN_BASE_t::gear);
            fieldType_[RDB_DRIVETRAIN_BASE_HDF5_GEAR] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_DRIVETRAIN_BASE_HDF5_GEAR] = "gear";

            dstOffset_[RDB_DRIVETRAIN_BASE_HDF5_SPARE0] = HOFFSET(RDB_DRIVETRAIN_BASE_t, spare0);
            dstSizes_ [RDB_DRIVETRAIN_BASE_HDF5_SPARE0] = sizeof(RDB_DRIVETRAIN_BASE_t::spare0);
            fieldType_[RDB_DRIVETRAIN_BASE_HDF5_SPARE0] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_DRIVETRAIN_BASE_HDF5_SPARE0] = "spare0";

            dstOffset_[RDB_DRIVETRAIN_BASE_HDF5_SPARE1] = HOFFSET(RDB_DRIVETRAIN_BASE_t, spare1);
            dstSizes_ [RDB_DRIVETRAIN_BASE_HDF5_SPARE1] = sizeof(RDB_DRIVETRAIN_BASE_t::spare1);
            fieldType_[RDB_DRIVETRAIN_BASE_HDF5_SPARE1] = uintArray_;
            fieldNames_[RDB_DRIVETRAIN_BASE_HDF5_SPARE1] = "spare1";
        }
}

