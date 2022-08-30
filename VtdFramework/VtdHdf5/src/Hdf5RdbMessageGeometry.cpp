#include <VtdHdf5/Hdf5RdbMessageGeometry.h>

namespace RdbToHdf5Writer
{

        Hdf5RdbMessageGeometry::Hdf5RdbMessageGeometry() : tableSize_(RDB_GEOMETRY_HDF5_NDATA)
        {
            this->initData();
        }

        void Hdf5RdbMessageGeometry::initData()
        {
            dstSize_ = sizeof(ENRICHED_RDB_GEOMETRY);

            dstOffset_[RDB_GEOMETRY_HDF5_DIM_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_GEOMETRY, frameNumber);
            dstSizes_ [RDB_GEOMETRY_HDF5_DIM_FRAME_NUMBER] = sizeof(ENRICHED_RDB_GEOMETRY::frameNumber);
            fieldType_[RDB_GEOMETRY_HDF5_DIM_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_GEOMETRY_HDF5_DIM_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_GEOMETRY_HDF5_DIM_X] = HOFFSET(ENRICHED_RDB_GEOMETRY, dimX);
            dstSizes_ [RDB_GEOMETRY_HDF5_DIM_X] = sizeof(ENRICHED_RDB_GEOMETRY::dimX);
            fieldType_[RDB_GEOMETRY_HDF5_DIM_X] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_GEOMETRY_HDF5_DIM_X] = "dimX";

            dstOffset_[RDB_GEOMETRY_HDF5_DIM_Y] = HOFFSET(ENRICHED_RDB_GEOMETRY, dimY);
            dstSizes_ [RDB_GEOMETRY_HDF5_DIM_Y] = sizeof(ENRICHED_RDB_GEOMETRY::dimY);
            fieldType_[RDB_GEOMETRY_HDF5_DIM_Y] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_GEOMETRY_HDF5_DIM_Y] = "dimY";

            dstOffset_[RDB_GEOMETRY_HDF5_DIM_Z] = HOFFSET(ENRICHED_RDB_GEOMETRY, dimZ);
            dstSizes_ [RDB_GEOMETRY_HDF5_DIM_Z] = sizeof(ENRICHED_RDB_GEOMETRY::dimZ);
            fieldType_[RDB_GEOMETRY_HDF5_DIM_Z] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_GEOMETRY_HDF5_DIM_Z] = "dimZ";

            dstOffset_[RDB_GEOMETRY_HDF5_OFF_X] = HOFFSET(ENRICHED_RDB_GEOMETRY, offX);
            dstSizes_ [RDB_GEOMETRY_HDF5_OFF_X] = sizeof(ENRICHED_RDB_GEOMETRY::offX);
            fieldType_[RDB_GEOMETRY_HDF5_OFF_X] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_GEOMETRY_HDF5_OFF_X] = "offX";

            dstOffset_[RDB_GEOMETRY_HDF5_OFF_Y] = HOFFSET(ENRICHED_RDB_GEOMETRY, offY);
            dstSizes_ [RDB_GEOMETRY_HDF5_OFF_Y] = sizeof(ENRICHED_RDB_GEOMETRY::offY);
            fieldType_[RDB_GEOMETRY_HDF5_OFF_Y] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_GEOMETRY_HDF5_OFF_Y] = "offY";

            dstOffset_[RDB_GEOMETRY_HDF5_OFF_Z] = HOFFSET(ENRICHED_RDB_GEOMETRY, offZ);
            dstSizes_ [RDB_GEOMETRY_HDF5_OFF_Z] = sizeof(ENRICHED_RDB_GEOMETRY::offZ);
            fieldType_[RDB_GEOMETRY_HDF5_OFF_Z] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_GEOMETRY_HDF5_OFF_Z] = "offZ";
        }
}

