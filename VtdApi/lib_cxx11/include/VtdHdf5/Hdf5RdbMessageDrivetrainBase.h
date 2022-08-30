#ifndef _RDB_HDF5_MESSAGE_RDB_DRIVETRAIN_BASE_H
#define _RDB_HDF5_MESSAGE_RDB_DRIVETRAIN_BASE_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageDrivetrainBase
    {
        
    public:
        
        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_DRIVETRAIN_BASE_HDF5 { RDB_DRIVETRAIN_BASE_HDF5_PLAYER_ID, RDB_DRIVETRAIN_BASE_HDF5_GEAR_BOX_TYPE, RDB_DRIVETRAIN_BASE_HDF5_DRIVE_TRAIN_TYPE
                                      , RDB_DRIVETRAIN_BASE_HDF5_GEAR, RDB_DRIVETRAIN_BASE_HDF5_SPARE0, RDB_DRIVETRAIN_BASE_HDF5_SPARE1
                                      , RDB_DRIVETRAIN_BASE_HDF5_NDATA}; // drive train base
        
        Hdf5RdbMessageDrivetrainBase();

        virtual ~Hdf5RdbMessageDrivetrainBase();

        void initData();

    public:
        
        hsize_t  dims_[1];
        size_t dstOffset_[RDB_DRIVETRAIN_BASE_HDF5_NDATA];
        size_t dstSizes_[RDB_DRIVETRAIN_BASE_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_DRIVETRAIN_BASE_HDF5_NDATA];
        hid_t fieldType_[RDB_DRIVETRAIN_BASE_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t uintArray_;
        
    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
