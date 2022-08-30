#include <VtdHdf5/Hdf5RdbMessageEngineExt.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessageEngineExt::Hdf5RdbMessageEngineExt() : tableSize_(RDB_ENGINE_EXT_HDF5_NDATA)
        {
            this->initData();
        }

        void Hdf5RdbMessageEngineExt::initData()
        {
            dstSize_ = sizeof(ENRICHED_RDB_ENGINE_EXT);

            dstOffset_[RDB_ENGINE_EXT_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_ENGINE_EXT, frameNumber);
            dstSizes_ [RDB_ENGINE_EXT_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_ENGINE_EXT::frameNumber);
            fieldType_[RDB_ENGINE_EXT_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_ENGINE_EXT_HDF5_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_ENGINE_EXT_HDF5_RPS_START] = HOFFSET(ENRICHED_RDB_ENGINE_EXT, rpsStart);
            dstSizes_ [RDB_ENGINE_EXT_HDF5_RPS_START] = sizeof(ENRICHED_RDB_ENGINE_EXT::rpsStart);
            fieldType_[RDB_ENGINE_EXT_HDF5_RPS_START] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ENGINE_EXT_HDF5_RPS_START] = "rpsStart";

            dstOffset_[RDB_ENGINE_EXT_HDF5_TORQUE] = HOFFSET(ENRICHED_RDB_ENGINE_EXT, torque);
            dstSizes_ [RDB_ENGINE_EXT_HDF5_TORQUE] = sizeof(ENRICHED_RDB_ENGINE_EXT::torque);
            fieldType_[RDB_ENGINE_EXT_HDF5_TORQUE] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ENGINE_EXT_HDF5_TORQUE] = "torque";

            dstOffset_[RDB_ENGINE_EXT_HDF5_TORQUE_INNER] = HOFFSET(ENRICHED_RDB_ENGINE_EXT, torqueInner);
            dstSizes_ [RDB_ENGINE_EXT_HDF5_TORQUE_INNER] = sizeof(ENRICHED_RDB_ENGINE_EXT::torqueInner);
            fieldType_[RDB_ENGINE_EXT_HDF5_TORQUE_INNER] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ENGINE_EXT_HDF5_TORQUE_INNER] = "torqueInner";

            dstOffset_[RDB_ENGINE_EXT_HDF5_TORQUE_MAX] = HOFFSET(ENRICHED_RDB_ENGINE_EXT, torqueMax);
            dstSizes_ [RDB_ENGINE_EXT_HDF5_TORQUE_MAX] = sizeof(ENRICHED_RDB_ENGINE_EXT::torqueMax);
            fieldType_[RDB_ENGINE_EXT_HDF5_TORQUE_MAX] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ENGINE_EXT_HDF5_TORQUE_MAX] = "torqueMax";

            dstOffset_[RDB_ENGINE_EXT_HDF5_TORQUE_FRICTION] = HOFFSET(ENRICHED_RDB_ENGINE_EXT, torqueFriction);
            dstSizes_ [RDB_ENGINE_EXT_HDF5_TORQUE_FRICTION] = sizeof(ENRICHED_RDB_ENGINE_EXT::torqueFriction);
            fieldType_[RDB_ENGINE_EXT_HDF5_TORQUE_FRICTION] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ENGINE_EXT_HDF5_TORQUE_FRICTION] = "torqueFriction";

            dstOffset_[RDB_ENGINE_EXT_HDF5_FUEL_CURRENT] = HOFFSET(ENRICHED_RDB_ENGINE_EXT, fuelCurrent);
            dstSizes_ [RDB_ENGINE_EXT_HDF5_FUEL_CURRENT] = sizeof(ENRICHED_RDB_ENGINE_EXT::fuelCurrent);
            fieldType_[RDB_ENGINE_EXT_HDF5_FUEL_CURRENT] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ENGINE_EXT_HDF5_FUEL_CURRENT] = "fuelCurrent";

            dstOffset_[RDB_ENGINE_EXT_HDF5_FUEL_AVERAGE] = HOFFSET(ENRICHED_RDB_ENGINE_EXT, fuelAverage);
            dstSizes_ [RDB_ENGINE_EXT_HDF5_FUEL_AVERAGE] = sizeof(ENRICHED_RDB_ENGINE_EXT::fuelAverage);
            fieldType_[RDB_ENGINE_EXT_HDF5_FUEL_AVERAGE] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ENGINE_EXT_HDF5_FUEL_AVERAGE] = "fuelAverage";

            dstOffset_[RDB_ENGINE_EXT_HDF5_OIL_TEMPERATURE] = HOFFSET(ENRICHED_RDB_ENGINE_EXT, oilTemperature);
            dstSizes_ [RDB_ENGINE_EXT_HDF5_OIL_TEMPERATURE] = sizeof(ENRICHED_RDB_ENGINE_EXT::oilTemperature);
            fieldType_[RDB_ENGINE_EXT_HDF5_OIL_TEMPERATURE] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ENGINE_EXT_HDF5_OIL_TEMPERATURE] = "oilTemperature";

            dstOffset_[RDB_ENGINE_EXT_HDF5_TEMPERATURE] = HOFFSET(ENRICHED_RDB_ENGINE_EXT, temperature);
            dstSizes_ [RDB_ENGINE_EXT_HDF5_TEMPERATURE] = sizeof(ENRICHED_RDB_ENGINE_EXT::temperature);
            fieldType_[RDB_ENGINE_EXT_HDF5_TEMPERATURE] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ENGINE_EXT_HDF5_TEMPERATURE] = "temperature";
        }

        void Hdf5RdbMessageEngineExt::convertToModifiedStructure(const RDB_ENGINE_EXT_t& data, const uint32_t frameNumber, Hdf5RdbMessageEngineExt::ENRICHED_RDB_ENGINE_EXT& modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.rpsStart = data.rpsStart;
            modifiedData.torque = data.torque;
            modifiedData.torqueInner = data.torqueInner;
            modifiedData.torqueMax = data.torqueMax;
            modifiedData.torqueFriction = data.torqueFriction;
            modifiedData.fuelCurrent = data.fuelCurrent;
            modifiedData.fuelAverage = data.fuelAverage;
            modifiedData.oilTemperature = data.oilTemperature;
            modifiedData.temperature = data.temperature;
        }
}

