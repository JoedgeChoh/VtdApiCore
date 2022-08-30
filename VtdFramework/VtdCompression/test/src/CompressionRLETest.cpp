#include <gtest/gtest.h>

#include <VtdCompression/Internal/CompressionRLE.h>

#include "MockData.h"

using namespace VTD;
using namespace Internal;

TEST(CompressionRLE_Test, CompressAbort)
{
    //test will abort as compressed data size will exceed uncompressed data size
    SizeType compressedSize = 0;
    SizeType decompressedSize = DATA_SIZE;
    const unsigned int bytesPerPixel = 32;

    unsigned char* compressedData = CompressionRLE::createRLEcompressedData(DATA_REF, decompressedSize, compressedSize, bytesPerPixel);

    EXPECT_EQ(NULLPTR, compressedData);
    EXPECT_EQ(0, compressedSize);
}

TEST(CompressionRLE_Test, CompressBmpData)
{
    //compression
    SizeType compressedSize;
    unsigned char* compressedData = CompressionRLE::createRLEcompressedData(BITMAP::REF, BITMAP::SIZE, compressedSize, BITMAP::STRIDE);

    ASSERT_NE(NULLPTR, compressedData);
    EXPECT_LT(0, compressedSize);

    //decompression
    unsigned char* decompressedData = CompressionRLE::createRLEdecompressedData(*compressedData, compressedSize, BITMAP::SIZE, BITMAP::STRIDE);

    ASSERT_NE(NULLPTR, decompressedData);
    for(SizeType i = 0; i < BITMAP::SIZE; ++i)
    {
        EXPECT_EQ(BITMAP::DATA[i], decompressedData[i]);
    }
}

TEST(CompressionRLE_Test, CompressBmpGeneratedData)
{
    //generate random data
    const BmpData data(1024, 32, 0, 32);
    ASSERT_NE(NULLPTR, data.getData());

    //compression
    SizeType compressedSize;
    unsigned char* compressedData = CompressionRLE::createRLEcompressedData(data.getDataRef(), data.getSize(), compressedSize, data.getStride());

    ASSERT_NE(NULLPTR, compressedData);
    EXPECT_LT(0, compressedSize);

    //decompression
    unsigned char* decompressedData = CompressionRLE::createRLEdecompressedData(*compressedData, compressedSize, data.getSize(), data.getStride());

    ASSERT_NE(NULLPTR, decompressedData);
    for(SizeType i = 0; i < data.getSize(); ++i)
    {
        EXPECT_EQ(data.getData()[i], decompressedData[i]);
    }
}