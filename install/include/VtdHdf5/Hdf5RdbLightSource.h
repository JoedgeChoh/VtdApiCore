#ifndef _RDB_HDF5_MESSAGE_RDB_LIGHT_SOURCE_H
#define _RDB_HDF5_MESSAGE_RDB_LIGHT_SOURCE_H

#include <VtdToolkit/viRDBIcd.h>

#include "WriteHdf5Data.h"
#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    struct Hdf5RdbLightSource
    {
    
    public:

        enum RDB_LIGHT_SOURCE_HDF5 {RDB_LIGHT_SOURCE_HDF5_NDATA}; // light source

        Hdf5_Rdb_Light_Source();

        virtual ~Hdf5_Rdb_Light_Source();
    };
}

#endif
