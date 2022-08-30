#include <VtdHdf5/Hdf5RdbMessageCoord.h>

namespace RdbToHdf5Writer
{

       Hdf5RdbMessageCoord::Hdf5RdbMessageCoord() : tableSize_(RDB_COORD_HDF5_NDATA)
        {
            this->initData();
        }

        void Hdf5RdbMessageCoord::initData()
        {
            dstSize_ = sizeof(ENRICHED_RDB_COORD);

            dstOffset_[RDB_COORD_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_COORD, frameNumber);
            dstSizes_ [RDB_COORD_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_COORD::frameNumber);
            fieldType_[RDB_COORD_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_COORD_HDF5_FRAME_NUMBER] = "Frame Number";

            dstOffset_[RDB_COORD_HDF5_X] = HOFFSET(ENRICHED_RDB_COORD, x);
            dstSizes_ [RDB_COORD_HDF5_X] = sizeof(ENRICHED_RDB_COORD::x);
            fieldType_[RDB_COORD_HDF5_X] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_COORD_HDF5_X] = "x";

            dstOffset_[RDB_COORD_HDF5_Y] = HOFFSET(ENRICHED_RDB_COORD, y);
            dstSizes_ [RDB_COORD_HDF5_Y] = sizeof(ENRICHED_RDB_COORD::y);
            fieldType_[RDB_COORD_HDF5_Y] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_COORD_HDF5_Y] = "y";

            dstOffset_[RDB_COORD_HDF5_Z] = HOFFSET(ENRICHED_RDB_COORD, z);
            dstSizes_ [RDB_COORD_HDF5_Z] = sizeof(ENRICHED_RDB_COORD::z);
            fieldType_[RDB_COORD_HDF5_Z] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_COORD_HDF5_Z] = "z";

            dstOffset_[RDB_COORD_HDF5_H] = HOFFSET(ENRICHED_RDB_COORD, h);
            dstSizes_ [RDB_COORD_HDF5_H] = sizeof(ENRICHED_RDB_COORD::h);
            fieldType_[RDB_COORD_HDF5_H] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_COORD_HDF5_H] = "h";

            dstOffset_[RDB_COORD_HDF5_P] = HOFFSET(ENRICHED_RDB_COORD, p);
            dstSizes_ [RDB_COORD_HDF5_P] = sizeof(ENRICHED_RDB_COORD::p);
            fieldType_[RDB_COORD_HDF5_P] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_COORD_HDF5_P] = "p";

            dstOffset_[RDB_COORD_HDF5_R] = HOFFSET(ENRICHED_RDB_COORD, r);
            dstSizes_ [RDB_COORD_HDF5_R] = sizeof(ENRICHED_RDB_COORD::r);
            fieldType_[RDB_COORD_HDF5_R] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_COORD_HDF5_R] = "r";

            dstOffset_[RDB_COORD_HDF5_FLAGS] = HOFFSET(ENRICHED_RDB_COORD, flags);
            dstSizes_ [RDB_COORD_HDF5_FLAGS] = sizeof(ENRICHED_RDB_COORD::flags);
            fieldType_[RDB_COORD_HDF5_FLAGS] = H5T_NATIVE_INT8;
            fieldNames_[RDB_COORD_HDF5_FLAGS] = "flags";

            dstOffset_[RDB_COORD_HDF5_TYPE] = HOFFSET(ENRICHED_RDB_COORD, type);
            dstSizes_ [RDB_COORD_HDF5_TYPE] = sizeof(ENRICHED_RDB_COORD::type);
            fieldType_[RDB_COORD_HDF5_TYPE] = H5T_NATIVE_INT8;
            fieldNames_[RDB_COORD_HDF5_TYPE] = "type";

            dstOffset_[RDB_COORD_HDF5_SYSTEM] = HOFFSET(ENRICHED_RDB_COORD, system);
            dstSizes_ [RDB_COORD_HDF5_SYSTEM] = sizeof(ENRICHED_RDB_COORD::system);
            fieldType_[RDB_COORD_HDF5_SYSTEM] = H5T_NATIVE_INT16;
            fieldNames_[RDB_COORD_HDF5_SYSTEM] = "system";
        }

        void Hdf5RdbMessageCoord::convertToModifiedStructure(const RDB_COORD_t &data, const uint32_t frameNumber, Hdf5RdbMessageCoord::ENRICHED_RDB_COORD &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.x = data.x;
            modifiedData.y = data.y;
            modifiedData.z = data.z;
            modifiedData.h = data.h;
            modifiedData.p = data.p;
            modifiedData.r = data.r;
            modifiedData.flags = data.flags;
            modifiedData.type = data.type;
            modifiedData.system = data.system;
        }

}

