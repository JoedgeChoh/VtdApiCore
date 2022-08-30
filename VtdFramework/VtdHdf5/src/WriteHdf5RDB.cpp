#include <VtdHdf5/WriteHdf5RDB.h>

namespace RdbToHdf5Writer
{
    WriteHdf5RDB::WriteHdf5RDB() :
        fillData_(NULL)
    {
#ifdef LOG_HDF5
    H5Eset_auto(H5E_DEFAULT, NULL, NULL);
#endif
    }

    WriteHdf5RDB::~WriteHdf5RDB()
    {
    }

    WriteHdf5RDB::WriteHdf5RDB(std::string fileName)
        : fileName_(fileName)
        , isFileOpen_(false)
    {
    }

    void WriteHdf5RDB::closeHdf5File()
    {
        // Close the file
        SAFE_CLOSE_HDF5 (fileId_);
        isFileOpen_ = false;
    }

    bool WriteHdf5RDB::openHdf5File(const std::string& fileName)
    {
        fileName_ = std::string(fileName) + HDF5_EXTENSION;
        fileId_ = H5Fcreate(fileName_.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        if (fileId_ == -1)
        {
            return false;
        }

        std::cout << "Opened sensor file with name: " << fileName << std::endl;
        isFileOpen_ = true;
        return true;
    }

    hid_t WriteHdf5RDB::createRootGroup(const std::string& tableName)
    {
        std::cout << fileName_ << ": createRootGroup(), name: " << tableName << std::endl;
        return H5Gcreate2(fileId_, tableName.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    }

    hid_t WriteHdf5RDB::createNestedGroup(const std::string& tableName, hid_t grp)
    {
        std::cout <<  fileName_ << ": createNestedGroup(), name: " << tableName << ", id: " << grp << std::endl;
        return H5Gcreate2(grp, tableName.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    }

    herr_t WriteHdf5RDB::closeGroup(hid_t groupId)
    {
        return H5Gclose(groupId);
    }
}
