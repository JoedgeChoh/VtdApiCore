#ifndef _RDB_HDF5_MESSAGE_RDB_TRAFFIC_LIGHT_H
#define _RDB_HDF5_MESSAGE_RDB_TRAFFIC_LIGHT_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbTrafficLight
    {
        
    public:
        
        enum RDB_TRAFFIC_LIGHT_HDF5 {RDB_TRAFFIC_LIGHT_HDF5_NDATA}; // light source

        Hdf5RdbTrafficLight();

        virtual ~Hdf5RdbTrafficLight();

    };
}

#endif
