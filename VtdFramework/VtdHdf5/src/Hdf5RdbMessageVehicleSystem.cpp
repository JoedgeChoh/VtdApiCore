#include <VtdHdf5/Hdf5RdbMessageVehicleSystem.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessageVehicleSystem::Hdf5RdbMessageVehicleSystem() : tableSize_(RDB_VEHICLE_SYSTEM_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbMessageVehicleSystem::~Hdf5RdbMessageVehicleSystem()
        {
            H5Tclose(unitArray_);
        }

        void Hdf5RdbMessageVehicleSystem::initData()
        {

            dims_[0] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::spare) / sizeof(uint32_t);
            
            unitArray_ = H5Tarray_create (H5T_NATIVE_UINT32, 1, dims_);

            dstSize_ = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS);

            dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_VEHICLE_SYSTEMS, frameNumber);
            dstSizes_ [RDB_VEHICLE_SYSTEM_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::frameNumber);
            fieldType_[RDB_VEHICLE_SYSTEM_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_PLAYER_ID] = HOFFSET(ENRICHED_RDB_VEHICLE_SYSTEMS, playerId);
            dstSizes_ [RDB_VEHICLE_SYSTEM_HDF5_PLAYER_ID] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::playerId);
            fieldType_[RDB_VEHICLE_SYSTEM_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_PLAYER_ID] = "playerId";

            dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_LIGHT_MASK] = HOFFSET(ENRICHED_RDB_VEHICLE_SYSTEMS, lightMask);
            dstSizes_ [RDB_VEHICLE_SYSTEM_HDF5_LIGHT_MASK] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::lightMask);
            fieldType_[RDB_VEHICLE_SYSTEM_HDF5_LIGHT_MASK] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_LIGHT_MASK] = "lightMask";

            dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_STEERING] = HOFFSET(ENRICHED_RDB_VEHICLE_SYSTEMS, steering);
            dstSizes_ [RDB_VEHICLE_SYSTEM_HDF5_STEERING] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::steering);
            fieldType_[RDB_VEHICLE_SYSTEM_HDF5_STEERING] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_STEERING] = "steering";

            dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_STEERING_WHEEL_TORQUE] = HOFFSET(ENRICHED_RDB_VEHICLE_SYSTEMS, steeringWheelTorque);
            dstSizes_ [RDB_VEHICLE_SYSTEM_HDF5_STEERING_WHEEL_TORQUE] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::steeringWheelTorque);
            fieldType_[RDB_VEHICLE_SYSTEM_HDF5_STEERING_WHEEL_TORQUE] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_STEERING_WHEEL_TORQUE] = "steeringWheelTorque";

            dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_ACC_MASK] = HOFFSET(ENRICHED_RDB_VEHICLE_SYSTEMS, accMask);
            dstSizes_ [RDB_VEHICLE_SYSTEM_HDF5_ACC_MASK] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::accMask);
            fieldType_[RDB_VEHICLE_SYSTEM_HDF5_ACC_MASK] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_ACC_MASK] = "accMask";

            dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_ACC_SPEED] = HOFFSET(ENRICHED_RDB_VEHICLE_SYSTEMS, accSpeed);
            dstSizes_ [RDB_VEHICLE_SYSTEM_HDF5_ACC_SPEED] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::accSpeed);
            fieldType_[RDB_VEHICLE_SYSTEM_HDF5_ACC_SPEED] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_ACC_SPEED] = "accSpeed";

            dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_BATTERY_STATE] = HOFFSET(ENRICHED_RDB_VEHICLE_SYSTEMS, batteryState);
            dstSizes_ [RDB_VEHICLE_SYSTEM_HDF5_BATTERY_STATE] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::batteryState);
            fieldType_[RDB_VEHICLE_SYSTEM_HDF5_BATTERY_STATE] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_BATTERY_STATE] = "batteryState";

            dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_BATTERY_RATE] = HOFFSET(ENRICHED_RDB_VEHICLE_SYSTEMS, batteryRate);
            dstSizes_ [RDB_VEHICLE_SYSTEM_HDF5_BATTERY_RATE] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::batteryRate);
            fieldType_[RDB_VEHICLE_SYSTEM_HDF5_BATTERY_RATE] = H5T_NATIVE_INT8;
            fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_BATTERY_RATE] = "batteryRate";

            dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_DISPLAY_LIGHT_MASK] = HOFFSET(ENRICHED_RDB_VEHICLE_SYSTEMS, displayLightMask);
            dstSizes_ [RDB_VEHICLE_SYSTEM_HDF5_DISPLAY_LIGHT_MASK] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::displayLightMask);
            fieldType_[RDB_VEHICLE_SYSTEM_HDF5_DISPLAY_LIGHT_MASK] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_DISPLAY_LIGHT_MASK] = "displayLightMask";

            dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_FUEL_GAUGE] = HOFFSET(ENRICHED_RDB_VEHICLE_SYSTEMS, fuelGauge);
            dstSizes_ [RDB_VEHICLE_SYSTEM_HDF5_FUEL_GAUGE] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::fuelGauge);
            fieldType_[RDB_VEHICLE_SYSTEM_HDF5_FUEL_GAUGE] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_FUEL_GAUGE] = "fuelGauge";

            dstOffset_[RDB_VEHICLE_SYSTEM_HDF5_SPARE] = HOFFSET(ENRICHED_RDB_VEHICLE_SYSTEMS, spare);
            dstSizes_ [RDB_VEHICLE_SYSTEM_HDF5_SPARE] = sizeof(ENRICHED_RDB_VEHICLE_SYSTEMS::spare);
            fieldType_[RDB_VEHICLE_SYSTEM_HDF5_SPARE] = unitArray_;
            fieldNames_[RDB_VEHICLE_SYSTEM_HDF5_SPARE] = "spare";
        }

        void Hdf5RdbMessageVehicleSystem::convertToModifiedStructure(const RDB_VEHICLE_SYSTEMS_t &data, const uint32_t frameNumber, Hdf5RdbMessageVehicleSystem::ENRICHED_RDB_VEHICLE_SYSTEMS &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.playerId = data.playerId;
            modifiedData.lightMask = data.lightMask;
            modifiedData.steering = data.steering;
            modifiedData.steeringWheelTorque = data.steeringWheelTorque;
            modifiedData.accMask = data.accMask;
            modifiedData.accSpeed = data.accSpeed;
            modifiedData.batteryState = data.batteryState;
            modifiedData.batteryRate = data.batteryRate;
            modifiedData.displayLightMask = data.displayLightMask;
            modifiedData.fuelGauge = data.fuelGauge;
            modifiedData.spare[0] = data.spare[0];
            modifiedData.spare[1] = data.spare[1];
            modifiedData.spare[2] = data.spare[2];
            modifiedData.spare[3] = data.spare[3];
            modifiedData.spare[4] = data.spare[4];
        }
}

