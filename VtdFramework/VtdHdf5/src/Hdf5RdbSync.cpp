#include <VtdHdf5/Hdf5RdbSync.h>

namespace RdbToHdf5Writer
{
    Hdf5RdbSync::Hdf5RdbSync() : tableSize_(RDB_SYNC_HDF5_NDATA)
    {
        this->initData();
    }

    void Hdf5RdbSync::initData()
    {
       dstSize_ = sizeof(ENRICHED_RDB_SYNC);

       dstOffset_[RDB_SYNC_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_SYNC, frameNumber);
       dstSizes_ [RDB_SYNC_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_SYNC::frameNumber);
       fieldType_[RDB_SYNC_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
       fieldNames_[RDB_SYNC_HDF5_FRAME_NUMBER] = "frameNumber";

       dstOffset_[RDB_SYNC_HDF5_MASK] = HOFFSET(ENRICHED_RDB_SYNC, mask);
       dstSizes_ [RDB_SYNC_HDF5_MASK] = sizeof(ENRICHED_RDB_SYNC::mask);
       fieldType_[RDB_SYNC_HDF5_MASK] = H5T_NATIVE_UINT32;
       fieldNames_[RDB_SYNC_HDF5_MASK] = "mask";

       dstOffset_[RDB_SYNC_HDF5_CMD_MASK] = HOFFSET(ENRICHED_RDB_SYNC, cmdMask);
       dstSizes_ [RDB_SYNC_HDF5_CMD_MASK] = sizeof(ENRICHED_RDB_SYNC::cmdMask);
       fieldType_[RDB_SYNC_HDF5_CMD_MASK] = H5T_NATIVE_UINT32;
       fieldNames_[RDB_SYNC_HDF5_CMD_MASK] = "cmdMask";

       dstOffset_[RDB_SYNC_HDF5_SYSTEM_TIME] = HOFFSET(ENRICHED_RDB_SYNC, systemTime);
       dstSizes_ [RDB_SYNC_HDF5_SYSTEM_TIME] = sizeof(ENRICHED_RDB_SYNC::systemTime);
       fieldType_[RDB_SYNC_HDF5_SYSTEM_TIME] = H5T_NATIVE_DOUBLE;
       fieldNames_[RDB_SYNC_HDF5_SYSTEM_TIME] = "systemTime";
    }

    void Hdf5RdbSync::convertToModifiedStructure(const RDB_SYNC_t &data, const uint32_t frameNumber, Hdf5RdbSync::ENRICHED_RDB_SYNC &modifiedData)
    {
        modifiedData.frameNumber = frameNumber;
        modifiedData.mask = data.mask;
        modifiedData.cmdMask = data.cmdMask;
        modifiedData.systemTime = data.systemTime;
    }
}

