#include <gtest/gtest.h>

#include <VtdEncryption/VtdEncryption.h>

TEST(VtdEncryptionTest, LoadFailTest)
{
    VTD::VtdEncryption* encrypt1 = VTD::VtdEncryption::load("ee");
    EXPECT_EQ(NULL, encrypt1);

    VTD::VtdEncryption* encrypt2 = VTD::VtdEncryption::load("");
    EXPECT_EQ(NULL, encrypt2);
}

TEST(VtdEncryptionTest, UnLoadTest)
{
    bool isUnloadOk = VTD::VtdEncryption::unload();
    EXPECT_TRUE(isUnloadOk);
}

TEST(VtdEncryptionTest, checkFileExtension)
{
    bool isExtensionOk;
    isExtensionOk = VTD::VtdEncryption::checkFileExtension("noFile");
    EXPECT_FALSE(isExtensionOk);
    isExtensionOk = VTD::VtdEncryption::checkFileExtension("test.xml");
    EXPECT_FALSE(isExtensionOk);
    isExtensionOk = VTD::VtdEncryption::checkFileExtension("test.exml");
    EXPECT_TRUE(isExtensionOk);
    isExtensionOk = VTD::VtdEncryption::checkFileExtension("test.ehtml");
    EXPECT_TRUE(isExtensionOk);
}