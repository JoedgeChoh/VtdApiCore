#include "VtdCompression/Internal/CompressionZLIB.h"
#include <boost/cast.hpp>
#include "zlib.h"

namespace VTD { namespace Internal {

unsigned char* CompressionZLIB::createZLIBcompressedData(const unsigned char& uncompressedData, SizeType uncompressedSize, SizeType& compressedSize)
{
    uLongf compressedBuffSize = compressBound(uncompressedSize);
    unsigned char* compressedData = new unsigned char[compressedBuffSize];

    z_stream zInfo  = {};
    zInfo.total_in  = boost::numeric_cast<unsigned long>( uncompressedSize );
    zInfo.avail_in  = boost::numeric_cast<unsigned int> ( uncompressedSize );
    zInfo.next_in   = const_cast<unsigned char*> ( &uncompressedData );
    zInfo.total_out = boost::numeric_cast<unsigned long> ( compressedBuffSize );
    zInfo.avail_out = boost::numeric_cast<unsigned int> ( compressedBuffSize );
    zInfo.next_out  = static_cast<unsigned char*> ( compressedData );
    zInfo.data_type = Z_BINARY;

    int errorNo = deflateInit2(&zInfo, Z_BEST_SPEED, Z_DEFLATED, 15, 9, Z_HUFFMAN_ONLY);
    if ( errorNo == Z_OK ) {
        errorNo = deflate(&zInfo, Z_FINISH);
        if ( errorNo == Z_STREAM_END ) {
            compressedSize = zInfo.total_out;
            errorNo = Z_OK;
        }
    }
    deflateEnd(&zInfo);

    if (errorNo != Z_OK) {
        delete[] compressedData;
        return NULL;
    }

    return reinterpret_cast<unsigned char*>(compressedData);
}

unsigned char* CompressionZLIB::createZLIBdecompressedData(const unsigned char& compressedData, SizeType compressedSize, SizeType uncompressedSize, int& errorNo)
{
    unsigned char* uncompressedData = new unsigned char[uncompressedSize];

    z_stream zInfo  = {};
    zInfo.total_in  = boost::numeric_cast<unsigned long> ( compressedSize );
    zInfo.avail_in  = boost::numeric_cast<unsigned int>  ( compressedSize );
    zInfo.next_in   = const_cast<unsigned char*> ( &compressedData );
    zInfo.total_out = boost::numeric_cast<unsigned long> ( uncompressedSize );
    zInfo.avail_out = boost::numeric_cast<unsigned int>  ( uncompressedSize );
    zInfo.next_out  = static_cast<unsigned char*>( uncompressedData );

    errorNo = inflateInit(&zInfo);
    if (errorNo == Z_OK)
    {
        errorNo = inflate(&zInfo, Z_FINISH);

        if (errorNo == Z_STREAM_END)
        {
            errorNo = Z_OK;
        }
    }

    inflateEnd( &zInfo );

    if (errorNo != Z_OK) {
        delete[] uncompressedData;
        return NULL;
    }

    return uncompressedData;
}

} // namespace Internal
} // namespace VTD
