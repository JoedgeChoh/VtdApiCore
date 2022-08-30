#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <boost/scoped_ptr.hpp>

#ifdef PNG_ENABLED
#include <png.h>
#endif // PNG_ENABLED

#ifdef JPEG_ENABLED
// libjpeg is compiled with C
extern "C"
{
    #include <jpeglib.h>
    #include <setjmp.h>
}
#endif // JPEG_ENABLED

#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/Rdb/RdbImageIO.h>
#include <VtdCore/Logging/Log.h>

//TODO: Due to circular dependencies this is being deactivated for now, and will be replaced by a better solution later on.
//TODO: To write images into HDF files please use the WriteHdf5Image class from VtdHdf5 directly
//#ifdef HDF_ENABLED
//    #include <VtdHdf5/WriteHdf5Image.h>
//    #include <VtdHdf5/WriteHdf532FGrid.h>
//#endif //HDF_ENABLED

#include <VtdCore/FileSystemIO.h>

namespace VTD {

#ifdef PNG_ENABLED
void png_error_callback(png_structp /*png_ptr*/, png_const_charp text)
{
    VTD_LOG_ERR("VtdToolkit: libpng error: " << text);
}

void png_warn_callback(png_structp /*png_ptr*/, png_const_charp text)
{
    VTD_LOG_ERR("VtdToolkit: libpng warning: " << text);
}
#endif // PNG_ENABLED

bool RdbImageIO::isFormatAvailable(const FileFormat::Enum& format)
{
    switch(format) {
        case FileFormat::RawData:
#ifdef PNG_ENABLED
        case FileFormat::PNG:
#endif // PNG_ENABLED
        case FileFormat::BMP:
#ifdef JPEG_ENABLED
        case FileFormat::JPG:
#endif // JPEG_ENABLED
        case FileFormat::CSV:
        case FileFormat::TGA:
        // TODO [BB] HDF File Format missing
            return true;
        default:
            return false;
    }
}

/**
 * @brief writeRdbImageToPng
 * @param img
 * @param flipped
 * @param compressionLevel 0 = no compression, 1 = best speed, 9 = best compression
 * @return
 */

#ifdef PNG_ENABLED
bool RdbImageIO::writeRdbImageToPng(RDB_IMAGE_t& img, const std::string& filePath, int compressionLevel, int filters, bool flipped)
{    
    volatile uint32_t pngBitDepth = 0;
    volatile uint32_t pngColorType = 0;
    volatile uint32_t rowWidth = 0;
    switch(img.pixelFormat) {
        case RDB_PIX_FORMAT_RGBA8:
            pngBitDepth = 8;
            pngColorType = PNG_COLOR_TYPE_RGB_ALPHA;
            rowWidth = 4;
        break;
        case RDB_PIX_FORMAT_RGB8:
            pngBitDepth = 8;
            pngColorType = PNG_COLOR_TYPE_RGB;
            rowWidth = 3;
        break;
    default:
        VTD_LOG_ERR("VtdToolkit: Only pixelformat RDB_PIX_FORMAT_RGB8 and RDB_PIX_FORMAT_RGBA8 supported for writing PNG files. Aborting writing file.");
        return false;
    }

    FILE* fp;
    fp = fopen(filePath.c_str(), "wb");
    if(!fp) {
        VTD_LOG_ERR("VtdToolkit: Could not open png file.");
        return false;
    }

    uint32_t width = img.width;
    uint32_t height = img.height;
    rowWidth *= width; //number of bytes * row width

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)0, png_error_callback, png_warn_callback);
    if(!png_ptr) {
        VTD_LOG_ERR("VtdToolkit: Error creating png write struct.");
        return false;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr) {
        VTD_LOG_ERR("VtdToolkit: Error Creating png info pointer.");
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        return false;
    }

    png_bytepp row_pointers = static_cast<png_bytepp>(png_malloc(png_ptr, (img.height) * sizeof(png_bytep)));
    if(!row_pointers) {
        VTD_LOG_ERR("VtdToolkit: Could not allocate libpng row pointers.");
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return false;
    }

#ifdef PNG_SETJMP_SUPPORTED
    //error handling in libpng is done by longjmp.
    if(setjmp(png_jmpbuf(png_ptr)))
    {
        VTD_LOG_ERR("VtdToolkit: PNG write error.");
        png_destroy_write_struct(&png_ptr, &info_ptr);
        png_free(png_ptr, row_pointers);
        return false;
    }
