#ifndef VTDFRAMEWORK_RDBIMAGEIO_H
#define VTDFRAMEWORK_RDBIMAGEIO_H

#include <iostream>
#include <VtdToolkit/viRDBIcd.h>

namespace
{
    // First 14 bytes of file for file header bitmap
    static const unsigned int FILE_HEADER_SIZE = 14;
    // First 40 bytes of file for file header bitmap
    static const unsigned int INFO_HEADER_SIZE = 40;
    //  write one line
    static const unsigned int ONE_ROW_TO_WRITE = 1;
    // First 18 bytes for tga header
    static const unsigned int TGA_HEADER_SIZE = 18;
    // Last 26 bytes for tga header
    static const unsigned int TGA_FOOTER_SIZE = 26;
    // float precision
    static const unsigned int FLOAT_PRECISION = 3;
    // jpeg quality
    static const unsigned int DEF_JPG_QUALITY = 80;
}

namespace VTD {

class RdbImageIO {

public:
    struct FileFormat {
        enum Enum {
                    RawData
#ifdef PNG_ENABLED
                    , PNG
#endif // PNG_ENABLED
                    , BMP
                    , TGA
                    , CSV
#ifdef JPEG_ENABLED
                    , JPG
#endif // JPEG_ENABLED
//TODO: Due to circular dependencies this is being deactivated for now, and will be replaced by a better solution later on.
//TODO: To write images into HDF files please use the WriteHdf5Image class from VtdHdf5 directly
//#ifdef HDF_ENABLED
//                    , HDF5
//#endif //HDF_ENABLED
        };
    };

    static bool isFormatAvailable(const FileFormat::Enum& format);

    /**
     * @brief writeRdbImageToPng
     * @param fp
     * @param img
     * @param flipped
     * @param compressionLevel 0 = no compression, 1 = fast compression, 9 = maximum compression
     * @return
     */
#ifdef PNG_ENABLED
    static bool writeRdbImageToPng(RDB_IMAGE_t& img, const std::string& filePath, int compressionLevel, int filters, bool flipped);
#endif // PNG_ENABLED

    static bool writeRdbImgToRawData(RDB_IMAGE_t& img, const std::string& filePath, bool flipped);

    static bool writeRdbImgToFile(RDB_IMAGE_t& img, const std::string& filePath, FileFormat::Enum format, int compressionLevel, bool flipImage);

    static bool writeRdbImageToBmp(RDB_IMAGE_t& img, const char* imageFileName, bool flipped);

    static unsigned char* createBitmapFileHeader(int height, int width, int paddingSize, unsigned int fileHeaderSize = FILE_HEADER_SIZE, unsigned int infoHeaderSize = INFO_HEADER_SIZE, unsigned int rowWidth = 3);

    static unsigned char* createBitmapInfoHeader(int height, int width, unsigned int infoHeaderSize = INFO_HEADER_SIZE, unsigned int rowWidth = 3);

    static bool writeRdbImageToTga(RDB_IMAGE_t& img, const char* filename, bool flipped);

    static bool writeRdbImageToCsv(RDB_IMAGE_t& img, const char* filename, bool flipped);

#ifdef JPEG_ENABLED
    static bool writeRdbImageToJpg(RDB_IMAGE_t& img, const char* filename, bool flipped, int quality = DEF_JPG_QUALITY);
#endif // JPEG_ENABLED
//TODO: Due to circular dependencies this is being deactivated for now, and will be replaced by a better solution later on.
//TODO: To write images into HDF files please use the WriteHdf5Image class from VtdHdf5 directly
//#ifdef HDF_ENABLED
//    static bool writeRdbImageToHdf5(RDB_IMAGE_t& img, const char* fileName, bool flipped, const std::string& imageName = "image");
//#endif //HDF_ENABLED

    template <typename T>
    static void flipedData(bool flipped, T* shmData, T* newImageData, const uint32_t &imgSize, const RDB_IMAGE_t& img, uint32_t &rowWidth)
    {
        if (!shmData || !newImageData)
            return;

        if(!flipped)
        {
            std::memcpy(newImageData, shmData, imgSize);
        }
        else
        {
            rowWidth = img.width * rowWidth;
            T* imgRow = shmData;
            for(int i=0; i<img.height; ++i)
            {
                int index = (img.height-1-i);
                std::memcpy(&newImageData[index * rowWidth], imgRow, rowWidth);
                imgRow += rowWidth;
            }
        }
    }
private:

};

} //namespace VTD

#endif //VTDFRAMEWORK_RDBIMAGEIO_H
