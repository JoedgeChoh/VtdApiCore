#ifndef _WRITE_HDF5_GRID_H
#define _WRITE_HDF5_GRID_H

#include "Hdf5Grid.h"
#include "Hdf5Pcd.h"

#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class WriteHdf5Pcd : public Hdf5Grid, public Hdf5PCDMetadata
    {

    public:

        /**
        *	Constructor
        */
        WriteHdf5Pcd(const unsigned int& chunkSize, const unsigned int& deflateLevel);

        /**
        *	Destructor
        */
        virtual ~WriteHdf5Pcd();

        /**
         * @brief openFile - open file name
         * @param fileName - hdf5 file name
         * @return handler to hdf5 file
         */
        hid_t openFile(const std::string& fileName);

        /**
         * @brief createdPcdDataSpace - create pcd data spece
         * @return handler to data space
         */
        bool createdPcdDataSpace();

        /**
         * @brief createdPcdDataSet - create data space
         * @param dataSetName - dataset name
         * @param grp - where to create dataspace
         * @return handler to data set
         */
        bool createdPcdDataSet(const std::string& dataSetName, hid_t& grp);

        /**
         * @brief writePcdData - write data
         * @param writeData - refernce to data which will be written to hdf5
         * @return return status -1 if operation is unsuccessful
         */
        bool writePcdData(const HDF5_META_DATA_t& writeData);

        /**
         * @brief zipPcdData - create parameters for zipping
         * @return true if successful
         */
        bool zipPcdData();

        /**
         * @brief closePcdDataSpace - close data space
         * @return true if dataspace is closed
         */
        bool closePcdDataSpace();

        /**
         * @brief closePcdDataSet - close data set
         * @return true if data set is closed
         */
        bool closePcdDataSet();

        /**
         * @brief closeZipPcdData - close zip parameters
         * @return true if succesusfull
         */
        bool closeZipPcdData();

    private:

         int *fillData_;
         int compress_;
         hsize_t chunkSize_;
         hsize_t deflateLevel_;
         hsize_t  cdims_[2];
         hid_t dset_, filetype_, space_, plist_id_;
         std::string fileName_;
    };
}

#endif
