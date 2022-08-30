#include <gtest/gtest.h>
#include "VtdEncryptionCommon.h"
#include "ExampleVtdEncryptionPlugin.h"
#include <fstream>

/*
 * Test for encrypting a non existing file 
 */
TEST(VtdEncryptionTest, encryptWithNonExistingFile)
{
    ExampleVtdEncryptionPlugin encrypt;
    const char* nonExistingFile = "noFile";
    std::remove(nonExistingFile);

    bool isEncryptOk = encrypt.encryptFile(nonExistingFile, nonExistingFile, nonExistingFile);
    EXPECT_FALSE(isEncryptOk);

    isEncryptOk = encrypt.encryptFile(nonExistingFile, "test.xml", "test.xml.decrypted");
    EXPECT_FALSE(isEncryptOk);

    isEncryptOk = encrypt.encryptFile("pub.pem", nonExistingFile, "test.xml.decrypted");
    EXPECT_FALSE(isEncryptOk);

    isEncryptOk = encrypt.encryptFile("pub.pem", "test.xml", nonExistingFile);
    EXPECT_TRUE(isEncryptOk);
}

/*
 * Test for decrypting a non existing file 
 */
TEST(VtdEncryptionTest, decryptWithNonExistingFile)
{
    ExampleVtdEncryptionPlugin encrypt;
    const char* nonExistingFile = "noFile";
    std::remove(nonExistingFile);

    bool isDecryptOk = encrypt.decryptFile( nonExistingFile, nonExistingFile);
    EXPECT_FALSE(isDecryptOk);
}

/**
 * Test for decrypting a file that was not encrypted
 */
TEST(VtdEncryptionTest, decryptIncorrectFile)
{
    ExampleVtdEncryptionPlugin encrypt;
    const char* nonExistingFile = "noFile";
    const char* testFile = "test.xml";

    bool isDecryptOk = encrypt.decryptFile( testFile, nonExistingFile);
    EXPECT_FALSE(isDecryptOk);

    std::remove(nonExistingFile);
}

/*
 * Test for encrypting, decrypting and comparing the contents with small size of file
 * 1- test.xml file is encrypted into test.xml.encrypted
 * 2- test.xml.encrypted file is decrypted to test.xml.decrypted
 * 3- content of test.xml and test.xml.decrypted files are compared
 */
TEST(VtdEncryptionTest, encryptDecryptFileSmall)
{
    ExampleVtdEncryptionPlugin encrypt;
    encrypt.encryptFile( "pub.pem","demo.html", "demo.html.encrypted");
    encrypt.decryptFile( "demo.html.encrypted", "demo.html.decrypted");

    std::ifstream input1("demo.html");
    std::ifstream input2("demo.html.decrypted");
    std::string testData, decryptedData;
    getline (input1, testData, (char) input1.eof());
    getline (input2, decryptedData, (char) input2.eof());
    EXPECT_STREQ(testData.c_str(),decryptedData.c_str());
}

/*
 * Test for encrypting, decrypting and comparing the contents with medium size of content
 * 1- test.xml file is encrypted into test.xml.encrypted
 * 2- test.xml.encrypted file is decrypted to test.xml.decrypted
 * 3- content of test.xml and test.xml.decrypted files are compared
 */
TEST(VtdEncryptionTest, encryptDecryptFileMedium)
{
    ExampleVtdEncryptionPlugin encrypt;
    encrypt.encryptFile( "pub.pem","test.xml", "test.xml.encrypted");
    encrypt.decryptFile( "test.xml.encrypted", "test.xml.decrypted");

    std::ifstream input1("test.xml");
    std::ifstream input2("test.xml.decrypted");
    std::string testData, decryptedData;
    getline (input1, testData, (char) input1.eof());
    getline (input2, decryptedData, (char) input2.eof());
    EXPECT_STREQ(testData.c_str(),decryptedData.c_str());
}


/*
 * Test for encrypting, decrypting and comparing the contents with small size of content
 * 1- save demo.html file into string
 * 2- encrypt the string and save to demo.ehtml file
 * 3- decrypt demo.ehtml file and save as string
 * 4- compare the contents
 */
