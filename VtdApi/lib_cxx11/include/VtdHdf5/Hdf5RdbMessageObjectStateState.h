#ifndef _RDB_HDF5_MESSAGE_RDB_OBJECT_STATE_H
#define _RDB_HDF5_MESSAGE_RDB_OBJECT_STATE_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageObjectState
    {

        enum RDB_OBJECT_STATE_HDF5 {RDB_OBJECT_STATE_HDF5_NDATA}; // Object state
        /**
        *	Constructor
        */
        Hdf5RdbMessageObjectState();
        /**
        *	Destructor
        */
        virtual ~Hdf5RdbMessageObjectState();

    };
}

#endif
