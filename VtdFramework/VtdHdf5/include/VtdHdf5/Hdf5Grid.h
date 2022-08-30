#ifndef _HDF5_GRID_H
#define _HDF5_GRID_H

#include <hdf5.h>
#include <string>

namespace RdbToHdf5Writer
{
    class Hdf5Grid
    {
    public:

        /**
        *	Constructor
        */
        Hdf5Grid();

        /**
        *	Copy constructor
        */
        Hdf5Grid(const Hdf5Grid& obj)
        {
            status_ = obj.status_;
            fileId_ = obj.fileId_;
        }
        /**
        *	Destructor
        */
        virtual ~Hdf5Grid(){}

        /**
        *	@brief close hdf5 file
        */
        virtual void closeFile();

        /**
        *	@brief openFile - open hdf5 file
        *   @param fileName - hdf5 file name
        *   @return handler to hdf5 file
        */
        virtual hid_t openFile(const std::string& fileName) = 0;

        /**
        *   @brief checkIfFilterExistered - check if GZIP filter could be applied
        *   @return return status true if operation is successful
        */
        virtual bool checkIfFilterExistered();

        /**
         * @brief createGroup -
         * @param tableName
         * @return
         */
        virtual hid_t createGroup(const std::string& tableName);

        /**
         * @brief closeGroup
         * @param groupId
         * @return
         */
        virtual herr_t closeGroup(hid_t groupId);

        template<typename T>
        void SAFE_CLOSE_HDF5(T& a)
        {
            if( (a) != 0 )
                H5Fclose(a);

            (a) = 0;
        }

    protected:
        /**
         * @brief status_ a protected variable - status of hdf5 operation when -1
         */
        hid_t status_;

        /**
         * @brief fileId_ a protected variable - handle to hdf5 if -1 file is bad
         */
        hid_t fileId_;
    };
}
#endif