TEST(VtdEncryptionTest, encryptDecryptSmall)
{
    std::string dataToEncrypt;
    std::string dataDecrypted;
    std::ifstream input("demo.html");
    getline (input, dataToEncrypt, (char) input.eof());

    ExampleVtdEncryptionPlugin encrypt;
    encrypt.encrypt( "pub.pem", dataToEncrypt, "demo.ehtml" );
    encrypt.decrypt( "demo.ehtml", dataDecrypted );
    
    // compare two strings
    EXPECT_STREQ(dataToEncrypt.c_str(),dataDecrypted.c_str());
}

/*
 * Test for encrypting, decrypting and comparing the contents with medium size of content
 * 1- save test.xml file into string
 * 2- encrypt the string and save to test.exml file
 * 3- decrypt test.exml file and save as string
 * 4- compare the contents
 */
TEST(VtdEncryptionTest, encryptDecryptMedium)
{
    std::string dataToEncrypt;
    std::string dataDecrypted;
    std::ifstream input("test.xml");
    getline (input, dataToEncrypt, (char) input.eof());

    ExampleVtdEncryptionPlugin encrypt;
    encrypt.encrypt( "pub.pem", dataToEncrypt, "test.exml" );
    encrypt.decrypt( "test.exml", dataDecrypted );
    
    // compare two strings
    EXPECT_STREQ(dataToEncrypt.c_str(),dataDecrypted.c_str());
}

/*
 * Test for encrypting, decrypting and comparing the contents with large size of content
 * 1- read test.xml file into string
 * 2- add up the string by 100 times
 * 3- encrypt the string and save to testLarge.exml file
 * 4- decrypt testLarge.exml file and save as string
 * 5- compare the contents
 */
TEST(VtdEncryptionTest, encryptDecryptLarge)
{
    std::string dataToEncrypt;
    std::string dataToEncryptLarge;
    std::string dataDecryptedLarge;
    std::ifstream input("test.xml");
    getline (input, dataToEncrypt, (char) input.eof());
    for (int i = 0; i < 100; i++ ) dataToEncryptLarge += dataToEncrypt;

    ExampleVtdEncryptionPlugin encrypt;
    encrypt.encrypt( "pub.pem", dataToEncryptLarge, "testLarge.exml" );
    encrypt.decrypt( "testLarge.exml", dataDecryptedLarge );
    
    // compare two strings
    EXPECT_STREQ(dataToEncryptLarge.c_str(),dataDecryptedLarge.c_str());
}
 

/*
 * Test for encrypting, decrypting and comparing the contents with small size of content
 * 1- read demo.html file into string
 * 2- encrypt the string and save to vector data
 * 3- save vector data into demo.ehtml
 * 3- decrypt demo.ehtml and save as string
 * 4- compare the contents
 */
TEST(VtdEncryptionTest, encryptContentSmall)
{
    std::string toEnc;
    std::string decrypted;
    std::ifstream input("demo.html");
    getline (input, toEnc, (char) input.eof());

    ExampleVtdEncryptionPlugin encrypt;
    std::vector<char> toDec;
    encrypt.encryptContent( "pub.pem", toEnc, toDec );
    std::ofstream output("data.ehtml", std::ios::out | std::ios::binary);
    output.write((char*)&toDec[0], toDec.size() * sizeof(char));
    output.close();
    encrypt.decrypt( "demo.ehtml", decrypted );
    
    // compare two strings
    EXPECT_STREQ(toEnc.c_str(),decrypted.c_str());
}

/*
 * Test for encrypting, decrypting and comparing the contents with medium size of content
 * 1- read test.xml file into string
 * 2- encrypt the string and save to vector data
 * 3- save vector data into test.exml
 * 3- decrypt test.exml and save as string
 * 4- compare the contents
 */
