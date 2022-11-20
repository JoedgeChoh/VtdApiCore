#ifndef _HDF5_PCD_METADATA_H
#define _HDF5_PCD_METADATA_H

#include <stdint.h>
#include <hdf5.h>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <iostream>

namespace RdbToHdf5Writer
{
     // Wrapper to PCD data structure
    typedef struct HDF5_META_DATA_t
    {
         float pcd_x;
         float pcd_y;
         float pcd_z;
         float signalIntensity;
         unsigned int object_id;
         unsigned int material_id;
         uint8_t hitInteractionType;
    } HDF5_META_DATA_t;

    /**
     * @brief The Hdf5PCDMetadata class wrapper from pcd data to hdf5 data
     */
    class Hdf5PCDMetadata
    {

    public:

       /**
       *	@brief Constructor
       */
       Hdf5PCDMetadata();

       /**
       *	@brief Destructor
       */
       virtual ~Hdf5PCDMetadata(){}

       /**
       *	@brief initPcdHdf5 - initalaze data space depending on data size
       *    height - height of data
       *    width - width of data
       */
       virtual void initPcdHdf5(const int& height, const int& width);

    private:

       /**
        * @brief createFileType
        */
       void createFileType();

    public:
       // dims for data space
       hsize_t dimsPcd_[2];
       // hdf5 file type for writting data
       hid_t fileTypePcd_;
    };

}
#endif // _HDF5_PCD_H
