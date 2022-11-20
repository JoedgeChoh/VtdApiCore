#ifndef _WRITE_HDF5_RDB_H
#define _WRITE_HDF5_RDB_H

#include <hdf5.h>
#include <hdf5_hl.h>

#include "RDBHDF5lib.h"

#include <string>
#include <map>
#include <boost/thread.hpp>
#include <iostream>

namespace RdbToHdf5Writer
{
    class WriteHdf5RDB
    {
    public:
        /**
        *	Constructor
        */
        WriteHdf5RDB();

        /**
        *	Constructor
        */
        explicit WriteHdf5RDB(std::string fileName);

        /**
        *	Destructor
        */
        virtual ~WriteHdf5RDB();

        /**
         * @brief openHdf5File - open file
         * @param fileName - file name
         * @return - return true if succesful
         */
        virtual bool openHdf5File(const std::string& fileName);

        /**
         * @brief closeHdf5File - close hdf5 file
         */
        virtual void closeHdf5File();

        /**
         * @brief createRootGroup - create root folder
         * @param tableName - table name
         * @return - return handler to table or -1 when is not created
         */
        virtual hid_t createRootGroup(const std::string& tableName);

        /**
         * @brief createNestedGroup - create nested group inside group
         * @param tableName - table name
         * @param grp - handler to root group
         * @return - return handler to table or -1 when is not created
         */
        virtual hid_t createNestedGroup(const std::string& tableName, hid_t grp);

        /**
         * @brief closeGroup - close group
         * @param groupId - group Id
         * @return  - return -1 when is not closed
         */
        virtual herr_t closeGroup(hid_t groupId);

        /**
         * @brief createDataTable - create table to write
         * @param data - pointer to data structure (object, traffic, engine, ...)
         * @param write - data to be written
         * @param grp - group pointer
         * @param tableName - table name
         * @return -1 if operation is not succesful
         */
        template<class T, class W>
        herr_t createDataTable(T& data, W& write, hid_t grp, const std::string& tableName)
        {

           std::cout << fileName_ << ": createDataTable(), name: " << tableName << ", grp: " << grp << std::endl;
           return H5TBmake_table(tableName.c_str(), grp, tableName.c_str(), data.tableSize_, SKIP_FIRST_RAW
                                  , data.dstSize_, data.fieldNames_, data.dstOffset_
                                  , data.fieldType_, chunkSize_, fillData_, compress_, &write);
        }


        /**
         * @brief appendDataTable - append data to table
         * @param data - pointer to data structure (object, traffic, engine, ...)
         * @param write - data to be written
         * @param grp - group pointer
         * @param tableName - table name
         * @return -1 if operation is not succesful
         */
        template<class T, class W>
        herr_t appendDataTable(T& data, W& write, hid_t grp, const std::string& tableName)
        {

         return H5TBappend_records(grp, tableName.c_str(), NUM_OF_ROW_WR
                                    , data.dstSize_, data.dstOffset_
                                    , data.dstSizes_, &write);
        }

        template<typename T>
        void SAFE_CLOSE_HDF5(T& a)
        {
            if( (a) != 0 )
                H5Fclose(a);

            (a) = 0;
        }

        bool isFileOpen(void) { return isFileOpen_; }

    protected:
        // file name
        std::string fileName_;
        // handler to file
        hid_t fileId_;
        // chunk size
        hsize_t chunkSize_;
        // fill data
        int *fillData_;
        // compress
        int compress_;
        // file opened
        bool isFileOpen_;

     };
}


#endif