#else
    VTD_LOG_ERR("VtdToolkit: Setjmp not supported. Program will abort on libpng error.");
#endif

    png_init_io(png_ptr, fp);

    png_set_filter(png_ptr, 0, filters);
    png_set_compression_level(png_ptr, compressionLevel);

    png_set_IHDR(png_ptr, info_ptr,
                 width, height,
                 pngBitDepth,
                 pngColorType,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_bytep imgRow = reinterpret_cast<png_bytep>(&img + 1);
    for (uint32_t i = 0; i < height; ++i) {
        int index = flipped ? (height - 1 - i) : i;

        row_pointers[index] = imgRow;

        imgRow += rowWidth;
    }

    png_set_rows(png_ptr, info_ptr, row_pointers);

    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    png_free(png_ptr, row_pointers);
    fclose(fp);
    return true;
}
#endif // PNG_ENABLED

bool RdbImageIO::writeRdbImgToRawData(RDB_IMAGE_t& img, const std::string& filePath, bool flipped)
{
    unsigned int rowWidth = 0;
    switch(img.pixelFormat) {
        case RDB_PIX_FORMAT_RGB8:
            rowWidth = 3;
            break;
        case RDB_PIX_FORMAT_RGBA8:
            rowWidth = 4;
            break;
        case RDB_PIX_FORMAT_RGB32:
        case RDB_PIX_FORMAT_RGB32F:
            rowWidth = 12;
            break;
        case RDB_PIX_FORMAT_RGBA32:
        case RDB_PIX_FORMAT_RGBA32F:
            rowWidth = 16;
            break;
    default:
        VTD_LOG_ERR("VtdToolkit: Unsupported pixel format" << std::hex << img.pixelFormat << " for raw .data files.");
        return false;
    }

    FILE* fp;
    fp = fopen(filePath.c_str(), "wb");
    if(!fp) {
        VTD_LOG_ERR("VtdToolkit: Could not open png file.");
        return false;
    }

    uint32_t imgSize = img.imgSize;
    unsigned char* shmData = reinterpret_cast<unsigned char*>(&img + 1);
    unsigned char* newImageData = new unsigned char[imgSize];

    flipedData(flipped, shmData, newImageData, imgSize, img, rowWidth);

    fwrite(newImageData, 1, imgSize, fp);
    fclose(fp);
    delete[] newImageData;
    return true;
}

bool RdbImageIO::writeRdbImageToBmp(RDB_IMAGE_t &img, const char* imageFileName, bool flipped)
{
    unsigned int rowWidth = 0;
    unsigned int fileHeaderSize = FILE_HEADER_SIZE;
    unsigned int infoHeaderSize = INFO_HEADER_SIZE;
    switch(img.pixelFormat) {
        case RDB_PIX_FORMAT_RGB8:
            rowWidth = 3;
            break;
    default:
        VTD_LOG_ERR("VtdToolkit: Unsupported pixel format" << std::hex << img.pixelFormat << " for raw .bmp files.");
        return false;
    }

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (img.width * rowWidth) % 4) % 4;

    unsigned char* fileHeader = createBitmapFileHeader(img.height, img.width, paddingSize);
    unsigned char* infoHeader = createBitmapInfoHeader(img.height, img.width);

    FILE* imageFile = fopen(imageFileName, "wb");

    fwrite(fileHeader, ONE_ROW_TO_WRITE, fileHeaderSize, imageFile);
    fwrite(infoHeader, ONE_ROW_TO_WRITE,  infoHeaderSize, imageFile);

    unsigned char* shmData = reinterpret_cast<unsigned char*>(&img + 1);
    unsigned char* newImageData = new unsigned char[img.imgSize];
    flipedData(flipped, shmData, newImageData, img.imgSize, img, rowWidth);

    for(int i = 0; i < img.height; ++i)
    {
        fwrite(newImageData + (i * img.width * rowWidth), rowWidth, img.width, imageFile);
        fwrite(padding, ONE_ROW_TO_WRITE, paddingSize, imageFile);
    }

    delete [] newImageData;
    fclose(imageFile);

    return true;
}

