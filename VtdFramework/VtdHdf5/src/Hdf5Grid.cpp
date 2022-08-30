#include <VtdHdf5/Hdf5Grid.h>

namespace RdbToHdf5Writer
{
    Hdf5Grid::Hdf5Grid()
    {
    }

    void Hdf5Grid::closeFile()
    {
         // Close the file
        SAFE_CLOSE_HDF5 (fileId_);
    }

    bool Hdf5Grid::checkIfFilterExistered()
    {
        unsigned filter_info;
        // Check if gzip compression is available and can be used for both compression and decompression.
        htri_t avail = H5Zfilter_avail(H5Z_FILTER_DEFLATE);

        if (!avail)
        {
            printf ("gzip filter not available.\n");
            return false;
        }

        status_ = H5Zget_filter_info (H5Z_FILTER_DEFLATE, &filter_info);
        if ( !(filter_info & H5Z_FILTER_CONFIG_ENCODE_ENABLED) || (filter_info & H5Z_FILTER_CONFIG_DECODE_ENABLED))
        {
            printf ("gzip filter not available for encoding and decoding.\n");
            return false;
        }

        return true;
    }

    hid_t Hdf5Grid::createGroup(const std::string& tableName)
    {
        return H5Gcreate2(fileId_, tableName.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    }

    herr_t Hdf5Grid::closeGroup(hid_t groupId)
    {
        return H5Gclose(groupId);
    }
}