TEST(VtdEncryptionTest, encryptContentMedium)
{
    std::string toEnc;
    std::string decrypted;
    std::ifstream input("test.xml");
    getline (input, toEnc, (char) input.eof());

    ExampleVtdEncryptionPlugin encrypt;
    std::vector<char> toDec;
    encrypt.encryptContent( "pub.pem", toEnc, toDec );
    std::ofstream output("test.exml", std::ios::out | std::ios::binary);
    output.write((char*)&toDec[0], toDec.size() * sizeof(char));
    output.close();
    encrypt.decrypt( "test.exml", decrypted );
    
    // compare two strings
    EXPECT_STREQ(toEnc.c_str(),decrypted.c_str());
}

/*
 * Test for encrypting, decrypting and comparing the contents with large size of content
 * 1- read test.xml file into string
 * 2- add up the string by 100 times
 * 3- encrypt the string and save to vector data
 * 4- save vector data into testLarge.exml
 * 5- decrypt testLarge.exml and save as string
 * 6- compare the contents
 */
TEST(VtdEncryptionTest, encryptContentLarge)
{
    std::string toEnc, toEncLarge;
    std::string decrypted;
    std::ifstream input("test.xml");
    getline (input, toEnc, (char) input.eof());
    for (int i = 0; i < 100; i++ ) toEncLarge += toEnc;

    ExampleVtdEncryptionPlugin encrypt;
    std::vector<char> toDec;
    encrypt.encryptContent( "pub.pem", toEncLarge, toDec );
    std::ofstream output("testLarge.exml", std::ios::out | std::ios::binary);
    output.write((char*)&toDec[0], toDec.size() * sizeof(char));
    output.close();
    encrypt.decrypt( "testLarge.exml", decrypted );
    

    // compare two strings
    EXPECT_STREQ(toEncLarge.c_str(),decrypted.c_str());
}

/*
 * Test for encrypting, decrypting and comparing the contents with small size of content
 * 1- read test.xml into string
 * 2- encrypt demo.html and save into demo.ehtml file
 * 3- read demo.ehtml as vector data
 * 4- decrypt vector data and save as string
 * 5- compare the contents
 */
TEST(VtdEncryptionTest, decryptContentSmall)
{
    std::string toEnc;
    std::string decrypted;
    std::ifstream input("demo.html");
    getline (input, toEnc, (char) input.eof());

    ExampleVtdEncryptionPlugin encrypt;
    encrypt.encryptFile( "pub.pem", "demo.html", "demo.ehtml" );
    std::ifstream encFile("demo.ehtml");
    std::vector<char> toDec = std::vector<char>(std::istreambuf_iterator<char>(encFile), std::istreambuf_iterator<char>());
    encrypt.decryptContent( toDec, decrypted );

    // compare two strings
    EXPECT_STREQ(toEnc.c_str(),decrypted.c_str());
}

/*
 * Test for encrypting, decrypting and comparing the contents with medium size of content
 * 1- read test.xml into string
 * 2- encrypt test.xml and save into test.exml file
 * 3- read test.exml as vector data
 * 4- decrypt vector data and save as string
 * 5- compare the contents
 */
TEST(VtdEncryptionTest, decryptContentMedium)
{
    std::string toEnc;
    std::string decrypted;
    std::ifstream input("test.xml");
    getline (input, toEnc, (char) input.eof());

    ExampleVtdEncryptionPlugin encrypt;
    encrypt.encryptFile( "pub.pem", "test.xml", "test.exml" );
    std::ifstream encFile("test.exml");
    std::vector<char> toDec = std::vector<char>(std::istreambuf_iterator<char>(encFile), std::istreambuf_iterator<char>());
    encrypt.decryptContent( toDec, decrypted );

    // compare two strings
    EXPECT_STREQ(toEnc.c_str(),decrypted.c_str());
}
 
/*
 * Test for encrypting, decrypting and comparing the contents with large size of content
 * 1- read test.xml file into string
 * 2- add up the string by 100 times and save into testLarge.xml
 * 3- encrypt testLarge.xml and save into testLarge.exml file
 * 4- read testLarge.exml as vector data
 * 5- decrypt vector data and save as string
 * 6- compare the contents
 */
