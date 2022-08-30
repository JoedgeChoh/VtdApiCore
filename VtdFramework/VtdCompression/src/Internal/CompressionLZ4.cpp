#include "VtdCompression/Internal/CompressionLZ4.h"
#include <boost/cast.hpp>
#include <lz4.h>

namespace VTD { namespace Internal {

    unsigned char *
    CompressionLZ4::createLZ4compressedData(const unsigned char& uncompressedData, SizeType uncompressedSize,
                                            SizeType &compressedSize) {
        if (uncompressedSize == 0u) {
            return NULL;
        }

        int compressedBuffSize = LZ4_compressBound( boost::numeric_cast<int>( uncompressedSize ) );
        char *compressedData = new char[boost::numeric_cast<unsigned long>( compressedBuffSize )];
        compressedSize =  boost::numeric_cast<unsigned long>( LZ4_compress_default(reinterpret_cast<const char *>(&uncompressedData), compressedData,
                                               boost::numeric_cast<int>( uncompressedSize ),  boost::numeric_cast<int>( compressedBuffSize ) ) );

        if (compressedSize <= 0) {
            delete[] compressedData;
            return NULL;
        }

        return reinterpret_cast<unsigned char *>(compressedData);
    }

    unsigned char *
    CompressionLZ4::createLZ4decompressedData(const unsigned char& compressedData, SizeType compressedSize,
                                              SizeType uncompressedSize) {
        if (compressedSize == 0u) {
            return NULL;
        }

        char *uncompressedData = new char[uncompressedSize];
        int errorNo = LZ4_decompress_safe(reinterpret_cast<const char *>(&compressedData), uncompressedData,
                                          boost::numeric_cast<int>( compressedSize ), boost::numeric_cast<int>( uncompressedSize ) );

        if (errorNo <= 0) {
            delete[] uncompressedData;
            return NULL;
        }

        return reinterpret_cast<unsigned char *>(uncompressedData);
    }

} // namespace Internal
} // namespace VTD
