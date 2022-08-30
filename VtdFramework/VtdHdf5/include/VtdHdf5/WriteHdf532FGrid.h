#ifndef _WRITE_HDF5_32F_GRID_H
#define _WRITE_HDF5_32F_GRID_H

#include "Hdf5Grid.h"
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    static const hid_t HDF5_ERROR = -1;

    class WriteHdf532FGrid : public Hdf5Grid
    {

    public:

        static const hsize_t TWO_DIM_SPACE = 2;

        /**
        *	Constructor
        */
        WriteHdf532FGrid(const unsigned int& chunkSize, const unsigned int& deflateLevel, const unsigned int& height, const int unsigned& width, const int unsigned& row);

        /**
        *	Constructor
        */
        WriteHdf532FGrid(const unsigned int& height, const int unsigned& width, const int unsigned& row);

        /**
        *	Destructor
        */
        virtual ~WriteHdf532FGrid();

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
        bool createdFloatDataSpace();

        /**
         * @brief createdPcdDataSet - create data space
         * @param dataSetName - dataset name
         * @param grp - where to create dataspace
         * @return handler to data set
         */
        bool createdFloatDataSet(const std::string& dataSetName, hid_t& grp);

        /**
         * @brief writePcdData - write data
         * @param writeData - refernce to data which will be written to hdf5
         * @return return status -1 if operation is unsuccessful
         */
        bool writeFloatData(const float& writeData);

        /**
         * @brief zipPcdData - create parameters for zipping
         * @return true if successful
         */
        bool zipFloatData();

        /**
         * @brief closePcdDataSpace - close data space
         * @return true if dataspace is closed
         */
        bool closeFloatDataSpace();

        /**
         * @brief closePcdDataSet - close data set
         * @return true if data set is closed
         */
        bool closeFloatDataSet();

        /**
         * @brief closeZipPcdData - close zip parameters
         * @return true if succesusfull
         */
        bool closeZipFloatData();

        /**
         * @brief getFileId - get handle to hdf5 file
         * @return file handle
         */
        inline hid_t getFileId() const {return fileId_;}

    private:

         int *fillData_;
         int compress_;
         hsize_t chunkSize_;
         hsize_t deflateLevel_;
         hsize_t  cdims_[TWO_DIM_SPACE];
         hsize_t  gridDims[TWO_DIM_SPACE];
         hid_t floatArray_;
         hsize_t floatArrayDims_[1];
         hid_t dset_, filetype_, space_, plist_id_;
         std::string fileName_;
    };
}

#endif
