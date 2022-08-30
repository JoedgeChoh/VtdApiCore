#ifndef _RDB_HDF5_MESSAGE_RDB_RDB_ENGINE_H
#define _RDB_HDF5_MESSAGE_RDB_RDB_ENGINE_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageEngine
    {

        enum RDB_ENGINE_HDF5 {RDB_ENGINE_HDF5_NDATA}; // engine

        Hdf5RdbMessageEngine();

        virtual ~Hdf5RdbMessageEngine();
    };
}

#endif