unsigned char* RdbImageIO::createBitmapFileHeader(int height, int width, int paddingSize, unsigned int fileHeaderSize, unsigned int infoHeaderSize, unsigned int rowWidth)
{
    int fileSize = fileHeaderSize + infoHeaderSize + (rowWidth * width+paddingSize) * height;
    static unsigned char fileHeader[] = {
        0,0, /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[0] = static_cast<unsigned char>('B');
    fileHeader[1] = static_cast<unsigned char>('M');
    fileHeader[2] = static_cast<unsigned char>(fileSize);
    fileHeader[3] = static_cast<unsigned char>(fileSize >> 8);
    fileHeader[4] = static_cast<unsigned char>(fileSize >> 16);
    fileHeader[5] = static_cast<unsigned char>(fileSize >> 24);
    fileHeader[10] = static_cast<unsigned char>(fileHeaderSize + infoHeaderSize);

    return fileHeader;
}

unsigned char* RdbImageIO::createBitmapInfoHeader(int height, int width, unsigned int infoHeaderSize, unsigned int rowWidth)
{
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0, /// number of color planes
        0,0, /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[ 0] = static_cast<unsigned char>(infoHeaderSize);
    infoHeader[ 4] = static_cast<unsigned char>(width    );
    infoHeader[ 5] = static_cast<unsigned char>(width>> 8);
    infoHeader[ 6] = static_cast<unsigned char>(width>>16);
    infoHeader[ 7] = static_cast<unsigned char>(width>>24);
    infoHeader[ 8] = static_cast<unsigned char>(height    );
    infoHeader[ 9] = static_cast<unsigned char>(height>> 8);
    infoHeader[10] = static_cast<unsigned char>(height>>16);
    infoHeader[11] = static_cast<unsigned char>(height>>24);
    infoHeader[12] = static_cast<unsigned char>(1);
    infoHeader[14] = static_cast<unsigned char>(rowWidth * 8);
    return infoHeader;
}

bool RdbImageIO::writeRdbImageToTga(RDB_IMAGE_t& img, const char *filename, bool flipped)
{
    unsigned int rowWidth = 0;
    unsigned int imageTypeCode = 0;
    unsigned int bitPerPixel = 0;
    switch(img.pixelFormat)
    {
        case RDB_PIX_FORMAT_RGB8:
            rowWidth = 3;
            imageTypeCode = 2;
            bitPerPixel = 24;
            break;
    default:
        VTD_LOG_ERR("VtdToolkit: Unsupported pixel format" << std::hex << img.pixelFormat << " for raw .tga files.");
        return false;
    }

    //the type code should be 2 (uncompressed RGB image)
    if (imageTypeCode != RDB_PIX_FORMAT_RGB_24)
        return false;

    std::ofstream tgafile( filename, std::ios::binary );
    if (!tgafile)
        return false;
    // The image header
    unsigned char header[18] = { 0 };
    header[2] = 2;  // uncompressed RGB image
    header[12] = static_cast<unsigned char>( img.width & 0xFF );
    header[13] = static_cast<unsigned char>( (img.width  >> 8) & 0xFF );
    header[14] = static_cast<unsigned char>( img.height & 0xFF );
    header[15] = static_cast<unsigned char>( ( img.height >> 8 ) & 0xFF );
    header[16] = static_cast<unsigned char>( bitPerPixel );  // bits per pixel

    tgafile.write( reinterpret_cast<const char*>(header), TGA_HEADER_SIZE);
    unsigned char* shmData = reinterpret_cast<unsigned char*>(&img + 1);
    unsigned char* newImageData = new unsigned char[img.imgSize];
    flipedData(flipped, shmData, newImageData, img.imgSize, img, rowWidth);

    // The image data is stored bottom-to-top, left-to-right
    for (unsigned int y = 0; y < img.height; y++)
        for (unsigned int x = 0; x < img.width * rowWidth; x += rowWidth)
        {
            //BGR
            tgafile.put(static_cast<char>(newImageData[ (y *img.width * rowWidth) + x + 2 ]));
            tgafile.put(static_cast<char>(newImageData[ (y *img.width * rowWidth) + x + 1 ]));
            tgafile.put(static_cast<char>(newImageData[ (y *img.width * rowWidth) + x + 0 ]));
        }

    // The file footer. This part is totally optional.
    static const char footer[TGA_FOOTER_SIZE] =
            "\0\0\0\0"  // no extension area
            "\0\0\0\0"  // no developer directory
            "TRUEVISION-XFILE"  // yep, this is a TGA file
            ".";
    tgafile.write(footer, TGA_FOOTER_SIZE);

    tgafile.close();
    delete [] newImageData;

    return true;
}

bool RdbImageIO::writeRdbImageToCsv(RDB_IMAGE_t& img, const char *filename, bool flipped)
{
    unsigned int rowWidth = 0;
    switch(img.pixelFormat)
    {
        case RDB_PIX_FORMAT_RGB8:
            rowWidth = 3;
            break;

        case RDB_PIX_FORMAT_RGB32F:
            rowWidth = 3;
        break;

        case RDB_PIX_FORMAT_RED32F:
            rowWidth = 3;
        break;

        case RDB_PIX_FORMAT_RED8:
            rowWidth = 1;
        break;

    default:
        VTD_LOG_ERR("VtdToolkit: Unsupported pixel format" << std::hex << img.pixelFormat << " for raw .csv files.");
        return false;
    }

    std::ofstream file(filename);
    unsigned int width = img.width * rowWidth;
    unsigned int height = img.height;

    unsigned char* shmData = reinterpret_cast<unsigned char*>(&img + 1);
    unsigned char* newImageData = new unsigned char[img.imgSize];

    flipedData(flipped, shmData, newImageData, img.imgSize, img, rowWidth);

    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; x += rowWidth)
        {
            if (img.pixelFormat == RDB_PIX_FORMAT_RGB8 || img.pixelFormat == RDB_PIX_FORMAT_RED8)
            {
                unsigned char value = reinterpret_cast<char*>(newImageData)[x + y * width ];
                file << std::fixed << value;
            }

            if (img.pixelFormat == RDB_PIX_FORMAT_RGB32F || img.pixelFormat == RDB_PIX_FORMAT_RED32F)
            {
                float value = reinterpret_cast<float*>(newImageData)[x + y * width ];
                if (value < 0.001)
                     value = 0.0;

                file << std::fixed << std::setprecision(FLOAT_PRECISION) << value;
            }

             if (x < width - rowWidth) {
                 file << ",";
             }
         }
         file << "\n";
     }

    delete [] newImageData;

    return true;
}

