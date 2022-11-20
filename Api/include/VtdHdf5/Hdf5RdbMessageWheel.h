#ifndef _RDB_HDF5_MESSAGE_RDB_WHEEL_H
#define _RDB_HDF5_MESSAGE_RDB_WHEEL_H

#include <VtdToolkit/viRDBIcd.h>
#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageWheel
    {
        
    public:

        enum RDB_WHEEL_HDF5 {RDB_WHEEL_HDF5_NDATA}; // wheel

        Hdf5RdbMessageWheel();

        virtual ~Hdf5RdbMessageWheel(){}
    };
}

#endif
