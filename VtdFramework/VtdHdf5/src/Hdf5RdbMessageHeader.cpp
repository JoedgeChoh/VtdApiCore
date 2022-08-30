#include <VtdHdf5/Hdf5RdbMessageHeader.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessageHeader::Hdf5RdbMessageHeader() : tableSize_(RDB_MSG_HDR_HDF5_NDATA)
        {
            this->initData();
        }

        void Hdf5RdbMessageHeader::initData()
        {
            dstSize_ = sizeof(RDB_MSG_HDR_t);

            dstOffset_[RDB_MSG_HDR_HDF5_FRAME_NO] = HOFFSET(RDB_MSG_HDR_t, frameNo);
            dstSizes_ [RDB_MSG_HDR_HDF5_FRAME_NO] = sizeof(RDB_MSG_HDR_t::frameNo);
            fieldType_[RDB_MSG_HDR_HDF5_FRAME_NO] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_MSG_HDR_HDF5_FRAME_NO] = "frameNumber";

            dstOffset_[RDB_MSG_HDR_HDF5_SIM_TIME] = HOFFSET(RDB_MSG_HDR_t, simTime);
            dstSizes_ [RDB_MSG_HDR_HDF5_SIM_TIME] = sizeof(RDB_MSG_HDR_t::simTime);
            fieldType_[RDB_MSG_HDR_HDF5_SIM_TIME] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_MSG_HDR_HDF5_SIM_TIME] = "simTime";

            dstOffset_[RDB_MSG_HDR_HDF5_MAGIC_NO] = HOFFSET(RDB_MSG_HDR_t, magicNo);
            dstSizes_ [RDB_MSG_HDR_HDF5_MAGIC_NO] = sizeof(RDB_MSG_HDR_t::magicNo);
            fieldType_[RDB_MSG_HDR_HDF5_MAGIC_NO] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_MSG_HDR_HDF5_MAGIC_NO] = "magicNo";

            dstOffset_[RDB_MSG_HDR_HDF5_VERSION] = HOFFSET(RDB_MSG_HDR_t, version);
            dstSizes_ [RDB_MSG_HDR_HDF5_VERSION] = sizeof(RDB_MSG_HDR_t::version);
            fieldType_[RDB_MSG_HDR_HDF5_VERSION] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_MSG_HDR_HDF5_VERSION] = "version";

            dstOffset_[RDB_MSG_HDR_HDF5_HEADER_SIZE] = HOFFSET(RDB_MSG_HDR_t, headerSize);
            dstSizes_ [RDB_MSG_HDR_HDF5_HEADER_SIZE] = sizeof(RDB_MSG_HDR_t::headerSize);
            fieldType_[RDB_MSG_HDR_HDF5_HEADER_SIZE] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_MSG_HDR_HDF5_HEADER_SIZE] = "headerSize";

            dstOffset_[RDB_MSG_HDR_HDF5_DATA_SIZE] = HOFFSET(RDB_MSG_HDR_t, dataSize);
            dstSizes_ [RDB_MSG_HDR_HDF5_DATA_SIZE] = sizeof(RDB_MSG_HDR_t::dataSize);
            fieldType_[RDB_MSG_HDR_HDF5_DATA_SIZE] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_MSG_HDR_HDF5_DATA_SIZE] = "dataSize";
        }
}

