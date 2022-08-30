#include "VtdCompression/Compression.h"
#include "VtdCompression/Internal/CompressionLZ4.h"
#include "VtdCompression/Internal/CompressionZLIB.h"

#include <limits>
#include <stddef.h>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#include <boost/numeric/conversion/cast.hpp>

namespace VTD {

using namespace Internal;

bool Compression::compressData(const CompressionType::Enum type, const unsigned char& uncompressedData, const SizeType uncompressedSize, unsigned char*& compressedDataOut, SizeType& compressedSizeOut)
{
    if (uncompressedSize == 0u)
    {
        return false;
    }

    unsigned char* compressedRawData = NULL;
    SizeType compressedRawDataSize = 0;

    switch (type) {
    case CompressionType::ZLIB:
        compressedRawData = CompressionZLIB::createZLIBcompressedData(uncompressedData, uncompressedSize, compressedRawDataSize);
        break;

    case CompressionType::LZ4:
        compressedRawData = CompressionLZ4::createLZ4compressedData(uncompressedData, uncompressedSize, compressedRawDataSize);
        break;

    case CompressionType::UNDEFINED:
    default:
        return false;
    }

    if (compressedRawData == NULL)
    {
        return false;
    }

    CompressionHeader header;
    header.compressionType = type;
    header.magicNumber = std::rand() % std::numeric_limits<UInt32>::max();
    header.compressedSize = boost::numeric_cast<UInt32>(compressedRawDataSize);
    header.decompressedSize = boost::numeric_cast<UInt32>(uncompressedSize);

    // Size = compressed data + header
    compressedSizeOut = compressedRawDataSize + sizeof(CompressionHeader);

    // Put header to final data
    unsigned char* compressedData = new unsigned char[compressedSizeOut];
    memcpy(compressedData, &header, sizeof(CompressionHeader));

    // Copy compressed data to final data
    std::copy(compressedRawData, compressedRawData + compressedRawDataSize, compressedData + sizeof(CompressionHeader));
    delete[] compressedRawData;

    compressedDataOut = compressedData;

    return true;
}

bool Compression::decompressData(const unsigned char& compressedData, const SizeType compressedSize, unsigned char*& decompressedDataOut, SizeType& decompressedSizeOut)
{
    if (compressedSize == 0u)
    {
        return false;
    }

    CompressionHeader header;
    memcpy(&header, &compressedData, sizeof(CompressionHeader));

    // check if the size matches (without header)
    if (compressedSize - sizeof(CompressionHeader) != header.compressedSize)
    {
        return false;
    }

    unsigned char* decompressedData = NULL;

    switch (header.compressionType) {
    case CompressionType::ZLIB:
    {
        int errorNo = 0; // if any error happens decompressedRawData will be NULL
        decompressedData = CompressionZLIB::createZLIBdecompressedData(*(&compressedData + sizeof(CompressionHeader)), header.compressedSize, header.decompressedSize, errorNo);
        break;
    }
    case CompressionType::LZ4:
    {
        decompressedData = CompressionLZ4::createLZ4decompressedData(*(&compressedData + sizeof(CompressionHeader)), header.compressedSize, header.decompressedSize);
        break;
    }
    case CompressionType::UNDEFINED:
    default:
        return false;
    }

    if (decompressedData == NULL)
    {
        delete[] decompressedData;
        return false;
    }

    decompressedSizeOut = header.decompressedSize;
    decompressedDataOut = decompressedData;

    return true;
}

} // namespace VTD
