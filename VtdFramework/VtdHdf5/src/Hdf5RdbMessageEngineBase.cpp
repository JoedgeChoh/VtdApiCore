#include <VtdHdf5/Hdf5RdbMessageEngineBase.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessageEngineBase::Hdf5RdbMessageEngineBase() : tableSize_(RDB_ENGINE_BASE_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbMessageEngineBase::~Hdf5RdbMessageEngineBase()
        {
            H5Tclose(uintArray);
        }

        void Hdf5RdbMessageEngineBase::initData()
        {
            dims[0] = sizeof(ENRICHED_RDB_ENGINE_BASE::spare1) / sizeof(uint32_t);
            
            uintArray = H5Tarray_create(H5T_NATIVE_UINT32, 1, dims);

            dstSize_ = sizeof(ENRICHED_RDB_ENGINE_BASE);

            dstOffset_[RDB_ENGINE_BASE_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_ENGINE_BASE, frameNumber);
            dstSizes_ [RDB_ENGINE_BASE_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_ENGINE_BASE::frameNumber);
            fieldType_[RDB_ENGINE_BASE_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_ENGINE_BASE_HDF5_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_ENGINE_BASE_HDF5_PLAYER_ID] = HOFFSET(ENRICHED_RDB_ENGINE_BASE, playerId);
            dstSizes_ [RDB_ENGINE_BASE_HDF5_PLAYER_ID] = sizeof(ENRICHED_RDB_ENGINE_BASE::playerId);
            fieldType_[RDB_ENGINE_BASE_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_ENGINE_BASE_HDF5_PLAYER_ID] = "playerId";

            dstOffset_[RDB_ENGINE_BASE_HDF5_RPS] = HOFFSET(ENRICHED_RDB_ENGINE_BASE, rps);
            dstSizes_ [RDB_ENGINE_BASE_HDF5_RPS] = sizeof(ENRICHED_RDB_ENGINE_BASE::rps);
            fieldType_[RDB_ENGINE_BASE_HDF5_RPS] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ENGINE_BASE_HDF5_RPS] = "rps";

            dstOffset_[RDB_ENGINE_BASE_HDF5_LOAD] = HOFFSET(ENRICHED_RDB_ENGINE_BASE, load);
            dstSizes_ [RDB_ENGINE_BASE_HDF5_LOAD] = sizeof(ENRICHED_RDB_ENGINE_BASE::load);
            fieldType_[RDB_ENGINE_BASE_HDF5_LOAD] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_ENGINE_BASE_HDF5_LOAD] = "load";

            dstOffset_[RDB_ENGINE_BASE_HDF5_SPARE1] = HOFFSET(ENRICHED_RDB_ENGINE_BASE, spare1);
            dstSizes_ [RDB_ENGINE_BASE_HDF5_SPARE1] = sizeof(ENRICHED_RDB_ENGINE_BASE::spare1);
            fieldType_[RDB_ENGINE_BASE_HDF5_SPARE1] = uintArray;
            fieldNames_[RDB_ENGINE_BASE_HDF5_SPARE1] = "spare1";
        }

        void Hdf5RdbMessageEngineBase::convertToModifiedStructure(const RDB_ENGINE_BASE_t &data, const uint32_t frameNumber, Hdf5RdbMessageEngineBase::ENRICHED_RDB_ENGINE_BASE &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.playerId = data.playerId;
            modifiedData.rps = data.rps;
            modifiedData.load = data.load;
            modifiedData.spare1[0] = data.spare1[0];
            modifiedData.spare1[1] = data.spare1[1];
        }
}

