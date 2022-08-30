#include <VtdHdf5/WriteHdf532FGrid.h>
#include <boost/thread.hpp>
#include <boost/cast.hpp>

namespace RdbToHdf5Writer
{
    WriteHdf532FGrid::WriteHdf532FGrid(const unsigned int& chunkSize, const unsigned int& deflateLevel, const unsigned int &height, const unsigned int &width, const unsigned int &row) :
        fillData_(NULL)
      , chunkSize_(chunkSize)
      , deflateLevel_(deflateLevel)
      , plist_id_(0)
    {
    #ifdef LOG_HDF5
        H5Eset_auto(H5E_DEFAULT, NULL, NULL);
    #endif
        compress_ = 0;
        gridDims[0] = height;
        gridDims[1] = width;
        // create array of row dim
        floatArrayDims_[0] = row;
        floatArray_ = H5Tarray_create(H5T_NATIVE_FLOAT, 1, floatArrayDims_);

    }

    WriteHdf532FGrid::WriteHdf532FGrid(const unsigned int& height, const int unsigned& width, const int unsigned& row)
                                        : chunkSize_(100)
                                        , deflateLevel_(0)
                                        , plist_id_(0)

    {
        gridDims[0] = height;
        gridDims[1] = width;
        // create array of row dim
        floatArrayDims_[0] = row;
        floatArray_ = H5Tarray_create(H5T_NATIVE_FLOAT, 1, floatArrayDims_);
        zipFloatData();
    }

    WriteHdf532FGrid::~WriteHdf532FGrid()
    {
        closeZipFloatData();
    }

    hid_t WriteHdf532FGrid::openFile(const std::string& fileName)
    {
            fileName_ = std::string(fileName);
            fileId_ = H5Fcreate(fileName_.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

            if (fileId_ == HDF5_ERROR)
                return HDF5_ERROR;

            return fileId_;
    }

    bool WriteHdf532FGrid::createdFloatDataSpace()
    {
        space_ = H5Screate_simple (TWO_DIM_SPACE, gridDims, NULL);
        if (space_ == HDF5_ERROR)
            return false;

        return true;
    }

    bool WriteHdf532FGrid::createdFloatDataSet(const std::string& dataSetName, hid_t& grp)
    {
        dset_ = H5Dcreate (grp, dataSetName.c_str(), floatArray_, space_, H5P_DEFAULT, plist_id_, H5P_DEFAULT);
        if (dset_ == HDF5_ERROR)
            return false;

        return true;
    }

    bool WriteHdf532FGrid::writeFloatData(const float& writeData)
    {
        status_ = H5Dwrite (dset_, floatArray_, H5S_ALL, H5S_ALL, H5P_DEFAULT, &writeData);
        if (status_ == HDF5_ERROR)
           return false;

        return true;
    }

    bool WriteHdf532FGrid::closeFloatDataSpace()
    {
        status_ = H5Sclose (space_);
        space_ = 0;
        if (status_ == HDF5_ERROR)
            return false;

        return true;
    }

    bool WriteHdf532FGrid::closeFloatDataSet()
    {
        status_ = H5Dclose (dset_);
        dset_ = 0;
        if (status_ == HDF5_ERROR)
            return false;

        return true;
    }

    bool WriteHdf532FGrid::closeZipFloatData()
    {
        status_ = H5Pclose (plist_id_);
        plist_id_ = 0;
        if (status_ == HDF5_ERROR)
            return false;

        return true;
    }

    bool WriteHdf532FGrid::zipFloatData()
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
        if (status_ == HDF5_ERROR)
            return false;

        return true;
    }

}