#ifdef JPEG_ENABLED
bool RdbImageIO::writeRdbImageToJpg(RDB_IMAGE_t& img, const char* filename, bool flipped, int quality)
{
    unsigned int rowWidth = 0;
    switch(img.pixelFormat)
    {
        case RDB_PIX_FORMAT_RGB8:
            rowWidth = 3;
            break;
        case RDB_PIX_FORMAT_RGBA8:
            rowWidth = 4;
            break;
    default:
        VTD_LOG_ERR("VtdToolkit: Unsupported pixel format" << std::hex << img.pixelFormat << " for jpeg .jpeg files.");
        return false;
    }
    if (quality < 0 || quality > 100)
        quality = DEF_JPG_QUALITY;

    // This struct contains the JPEG compression parameters and pointers to working space (which is allocated as needed by the JPEG library).
     struct jpeg_compress_struct cinfo;
    // This struct represents a JPEG error handler.
    struct jpeg_error_mgr jerr;
    /* target file */
    FILE * outfile;
    JSAMPROW row_pointer[1];
    int row_stride;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    //write file
    if ((outfile = fopen(filename, "wb")) == NULL)
    {
      fprintf(stderr, "can't open %s\n", filename);
      return false;
    }

    jpeg_stdio_dest(&cinfo, outfile);
    /* image width and height, in pixels */
    cinfo.image_width = img.width;
    cinfo.image_height = img.height;
    cinfo.input_components = rowWidth;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);
    jpeg_start_compress(&cinfo, TRUE);
    row_stride = img.width * rowWidth;	/* JSAMPLEs per row in image_buffer */
    JSAMPLE* shmData = reinterpret_cast<JSAMPLE*>(&img + 1);
    JSAMPLE* newImageData = new JSAMPLE[img.imgSize];

    flipedData(flipped, shmData, newImageData, img.imgSize, img, rowWidth);

    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = &newImageData[cinfo.next_scanline * row_stride];
        static_cast<void>(jpeg_write_scanlines(&cinfo, row_pointer, 1));
    }
    /* Step 6: Finish compression */
    jpeg_finish_compress(&cinfo);
    /* After finish_compress, we can close the output file. */
    fclose(outfile);
    /* Step 7: release JPEG compression object */
    /* This is an important step since it will release a good deal of memory. */
    jpeg_destroy_compress(&cinfo);
    /* And we're done! */
    delete [] newImageData;
    
    return true;
  }
