#include <VtdHdf5/Hdf5RdbMessageEntryHeader.h>

namespace RdbToHdf5Writer
{
    Hdf5RdbMessageEntryHeader:: Hdf5RdbMessageEntryHeader() : tableSize_(RDB_MSG_ENTRY_HDR_HDF5_NDATA)
    {
        this->initData();
    }

    void Hdf5RdbMessageEntryHeader::initData()
    {

        dstSize_ = sizeof(RDB_MSG_ENTRY_HDR_t);

        dstOffset_[RDB_MSG_ENTRY_HDR_HDF5_HEADER_SIZE] = HOFFSET(RDB_MSG_ENTRY_HDR_t, headerSize);
        dstSizes_ [RDB_MSG_ENTRY_HDR_HDF5_HEADER_SIZE] = sizeof(RDB_MSG_ENTRY_HDR_t:: headerSize);
        fieldType_[RDB_MSG_ENTRY_HDR_HDF5_HEADER_SIZE] = H5T_NATIVE_UINT32;
        fieldNames_[RDB_MSG_ENTRY_HDR_HDF5_HEADER_SIZE] = "headerSize";

        dstOffset_[RDB_MSG_ENTRY_HDR_HDF5_DATA_SIZE] = HOFFSET(RDB_MSG_ENTRY_HDR_t, dataSize);
        dstSizes_ [RDB_MSG_ENTRY_HDR_HDF5_DATA_SIZE] = sizeof(RDB_MSG_ENTRY_HDR_t::dataSize);
        fieldType_[RDB_MSG_ENTRY_HDR_HDF5_DATA_SIZE] = H5T_NATIVE_UINT32;
        fieldNames_[RDB_MSG_ENTRY_HDR_HDF5_DATA_SIZE] = "dataSize";

        dstOffset_[RDB_MSG_ENTRY_HDR_HDF5_ELEMENT_SIZE] = HOFFSET(RDB_MSG_ENTRY_HDR_t, elementSize);
        dstSizes_ [RDB_MSG_ENTRY_HDR_HDF5_ELEMENT_SIZE] = sizeof(RDB_MSG_ENTRY_HDR_t::elementSize);
        fieldType_[RDB_MSG_ENTRY_HDR_HDF5_ELEMENT_SIZE] = H5T_NATIVE_UINT32;
        fieldNames_[RDB_MSG_ENTRY_HDR_HDF5_ELEMENT_SIZE] = "elementSize";

        dstOffset_[RDB_MSG_ENTRY_HDR_HDF5_PKG_ID] = HOFFSET(RDB_MSG_ENTRY_HDR_t, pkgId);
        dstSizes_ [RDB_MSG_ENTRY_HDR_HDF5_PKG_ID] = sizeof(RDB_MSG_ENTRY_HDR_t::pkgId);
        fieldType_[RDB_MSG_ENTRY_HDR_HDF5_PKG_ID] = H5T_NATIVE_UINT16;
        fieldNames_[RDB_MSG_ENTRY_HDR_HDF5_PKG_ID] = "pkgId";

        dstOffset_[RDB_MSG_ENTRY_HDR_HDF5_FLAGS] = HOFFSET(RDB_MSG_ENTRY_HDR_t, flags);
        dstSizes_ [RDB_MSG_ENTRY_HDR_HDF5_FLAGS] = sizeof(RDB_MSG_ENTRY_HDR_t::flags);
        fieldType_[RDB_MSG_ENTRY_HDR_HDF5_FLAGS] = H5T_NATIVE_UINT16;
        fieldNames_[RDB_MSG_ENTRY_HDR_HDF5_FLAGS] = "flags";
    }
}

