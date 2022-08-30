#include <VtdHdf5/Hdf5RdbTrafficLightBase.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbTrafficLightBase::Hdf5RdbTrafficLightBase() : tableSize_(RDB_TRAFFIC_LIGHT_BASE_HDF5_NDATA)
        {
            this->initData();
        }

        void Hdf5RdbTrafficLightBase::initData()
        {

            dstSize_ = sizeof(ENRICHED_RDB_TRAFFIC_LIGHT_BASE);

            dstOffset_[RDB_TRAFFIC_LIGHT_BASE_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_TRAFFIC_LIGHT_BASE, frameNumber);
            dstSizes_ [RDB_TRAFFIC_LIGHT_BASE_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_TRAFFIC_LIGHT_BASE::frameNumber);
            fieldType_[RDB_TRAFFIC_LIGHT_BASE_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_TRAFFIC_LIGHT_BASE_HDF5_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_TRAFFIC_LIGHT_BASE_HDF5_ID] = HOFFSET(ENRICHED_RDB_TRAFFIC_LIGHT_BASE, id);
            dstSizes_ [RDB_TRAFFIC_LIGHT_BASE_HDF5_ID] = sizeof(ENRICHED_RDB_TRAFFIC_LIGHT_BASE::id);
            fieldType_[RDB_TRAFFIC_LIGHT_BASE_HDF5_ID] = H5T_NATIVE_INT32;
            fieldNames_[RDB_TRAFFIC_LIGHT_BASE_HDF5_ID] = "id";

            dstOffset_[RDB_TRAFFIC_LIGHT_BASE_HDF5_STATE] = HOFFSET(ENRICHED_RDB_TRAFFIC_LIGHT_BASE, state);
            dstSizes_ [RDB_TRAFFIC_LIGHT_BASE_HDF5_STATE] = sizeof(ENRICHED_RDB_TRAFFIC_LIGHT_BASE::state);
            fieldType_[RDB_TRAFFIC_LIGHT_BASE_HDF5_STATE] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_TRAFFIC_LIGHT_BASE_HDF5_STATE] = "state";

            dstOffset_[RDB_TRAFFIC_LIGHT_BASE_HDF5_STATE_MASK] = HOFFSET(ENRICHED_RDB_TRAFFIC_LIGHT_BASE, stateMask);
            dstSizes_ [RDB_TRAFFIC_LIGHT_BASE_HDF5_STATE_MASK] = sizeof(ENRICHED_RDB_TRAFFIC_LIGHT_BASE::stateMask);
            fieldType_[RDB_TRAFFIC_LIGHT_BASE_HDF5_STATE_MASK] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_TRAFFIC_LIGHT_BASE_HDF5_STATE_MASK] = "stateMask";
        }

        void Hdf5RdbTrafficLightBase::convertToModifiedStructure(const RDB_TRAFFIC_LIGHT_BASE_t &data, const uint32_t frameNumber, Hdf5RdbTrafficLightBase::ENRICHED_RDB_TRAFFIC_LIGHT_BASE &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.id = data.id;
            modifiedData.state = data.state;
            modifiedData.stateMask = data.stateMask;
        }
}

