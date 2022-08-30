#ifndef _RDB_HDF5_MESSAGE_RDB_DRIVETRAIN_H
#define _RDB_HDF5_MESSAGE_RDB_DRIVETRAIN_H

#include <VtdToolkit/viRDBIcd.h>

#include "WriteHdf5Data.h"
#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageDrivetrain
    {
        
    public:

        enum RDB_DRIVETRAIN_HDF5 {RDB_DRIVETRAIN_HDF5_NDATA}; // drive train

        Hdf5RdbMessageDrivetrain();

        virtual ~Hdf5RdbMessageDrivetrain();
    };
}

#endif
