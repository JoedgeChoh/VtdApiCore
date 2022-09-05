#ifndef _WRITE_HDF5_IMAGE_H
#define _WRITE_HDF5_IMAGE_H

#include <hdf5.h>
#include <hdf5_hl.h>

#include <string>

namespace RdbToHdf5Writer
{

class WriteHdf5Image
{
public:
	WriteHdf5Image();

    virtual ~WriteHdf5Image();

    void openFile(const char* fileName);

	void closeFile();

    herr_t writeImage(unsigned char& gbuf, hsize_t width /* width of image */, hsize_t height/* height of image */, const char* pictureName /*name of the picture in hdf5 file*/);

private:

	hid_t fileId_;
};

}

#endif //_WRITE_HDF5_IMAGE_H
