#include <gtest/gtest.h>
#include <VtdCore/BasicTypes.h>

using namespace VTD;

TEST(VTDTypesTest, SizeTest)
{
    EXPECT_EQ(sizeof(UInt8), 1);
    EXPECT_EQ(sizeof(UInt16), 2);
    EXPECT_EQ(sizeof(UInt32), 4);

    EXPECT_EQ(sizeof(UInt8), 1);
    EXPECT_EQ(sizeof(UInt16), 2);
    EXPECT_EQ(sizeof(UInt32), 4);

#ifdef VTD_INT64_AVAILABLE
    EXPECT_EQ(sizeof(Int64), 8);
    EXPECT_EQ(sizeof(UInt64), 8);
#endif
}

