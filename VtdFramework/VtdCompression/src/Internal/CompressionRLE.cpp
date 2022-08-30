#include "VtdCompression/Internal/CompressionRLE.h"

#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdint.h>

namespace VTD { namespace Internal {

#define IMAGE_MAX_BYTES_PER_PIXEL 16u

unsigned char* CompressionRLE::createRLEcompressedData(const unsigned char& uncompressedData, SizeType uncompressedSize, SizeType &compressedSize, unsigned int bytesPerPixel)
{
    unsigned int bytes = std::min(bytesPerPixel, IMAGE_MAX_BYTES_PER_PIXEL);
    if (uncompressedSize != 0 && bytes > 0) {

        unsigned char* tmpData = new unsigned char[uncompressedSize];

        uint32_t write_pos = 0;
        unsigned char frequency = 1;
        unsigned int writeOffset = bytes + 1;

        unsigned char character[IMAGE_MAX_BYTES_PER_PIXEL];
        unsigned char next_character[IMAGE_MAX_BYTES_PER_PIXEL];

        for (unsigned int c = 0; c < IMAGE_MAX_BYTES_PER_PIXEL; ++c) {
            character[c] = 0;
            next_character[c] = 0;
        }

        bool endOfData = false;
        bool isEqual = false;

        for(uint32_t i = 0; i < uncompressedSize; i += bytes)
        {
            for (unsigned int c = 0; c < bytes; ++c) {
                character[c] = (&uncompressedData)[i + c];
            }

            if (i + bytes < uncompressedSize) {
                for (unsigned int c = 0; c < bytes; ++c) {
                    next_character[c] = (&uncompressedData)[i + c + bytes];
                }
            } else {
                endOfData =  true;
            }

            //compare
            isEqual = true;
            for (unsigned int c = 0; c < bytes && isEqual; ++c) {
                isEqual = character[c] == next_character[c];
            }

            if(!isEqual || frequency == 255 || endOfData)
            {
                if (write_pos + writeOffset < uncompressedSize) {

                    tmpData[write_pos] = frequency;

                    for (unsigned int c = 0; c < bytes; ++c) {
                        tmpData[write_pos + c + 1] = character[c];
                    }

                    write_pos += writeOffset;
                    frequency = 0;
                } else {
                    //fail: compressed data is bigger than incoming data
                    std::cerr << "VtdCompression: WARNING: VTD::createRLEcompressedData: compression size will exceed uncompressed size, aborting compression." << std::endl;
                    delete[] tmpData;
                    return NULL;
                }
            }

            for (unsigned int c = 0; c < bytes; ++c) {
                character[c] = next_character[c];
            }

            ++frequency;
        }


        compressedSize = write_pos;

        unsigned char* compressedData = new unsigned char[compressedSize];
        memcpy(compressedData, tmpData, compressedSize);
        delete[] tmpData;

        return compressedData;
    }
    return NULL;
}

unsigned char* CompressionRLE::createRLEdecompressedData(const unsigned char& compressedData, SizeType compressedSize, SizeType uncompressedSize, unsigned int bytesPerPixel)
{
    unsigned int bytes = std::min(bytesPerPixel, IMAGE_MAX_BYTES_PER_PIXEL);
    unsigned int writeOffset = bytes + 1;
    if (compressedSize >= writeOffset) {

        unsigned char* uncompressedData = new unsigned char[uncompressedSize];

        uint32_t write_pos = 0;
        unsigned char frequency = 0;

        unsigned char character[IMAGE_MAX_BYTES_PER_PIXEL];

        for (unsigned int c = 0; c < IMAGE_MAX_BYTES_PER_PIXEL; ++c) {
            character[c] = 0;
        }

        for(uint32_t i = 0; i < compressedSize; i += writeOffset)
        {
            frequency = (&compressedData)[i];

            for (unsigned int c = 0; c < bytes; ++c) {
                character[c] = (&compressedData)[i + 1 + c];
            }

            if (write_pos + frequency * bytes - 1 < uncompressedSize) {
                for(int j = 0; j < frequency; ++j)
                {
                    for (unsigned int c = 0; c < bytes; ++c) {
                        uncompressedData[write_pos] = character[c];
                        ++write_pos;
                    }
                }
            } else {
                //fail: uncompressed data is bigger than the buffer
                std::cerr << "VtdCompression: WARNING: VTD::createRLEdecompressedData: current write position " << write_pos << " at index"  << i << " will exceed size " << uncompressedSize <<  " with " << frequency*bytes << std::endl;
                std::cerr << "VtdCompression: WARNING: VTD::createRLEdecompressedData: aborting decompression." << std::endl;
                delete[] uncompressedData;
                return NULL;
            }
        }

        return uncompressedData;
    }
    return NULL;
}

} // namespace Internal
} // namespace VTD