TEST(VtdEncryptionTest, decryptContentLarge)
{
    std::string toEnc;
    std::string toEncLarge;
    std::ifstream input("test.xml");
    getline (input, toEnc, (char) input.eof());
    for (int i = 0; i < 100; i++ ) toEncLarge += toEnc;
    std::ofstream output;
    output.open("testLarge.xml");
    output << toEncLarge;
    output.close();

    ExampleVtdEncryptionPlugin encrypt;
    encrypt.encryptFile( "pub.pem", "testLarge.xml", "testLarge.exml" );
    std::ifstream encLarge("testLarge.exml");
    std::vector<char> toDec = std::vector<char>(std::istreambuf_iterator<char>(encLarge), std::istreambuf_iterator<char>());
    std::string decLarge;
    encrypt.decryptContent( toDec, decLarge );
    
    // compare two strings
    EXPECT_STREQ(toEncLarge.c_str(),decLarge.c_str());
}


/*
 * Test for encrypting, decrypting and comparing the contents with small size of content
 * 1- save demo.html file into string
 * 2- encrypt the string and save into vector data
 * 3- decrypt vector data and save into string
 * 4- compare the contents
 */
TEST(VtdEncryptionTest, encryptDecryptContentSmall)
{
    // read the input file and save the whole file into string
    std::string dataToEncrypt;
    std::string dataDecrypted;
    std::string dataDecrypted1;
    std::ifstream input("demo.html");
    getline (input, dataToEncrypt, (char) input.eof());

    ExampleVtdEncryptionPlugin encrypt;
    std::vector<char> dataEncrypted;
    encrypt.encryptContent( "pub.pem", dataToEncrypt, dataEncrypted );
    encrypt.decryptContent( dataEncrypted, dataDecrypted );
    
    // compare two strings
    EXPECT_STREQ(dataToEncrypt.c_str(),dataDecrypted.c_str());
}



/*
 * Test for encrypting, decrypting and comparing the contents with medium size of content
 * 1- save test.xml file into string
 * 2- encrypt the string and save into vector data
 * 3- decrypt vector data and save into string
 * 4- compare the contents
 */
TEST(VtdEncryptionTest, encryptDecryptContentMedium)
{
    std::string dataToEncrypt;
    std::string dataDecrypted;
    std::string dataDecrypted1;
    std::ifstream input("test.xml");
    getline (input, dataToEncrypt, (char) input.eof());

    ExampleVtdEncryptionPlugin encrypt;
    std::vector<char> dataEncrypted;
    encrypt.encryptContent( "pub.pem", dataToEncrypt, dataEncrypted );
    encrypt.decryptContent( dataEncrypted, dataDecrypted );
    
    // compare two strings
    EXPECT_STREQ(dataToEncrypt.c_str(),dataDecrypted.c_str());
}

/*
 * Test for encrypting, decrypting and comparing the contents with large size of content
 * 1- save test.xml file into string
 * 2- add up the string by 100 times
 * 3- encrypt the string and save into vector data
 * 4- decrypt vector data and save into string
 * 5- compare the contents
 */
TEST(VtdEncryptionTest, encryptDecryptContentLarge)
{
    std::string dataToEncrypt;
    std::string dataToEncryptLarge;
    std::string dataDecryptedLarge;
    std::ifstream input("test.xml");
    getline (input, dataToEncrypt, (char) input.eof());
    for (int i = 0; i < 100; i++ ) dataToEncryptLarge += dataToEncrypt;

    ExampleVtdEncryptionPlugin encrypt;
    std::vector<char> dataEncryptedLarge;
    encrypt.encryptContent( "pub.pem", dataToEncryptLarge, dataEncryptedLarge );
    encrypt.decryptContent( dataEncryptedLarge, dataDecryptedLarge );
    
    // compare two strings
    EXPECT_STREQ(dataToEncryptLarge.c_str(),dataDecryptedLarge.c_str());
}



int main(int argc, char** argv) {

  ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

