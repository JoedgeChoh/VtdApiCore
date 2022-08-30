#include <VtdHdf5/WriteHdf5Image.h>
#include <string.h>
#include <stdlib.h>

namespace RdbToHdf5Writer
{
WriteHdf5Image::WriteHdf5Image()
{
}


WriteHdf5Image::~WriteHdf5Image()
{
}

void WriteHdf5Image::openFile(const char* fileName)
{
    fileId_ = H5Fcreate(fileName, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
}

void WriteHdf5Image::closeFile()
{
	H5Fclose(fileId_);
}

herr_t WriteHdf5Image::writeImage(unsigned char& gbuf, hsize_t width, hsize_t height, const char* pictureName)
{
   return H5IMmake_image_24bit(fileId_, pictureName, width, height, "INTERLACE_PIXEL", &gbuf);
}
}
