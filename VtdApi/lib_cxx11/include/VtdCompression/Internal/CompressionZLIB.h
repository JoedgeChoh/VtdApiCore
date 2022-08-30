#ifndef VtdFramework_COMPRESSION_ZLIB_H
#define VtdFramework_COMPRESSION_ZLIB_H

#include <VtdCore/BasicTypes.h>
#include <VtdCore/Macros.h>

namespace VTD {
namespace Internal {

    class CompressionZLIB VTD_FINAL {
    public:

        /**
         * @brief createZLIBcompressedData compresses a sequence of bytes using ZLIB compression.
         * @param uncompressedData a reference to the uncompressed data.
         * @param uncompressedSize the size in bytes of the uncompressed data.
         * @param compressedSize output parameter of the size in bytes of the compressed data.
         * @return a pointer to the beginning of the compressed data on success, NULL otherwise.
         */
        static unsigned char* createZLIBcompressedData(const unsigned char& uncompressedData, SizeType uncompressedSize,
                                                       SizeType& compressedSize);

        /**
         * @brief createZLIBdecompressedData decompresses a sequence of bytes using ZLIB compression.
         * @param compressedData reference to the beginning of the compressed data.
         * @param compressedSize size in bytes of the compressed data.
         * @param uncompressedSize expected size of the uncompressed data, in bytes.
         * @param errorNo output parameter specifying the error code written by ZLIB.
         * @return a pointer to the beginning of the decompressed data on success, NULL otherwise.
         */
        static unsigned char* createZLIBdecompressedData(const unsigned char& compressedData, SizeType compressedSize,
                                                         SizeType uncompressedSize, int &errorNo);

    private:
        CompressionZLIB(void) {}
        ~CompressionZLIB(void) {}
    };

} //namespace Internal
} // namespace VTD

#endif // VtdFramework_COMPRESSION_ZLIB_H
