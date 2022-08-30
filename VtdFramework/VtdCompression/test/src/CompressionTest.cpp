#include <gtest/gtest.h>

#include <VtdCompression/Compression.h>
#include "MockData.h"

using namespace VTD;

struct CompressionTestParams {
    const CompressionType::Enum type;
    const unsigned char* data;
    const size_t dataSize;
};

typedef ::testing::TestWithParam<CompressionTestParams> CompressionParameterizedTest;
typedef ::testing::TestWithParam<CompressionTestParams> CompressionParameterizedFailingTest;

TEST(CompressionTest, CompressionHeaderSize)
{
    // This test is here to ensure that if the compression header size is changed for whatever reason
    // that one is made aware that this will have implications for reading files that were written with a different header
    // and that files will need to be reexported, or handled as special cases.
    const SizeType CompressionHeaderSize = 16u;
    EXPECT_EQ(CompressionHeaderSize, sizeof(CompressionHeader)); //output parameters should remain untouched
}

TEST(CompressionTest, CompressUndefined)
{
    const unsigned char uncompressedData[4] = {0xff,0xcc,0xff,0xcc};
    unsigned char dummyData = 0x0;
    unsigned char* compressedData = &dummyData; // some value
    SizeType compressedSize = 123u;
    bool result = Compression::compressData(CompressionType::UNDEFINED, uncompressedData[0], 4u, compressedData, compressedSize);

    EXPECT_FALSE(result); // compression failed (undefined compression type)
    EXPECT_EQ(&dummyData, compressedData); //output parameters should remain untouched
    EXPECT_EQ(123u, compressedSize); //output parameters should remain untouched
}

TEST_P(CompressionParameterizedTest, CompressAndDecompress)
{
    const CompressionTestParams& params = GetParam();

    unsigned char* compressedData = NULL;
    SizeType compressedSize;

    //compression
    bool result = Compression::compressData(params.type, *params.data, params.dataSize, compressedData, compressedSize);

    EXPECT_TRUE(result);
    EXPECT_NE(NULLPTR, compressedData);
    EXPECT_LT(0, compressedSize);

    //decompression
    unsigned char* decompressedData = NULL;
    SizeType decompressedSize;
    result = Compression::decompressData(*compressedData, compressedSize, decompressedData, decompressedSize);

    EXPECT_TRUE(result);
    EXPECT_NE(NULLPTR, decompressedData);
    EXPECT_EQ(params.dataSize, decompressedSize);
    for(SizeType i = 0; i < decompressedSize; ++i)
    {
        EXPECT_EQ(params.data[i], decompressedData[i]);
    }
}

TEST_P(CompressionParameterizedFailingTest, CompressFail)
{
    const CompressionTestParams& params = GetParam();

    unsigned char* compressedData = NULL;
    SizeType compressedSize = ~0u;

    //compression
    bool result = Compression::compressData(params.type, *params.data, params.dataSize, compressedData, compressedSize);

    EXPECT_FALSE(result);
    EXPECT_EQ(NULLPTR, compressedData);
    EXPECT_EQ(~0u, compressedSize);
}

INSTANTIATE_TEST_CASE_P(
    CompressionTests,
    CompressionParameterizedTest,
    ::testing::Values(
            (CompressionTestParams){CompressionType::LZ4, DATA, DATA_SIZE},
            (CompressionTestParams){CompressionType::LZ4, DATA, DATA_SIZE-1},
            (CompressionTestParams){CompressionType::LZ4, DATA, DATA_SIZE/3},
            (CompressionTestParams){CompressionType::ZLIB, DATA, DATA_SIZE},
            (CompressionTestParams){CompressionType::ZLIB, DATA, DATA_SIZE-1},
            (CompressionTestParams){CompressionType::ZLIB, DATA, DATA_SIZE/3}
    )
);

INSTANTIATE_TEST_CASE_P(
        CompressFail,
        CompressionParameterizedFailingTest,
        ::testing::Values(
                (CompressionTestParams){CompressionType::LZ4, DATA, 0},
                (CompressionTestParams){CompressionType::ZLIB, DATA, 0},
                (CompressionTestParams){CompressionType::UNDEFINED, DATA, DATA_SIZE}
        )
);
