#ifndef VtdFramework_COMPRESSION_RLE_H
#define VtdFramework_COMPRESSION_RLE_H

#include <VtdCore/BasicTypes.h>
#include <VtdCore/Macros.h>

namespace VTD {
namespace Internal {

class CompressionRLE VTD_FINAL {
    public:
        /**
         * @brief compress data using run length encoding (RLE).
         * @param uncompressedData a reference to the uncompressed data.
         * @param uncompressedSize the size in bytes of the uncompressed data.
         * @param compressedSize output parameter of the size in bytes of the compressed data.
         * @param bytesPerPixel the pixel stride in bytes.
         * @return a pointer to the beginning of the compressed data on success, NULL otherwise.
         */
        static unsigned char* createRLEcompressedData(const unsigned char& uncompressedData, SizeType uncompressedSize,
                                                      SizeType &compressedSize, unsigned int bytesPerPixel);

        /**
         * @brief decompress run length encoded (RLE) data.
         * @param compressedData a reference to the start of the compressed data.
         * @param compressedSize the size in bytes of the compressed data.
         * @param uncompressedSize the size in bytes of the uncompressed data.
         * @param bytesPerPixel  the pixel stride in bytes.
         * @return a pointer to the beginning of the uncompressed data, NULL otherwise.
         */
        static unsigned char* createRLEdecompressedData(const unsigned char& compressedData, SizeType compressedSize,
                                                        SizeType uncompressedSize, unsigned int bytesPerPixel);

    private:
        CompressionRLE(void) {}
        ~CompressionRLE(void) {}
};

} // namespace Internal
} // namespace VTD

#endif // VtdFramework_COMPRESSION_RLE_H
