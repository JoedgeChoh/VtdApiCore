#include <gtest/gtest.h>
#include <VtdMath/Vector.h>

using namespace VTD;

TEST(VectorTest, CtorTest)
{
    Vector3 a;
    EXPECT_EQ(a.x(), 0.0);
    EXPECT_EQ(a.y(), 0.0);
    EXPECT_EQ(a.z(), 0.0);

    a = Vector3(1.0, 2.0, 3.0);
    EXPECT_EQ(a.x(), 1.0);
    EXPECT_EQ(a.y(), 2.0);
    EXPECT_EQ(a.z(), 3.0);

    double values[3] = {4.0, 5.0, 6.0};
    a = Vector3(values);
    EXPECT_EQ(a.x(), 4.0);
    EXPECT_EQ(a.y(), 5.0);
    EXPECT_EQ(a.z(), 6.0);

    Vector3 b(a);
    EXPECT_EQ(b.x(), 4.0);
    EXPECT_EQ(b.y(), 5.0);
    EXPECT_EQ(b.z(), 6.0);
}

TEST(VectorTest, AccessorTest)
{
    Vector3 a(1.0, 2.0, 3.0);
    EXPECT_EQ(a.x(), 1.0);
    EXPECT_EQ(a.y(), 2.0);
    EXPECT_EQ(a.z(), 3.0);

    EXPECT_EQ(a.h(), 1.0);
    EXPECT_EQ(a.p(), 2.0);
    EXPECT_EQ(a.r(), 3.0);

    EXPECT_EQ(a[0], 1.0);
    EXPECT_EQ(a[1], 2.0);
    EXPECT_EQ(a[2], 3.0);

    a[0] = 4.0;
    a[1] = 5.0;
    a[2] = 6.0;

    EXPECT_EQ(a.x(), 4.0);
    EXPECT_EQ(a.y(), 5.0);
    EXPECT_EQ(a.z(), 6.0);
}

//Vector3lf& operator+=(const Vector3lf &other);
TEST(VectorTest, AdditionTest)
{
    Vector3 a;
    EXPECT_EQ(a.x(), 0.0);
    EXPECT_EQ(a.y(), 0.0);
    EXPECT_EQ(a.z(), 0.0);

    a += Vector3(1.0, 1.0, 1.0);
    EXPECT_EQ(a.x(), 1.0);
    EXPECT_EQ(a.y(), 1.0);
    EXPECT_EQ(a.z(), 1.0);

    Vector3 c = a + Vector3(1.0, 2.0, 3.0);
    EXPECT_EQ(c.x(), 2.0);
    EXPECT_EQ(c.y(), 3.0);
    EXPECT_EQ(c.z(), 4.0);
}

TEST(VectorTest, SubtractionTest)
{
    Vector3 a;
    EXPECT_EQ(a.x(), 0.0);
    EXPECT_EQ(a.y(), 0.0);
    EXPECT_EQ(a.z(), 0.0);

    a -= Vector3(1.0, 1.0, 1.0);
    EXPECT_EQ(a.x(), -1.0);
    EXPECT_EQ(a.y(), -1.0);
    EXPECT_EQ(a.z(), -1.0);

    Vector3 c = a - Vector3(1.0, 2.0, 3.0);
    EXPECT_EQ(a.x(), -1.0);
    EXPECT_EQ(a.y(), -1.0);
    EXPECT_EQ(a.z(), -1.0);
    EXPECT_EQ(c.x(), -2.0);
    EXPECT_EQ(c.y(), -3.0);
    EXPECT_EQ(c.z(), -4.0);
}

TEST(VectorTest, MultiplicationTest)
{
    Vector3 a(1.0, 2.0, 3.0);

    a *= 2.0;
    EXPECT_EQ(a.x(), 2.0);
    EXPECT_EQ(a.y(), 4.0);
    EXPECT_EQ(a.z(), 6.0);

    Vector3 c = a * 2.0;
    EXPECT_EQ(a.x(), 2.0);
    EXPECT_EQ(a.y(), 4.0);
    EXPECT_EQ(a.z(), 6.0);
    EXPECT_EQ(c.x(), 4.0);
    EXPECT_EQ(c.y(), 8.0);
    EXPECT_EQ(c.z(), 12.0);
}

TEST(VectorTest, CrossProductTest)
{
    const Vector3 a(1.0, 2.0, 3.0);
    const Vector3 b(4.0, 5.0, 6.0);
    Vector3 c = a.cross(b);

    const Vector3 exp(-3.0, 6.0, -3.0);
    EXPECT_EQ(c.x(), exp.x());
    EXPECT_EQ(c.y(), exp.y());
    EXPECT_EQ(c.z(), exp.z());
}

TEST(VectorTest, DotProductTest)
{
    const Vector3 a(1.0, 2.0, 3.0);
    const Vector3 b(4.0, 5.0, 6.0);
    double dot = a.dot(b);

    EXPECT_EQ(dot, 32.0);
}

TEST(VectorTest, LengthTest)
{
    Vector3 a(1.0, 2.0, 3.0);
    double length = a.length();
    double lengthSq = a.lengthSquared();

    EXPECT_DOUBLE_EQ(length, 3.7416573867739413);
    EXPECT_DOUBLE_EQ(lengthSq, 14.0);
}

TEST(VectorTest, NormalizationTest)
{
    Vector3 a(10.0, 0.0, 0.0);
    a.normalize();
    EXPECT_DOUBLE_EQ(a.length(), 1.0);
    EXPECT_DOUBLE_EQ(a.x(), 1.0);

    a = Vector3(1.0, 2.0, 3.0);
    a.normalize();
    EXPECT_DOUBLE_EQ(a.length(), 1.0);
    EXPECT_FLOAT_EQ(a.x(), 0.2672612419124244);
    EXPECT_DOUBLE_EQ(a.y(), 0.53452248382484879);
    EXPECT_DOUBLE_EQ(a.z(), 0.80178372573727319);
}

TEST(VectorTest, DISABLED_RotateTest)
{
    /* TODO */
}

TEST(VectorTest, DISABLED_AngleTest)
{
    /* TODO */
}

