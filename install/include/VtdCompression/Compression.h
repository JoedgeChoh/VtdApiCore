#ifndef VtdFramework_COMPRESSION_H
#define VtdFramework_COMPRESSION_H

#include <VtdCore/BasicTypes.h>
#include <VtdCore/Macros.h>

namespace VTD {

namespace CompressionType {
    enum Enum {
        UNDEFINED,
        ZLIB,
        LZ4
    };
} // namespace CompressionType

struct CompressionHeader
{
    CompressionHeader(void) :
        compressionType(CompressionType::UNDEFINED),
        compressedSize(0u),
        decompressedSize(0u),
        magicNumber(0u)
    {}

    unsigned char compressionType;
    UInt32 compressedSize;
    UInt32 decompressedSize;
    UInt32 magicNumber;
};

class Compression VTD_FINAL
{
public:

    /**
     * Compress data using the selected compression method. A header will be attached to the data to prevent decompression by third parties.
     * @param type enum specifying the type of compression to use.
     * @param uncompressedData a reference to the beginning of the uncompressed data.
     * @param uncompressedSize the size of the uncompressed data, in bytes.
     * @param compressedData on success this output variable will contain the pointer to the beginning of the compressed data.
     * @param compressedSize on success this output variable will contain the size of the compressed data.
     * @returns
     */
    static bool compressData(const CompressionType::Enum type, const unsigned char& uncompressedData, const SizeType uncompressedSize, unsigned char*& compressedData, SizeType& compressedSize);

    /**
     * Decompress data using the selected compression method. The header will be read and removed, also the compression method will be read from the header.
     * @param compressedData a reference to the beginning of the compressed data.
     * @param compressedSize the size of the compressed data, in bytes.
     * @param decompressedData on success this output variable will contain the pointer to the beginning of the decompressed data.
     * @param decompressedSize on success this output variable will contain the size of the decompressed data.
     */
    static bool decompressData(const unsigned char& compressedData, const SizeType compressedSize, unsigned char*& decompressedData, SizeType& decompressedSize);

private:
    Compression(void) {}
    ~Compression(void) {}
};

} // namespace VTD

#endif // VtdFramework_COMPRESSION_H
