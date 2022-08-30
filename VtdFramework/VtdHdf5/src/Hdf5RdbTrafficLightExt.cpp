#include <VtdHdf5/Hdf5RdbTrafficLightExt.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbTrafficLightExt::Hdf5RdbTrafficLightExt() : tableSize_(RDB_TRAFFIC_LIGHT_EXT_HDF5_NDATA)
        {
            this->initData();
        }

        void Hdf5RdbTrafficLightExt::initData()
        {
           dstSize_ = sizeof(ENRICHED_RDB_TRAFFIC_LIGHT_EXT);

           dstOffset_[RDB_TRAFFIC_LIGHT_EXT_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_TRAFFIC_LIGHT_EXT, frameNumber);
           dstSizes_ [RDB_TRAFFIC_LIGHT_EXT_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_TRAFFIC_LIGHT_EXT::frameNumber);
           fieldType_[RDB_TRAFFIC_LIGHT_EXT_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_TRAFFIC_LIGHT_EXT_HDF5_FRAME_NUMBER] = "frameNumber";

           dstOffset_[RDB_TRAFFIC_LIGHT_EXT_HDF5_CTRL_ID] = HOFFSET(ENRICHED_RDB_TRAFFIC_LIGHT_EXT, ctrlId);
           dstSizes_ [RDB_TRAFFIC_LIGHT_EXT_HDF5_CTRL_ID] = sizeof(ENRICHED_RDB_TRAFFIC_LIGHT_EXT::ctrlId);
           fieldType_[RDB_TRAFFIC_LIGHT_EXT_HDF5_CTRL_ID] = H5T_NATIVE_INT32;
           fieldNames_[RDB_TRAFFIC_LIGHT_EXT_HDF5_CTRL_ID] = "ctrlId";

           dstOffset_[RDB_TRAFFIC_LIGHT_EXT_HDF5_CYCLE_TIME] = HOFFSET(ENRICHED_RDB_TRAFFIC_LIGHT_EXT, cycleTime);
           dstSizes_ [RDB_TRAFFIC_LIGHT_EXT_HDF5_CYCLE_TIME] = sizeof(ENRICHED_RDB_TRAFFIC_LIGHT_EXT::cycleTime);
           fieldType_[RDB_TRAFFIC_LIGHT_EXT_HDF5_CYCLE_TIME] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_TRAFFIC_LIGHT_EXT_HDF5_CYCLE_TIME] = "cycleTime";

           dstOffset_[RDB_TRAFFIC_LIGHT_EXT_HDF5_NO_PHASE] = HOFFSET(ENRICHED_RDB_TRAFFIC_LIGHT_EXT, noPhases);
           dstSizes_ [RDB_TRAFFIC_LIGHT_EXT_HDF5_NO_PHASE] = sizeof(ENRICHED_RDB_TRAFFIC_LIGHT_EXT::noPhases);
           fieldType_[RDB_TRAFFIC_LIGHT_EXT_HDF5_NO_PHASE] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_TRAFFIC_LIGHT_EXT_HDF5_NO_PHASE] = "noPhases";

           dstOffset_[RDB_TRAFFIC_LIGHT_EXT_HDF5_DATA_SIZE] = HOFFSET(ENRICHED_RDB_TRAFFIC_LIGHT_EXT, dataSize);
           dstSizes_ [RDB_TRAFFIC_LIGHT_EXT_HDF5_DATA_SIZE] = sizeof(ENRICHED_RDB_TRAFFIC_LIGHT_EXT::dataSize);
           fieldType_[RDB_TRAFFIC_LIGHT_EXT_HDF5_DATA_SIZE] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_TRAFFIC_LIGHT_EXT_HDF5_DATA_SIZE] = "dataSize";
        }

        void Hdf5RdbTrafficLightExt::convertToModifiedStructure(const RDB_TRAFFIC_LIGHT_EXT_t &data, const uint32_t frameNumber, Hdf5RdbTrafficLightExt::ENRICHED_RDB_TRAFFIC_LIGHT_EXT &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.ctrlId = data.ctrlId;
            modifiedData.cycleTime = data.cycleTime;
            modifiedData.noPhases = data.noPhases;
            modifiedData.dataSize = data.dataSize;
        }
}

