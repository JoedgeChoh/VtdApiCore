#include <VtdHdf5/Hdf5RdbMessageVehicleSetup.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessageVehicleSetup::Hdf5RdbMessageVehicleSetup() : tableSize_(RDB_VEHICLE_SETUP_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbMessageVehicleSetup::~Hdf5RdbMessageVehicleSetup()
        {
            H5Tclose(intArray_);
        }

        void Hdf5RdbMessageVehicleSetup::initData()
        {
            dims_[0] = sizeof(ENRICHED_RDB_VEHICLE_SETUP::spare) / sizeof(int32_t);
            
            intArray_ = H5Tarray_create(H5T_NATIVE_INT32, 1, dims_);

            dstSize_ = sizeof(ENRICHED_RDB_VEHICLE_SETUP);

            dstOffset_[RDB_VEHICLE_SETUP_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_VEHICLE_SETUP, frameNumber);
            dstSizes_ [RDB_VEHICLE_SETUP_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_VEHICLE_SETUP::frameNumber);
            fieldType_[RDB_VEHICLE_SETUP_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_VEHICLE_SETUP_HDF5_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_VEHICLE_SETUP_HDF5_PLAYER_ID] = HOFFSET(ENRICHED_RDB_VEHICLE_SETUP, playerId);
            dstSizes_ [RDB_VEHICLE_SETUP_HDF5_PLAYER_ID] = sizeof(ENRICHED_RDB_VEHICLE_SETUP::playerId);
            fieldType_[RDB_VEHICLE_SETUP_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_VEHICLE_SETUP_HDF5_PLAYER_ID] = "playerId";

            dstOffset_[RDB_VEHICLE_SETUP_HDF5_MASS] = HOFFSET(ENRICHED_RDB_VEHICLE_SETUP, mass);
            dstSizes_ [RDB_VEHICLE_SETUP_HDF5_MASS] = sizeof(ENRICHED_RDB_VEHICLE_SETUP::mass);
            fieldType_[RDB_VEHICLE_SETUP_HDF5_MASS] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_VEHICLE_SETUP_HDF5_MASS] = "mass";

            dstOffset_[RDB_VEHICLE_SETUP_HDF5_WHEEL_BASE] = HOFFSET(ENRICHED_RDB_VEHICLE_SETUP, wheelBase);
            dstSizes_ [RDB_VEHICLE_SETUP_HDF5_WHEEL_BASE] = sizeof(ENRICHED_RDB_VEHICLE_SETUP::wheelBase);
            fieldType_[RDB_VEHICLE_SETUP_HDF5_WHEEL_BASE] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_VEHICLE_SETUP_HDF5_WHEEL_BASE] = "wheelBase";

            dstOffset_[RDB_VEHICLE_SETUP_HDF5_SPARE] = HOFFSET(ENRICHED_RDB_VEHICLE_SETUP, spare);
            dstSizes_ [RDB_VEHICLE_SETUP_HDF5_SPARE] = sizeof(ENRICHED_RDB_VEHICLE_SETUP::spare);
            fieldType_[RDB_VEHICLE_SETUP_HDF5_SPARE] = intArray_;
            fieldNames_[RDB_VEHICLE_SETUP_HDF5_SPARE] = "spare";
        }

        void Hdf5RdbMessageVehicleSetup::convertToModifiedStructure(const RDB_VEHICLE_SETUP_t& data, const uint32_t frameNumber, Hdf5RdbMessageVehicleSetup::ENRICHED_RDB_VEHICLE_SETUP& modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.playerId = data.playerId;
            modifiedData.mass = data.mass;
            modifiedData.wheelBase = data.wheelBase;
            modifiedData.spare[0] = data.spare[0];
            modifiedData.spare[1] = data.spare[1];
            modifiedData.spare[2] = data.spare[2];
            modifiedData.spare[3] = data.spare[3];

        }
}