#endif // JPEG_ENABLED

//TODO: Due to circular dependencies this is being deactivated for now, and will be replaced by a better solution later on.
//TODO: To write images into HDF files please use the WriteHdf5Image class from VtdHdf5 directly
//#ifdef HDF_ENABLED
//bool RdbImageIO::writeRdbImageToHdf5(RDB_IMAGE_t& img, const char* fileName, bool flipped, const std::string& imageName)
//{
//    unsigned int rowWidth = 0;
//    switch(img.pixelFormat)
//    {
//        case RDB_PIX_FORMAT_RGB8:
//        {
//            rowWidth = 3;
//            RdbToHdf5Writer::WriteHdf5Image writeHdf5Image;

//            writeHdf5Image.openFile(fileName);

//            unsigned char* shmData = reinterpret_cast<unsigned char*>(&img + 1);
//            boost::scoped_ptr<unsigned char> newImageData (new unsigned char[img.imgSize]);

//            flipedData(flipped, shmData, newImageData.get(), img.imgSize, img, rowWidth);

//            if ((!writeHdf5Image.writeImage(*newImageData.get(), img.width, img.height, imageName.c_str())) == -1)
//                return false;

//            writeHdf5Image.closeFile();
//        } break;

//        case RDB_PIX_FORMAT_RGB32F:
//        case RDB_PIX_FORMAT_RED32F:
//        {
//            rowWidth = 3;
//            RdbToHdf5Writer::WriteHdf532FGrid writeHdf532FGrid(img.height, img.width, rowWidth);

//            hid_t fileId = writeHdf532FGrid.openFile(fileName);

//            writeHdf532FGrid.createdFloatDataSpace();

//            writeHdf532FGrid.createdFloatDataSet(imageName, fileId);


//            unsigned char* shmData = reinterpret_cast<unsigned char*>(&img + 1);

//            boost::scoped_ptr<unsigned char> newImageData (new unsigned char[img.imgSize]);

//            flipedData(flipped, shmData, newImageData.get(), img.imgSize, img, rowWidth);

//            if (writeHdf532FGrid.writeFloatData(*newImageData.get()) == -1)
//                return false;

//            writeHdf532FGrid.closeFloatDataSpace();

//            writeHdf532FGrid.closeFloatDataSet();

//            writeHdf532FGrid.closeFile();

//        } break;

//        VTD_LOG_ERR("VtdToolkit: Unsupported pixel format" << std::hex << img.pixelFormat << " for hdf5 .h5 files.");
//        return false;
//    }


//    return true;
//}
//#endif // HDF_ENABLED

bool RdbImageIO::writeRdbImgToFile(RDB_IMAGE_t& img, const std::string& filePath, FileFormat::Enum format, int compressionLevel, bool flipImage)
{
    switch(format) {
#ifdef PNG_ENABLED
        case FileFormat::PNG:
            return writeRdbImageToPng(img, filePath, compressionLevel, PNG_FILTER_NONE, flipImage); //dont use filters for now - too slow
#endif // PNG_ENABLED
        case FileFormat::RawData:
            return writeRdbImgToRawData(img, filePath, flipImage);
        case FileFormat::BMP:
            return writeRdbImageToBmp(img, filePath.c_str(), flipImage);
        case FileFormat::TGA:
            return writeRdbImageToTga(img, filePath.c_str(), flipImage);
        case FileFormat::CSV:
            return writeRdbImageToCsv(img, filePath.c_str(), flipImage);
#ifdef JPEG_ENABLED
        case FileFormat::JPG:
            return writeRdbImageToJpg(img, filePath.c_str(), flipImage, compressionLevel);
#endif // JPEG_ENABLED

//TODO: Due to circular dependencies this is being deactivated for now, and will be replaced by a better solution later on.
//TODO: To write images into HDF files please use the WriteHdf5Image class from VtdHdf5 directly
//#ifdef HDF_ENABLED
//        case FileFormat::HDF5:
//            return writeRdbImageToHdf5(img, filePath.c_str(), flipImage);
//#endif //HDF_ENABLED

        default:
            VTD_LOG("VtdToolkit: Unknown Image Format, RDB image will be exported in raw format instead.");
            return writeRdbImgToRawData(img, filePath.c_str(), flipImage);
    }
}

} //namespace Util
