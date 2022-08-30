#include <VtdHdf5/WriteHdf5Pcd.h>
#include <boost/cast.hpp>

namespace RdbToHdf5Writer
{
    WriteHdf5Pcd::WriteHdf5Pcd(const unsigned int& chunkSize, const unsigned int& deflateLevel) :
        fillData_(NULL)
      , chunkSize_(chunkSize)
      , deflateLevel_(deflateLevel)
    {
    #ifdef LOG_HDF5
        H5Eset_auto(H5E_DEFAULT, NULL, NULL);
    #endif
        chunkSize_ = 10;
        compress_ = 0;

    }

    WriteHdf5Pcd::~WriteHdf5Pcd()
    {

    }

    hid_t WriteHdf5Pcd::openFile(const std::string& fileName)
    {
            fileName_ = std::string(fileName);
            fileId_ = H5Fcreate(fileName_.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

            if (fileId_ == -1)
                return -1;

            return fileId_;
    }

    bool WriteHdf5Pcd::createdPcdDataSpace()
    {
        space_ = H5Screate_simple (2, dimsPcd_, NULL);
        if (space_ == -1)
            return false;

        return true;
    }

    bool WriteHdf5Pcd::createdPcdDataSet(const std::string& dataSetName, hid_t& grp)
    {
        dset_ = H5Dcreate (grp, dataSetName.c_str(), fileTypePcd_, space_, H5P_DEFAULT, plist_id_, H5P_DEFAULT);
        if (dset_ == -1)
            return false;

        return true;
    }

    bool WriteHdf5Pcd::writePcdData(const HDF5_META_DATA_t& writeData)
    {
        status_ = H5Dwrite (dset_, fileTypePcd_, H5S_ALL, H5S_ALL, H5P_DEFAULT, &writeData);
        if (status_ == -1)
           return false;


        return true;
    }

    bool WriteHdf5Pcd::closePcdDataSpace()
    {
        status_ = H5Sclose (space_);
        space_ = 0;
        if (status_ == -1)
            return false;

        return true;
    }

    bool WriteHdf5Pcd::closePcdDataSet()
    {
        status_ = H5Dclose (dset_);
        dset_ = 0;
        if (status_ == -1)
            return false;

        return true;
    }

    bool WriteHdf5Pcd::closeZipPcdData()
    {
        status_ = H5Pclose (plist_id_);
        plist_id_ = 0;
        if (status_ == -1)
            return false;

        return true;
    }

    bool WriteHdf5Pcd::zipPcdData()
    {
        if (plist_id_ == 0)
            plist_id_  = H5Pcreate (H5P_DATASET_CREATE);
        else
        {
            H5Pclose(plist_id_);
            plist_id_  = H5Pcreate (H5P_DATASET_CREATE);
        }
        // Dataset must be chunked for compression
        cdims_[0] = chunkSize_;
        cdims_[1] = chunkSize_;
        status_ = H5Pset_chunk (plist_id_, 2, cdims_);
        status_ = H5Pset_deflate (plist_id_, boost::numeric_cast<unsigned int>( deflateLevel_ ) );
        if (status_ == -1)
            return false;

        return true;
    }

}
