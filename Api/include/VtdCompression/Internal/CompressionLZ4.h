#ifndef VtdFramework_COMPRESSION_LZ4_H
#define VtdFramework_COMPRESSION_LZ4_H

#include <VtdCore/BasicTypes.h>
#include <VtdCore/Macros.h>

namespace VTD {
namespace Internal {

    class CompressionLZ4 VTD_FINAL {
    public:
        /**
         * @brief createLZ4compressedData compresses a sequence of bytes using LZ4 compression.
         * @param uncompressedData reference to the beginning of the uncompressed data.
         * @param uncompressedSize size in bytes of the uncompressed data.
         * @param compressedSize output parameter of the size in bytes of the compressed data.
         * @return a pointer to the beginning of the compressed data on success, NULL otherwise.
         */
        static unsigned char* createLZ4compressedData(const unsigned char& uncompressedData, SizeType uncompressedSize,
                                                      SizeType &compressedSize);

        /**
         * @brief createLZ4decompressedData decompresses a sequence of bytes using LZ4 compression.
         * @param compressedData reference to the beginning of the compressed data.
         * @param compressedSize size in bytes of the compressed data.
         * @param uncompressedSize expected size in bytes of the uncompressed data.
         * @return a pointer to the beginning of the decompressed data on success, NULL otherwise.
         */
        static unsigned char* createLZ4decompressedData(const unsigned char& compressedData, SizeType compressedSize,
                                                        SizeType uncompressedSize);

    private:
        CompressionLZ4(void) {}
        ~CompressionLZ4(void) {}
    };

} //namespace Internal
} // namespace VTD

#endif // VtdFramework_COMPRESSION_LZ4_H
