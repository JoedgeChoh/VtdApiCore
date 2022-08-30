#include <VtdHdf5/Hdf5Pcd.h>

namespace RdbToHdf5Writer
{
    Hdf5PCDMetadata::Hdf5PCDMetadata()
    {
        createFileType();
    }

    void Hdf5PCDMetadata::initPcdHdf5(const int& height, const int& width)
    {
        dimsPcd_ [0] = height;
        dimsPcd_ [1] = width;
    }

    void Hdf5PCDMetadata::createFileType()
    {
        fileTypePcd_ = H5Tcreate (H5T_COMPOUND, sizeof(HDF5_META_DATA_t));
        H5Tinsert (fileTypePcd_, "pcd_x", HOFFSET(HDF5_META_DATA_t, pcd_x), H5T_NATIVE_FLOAT);
        H5Tinsert (fileTypePcd_, "pcd_y", HOFFSET(HDF5_META_DATA_t, pcd_y), H5T_NATIVE_FLOAT);
        H5Tinsert (fileTypePcd_, "pcd_z", HOFFSET(HDF5_META_DATA_t, pcd_z), H5T_NATIVE_FLOAT);
        H5Tinsert (fileTypePcd_, "signalIntensity", HOFFSET(HDF5_META_DATA_t,signalIntensity), H5T_NATIVE_FLOAT);
        H5Tinsert (fileTypePcd_, "object_id", HOFFSET(HDF5_META_DATA_t,object_id), H5T_NATIVE_UINT);
        H5Tinsert (fileTypePcd_, "material_id", HOFFSET(HDF5_META_DATA_t,material_id), H5T_NATIVE_UINT);
        H5Tinsert (fileTypePcd_, "hitInteractionType", HOFFSET(HDF5_META_DATA_t,hitInteractionType), H5T_NATIVE_UINT8);
    }
}
