#ifndef VTDAPI_EXAMPLEVTDENCRYPTIONPLUGIN_H
#define VTDAPI_EXAMPLEVTDENCRYPTIONPLUGIN_H

#include <VtdEncryption/VtdEncryption.h>
#include <string>

class ExampleVtdEncryptionPlugin : public VTD::VtdEncryption
{
public:

    /**
     * Encrypt inputContent using publicKeyFile, result is written to outputFile.
     * @param publicKeyFile public key file
     * @param inputContent input content to be encrypted
     * @param outputFile encrypted output file
     * @returns true if success, false if fail
     **/
    virtual bool encrypt(const std::string& publicKeyFile, const std::string& inputContent, const std::string& outputFile) VTD_OVERRIDE;

    /**
     * Encrypt inputFile using publicKeyFile, result is written to outputFile.
     * @param publicKeyFile public key file
     * @param inputFile input file to be encrypted
     * @param outputFile encrypted output file
     * @returns true if success, false if fail
     **/
    virtual bool encryptFile(const std::string& publicKeyFile, const std::string& inputFile, const std::string& outputFile) VTD_OVERRIDE;

    /**
     * Encrypt inputContent using publicKeyFile, result is written to outputContent.
     * @param publicKeyFile public key file
     * @param inputContent input content to be encrypted
     * @param outputContent encrypted output content
     * @returns true if success, false if fail
     **/
    virtual bool encryptContent(const std::string& publicKeyFile, const std::string& inputContent, std::vector<char>& outputContent) VTD_OVERRIDE;

    /**
     * Decrypt encrypted inputFile and result is written to outputContent.
     * @param inputFile encrypted input file path to be decrypted
     * @param outputContent decrypted output content
     * @returns true if success, false if fail
     **/
    virtual bool decrypt(const std::string& inputFile, std::string& outputContent) VTD_OVERRIDE;

    /**
     * Decrypt encrypted inputFile and result is written to outputFile.
     * @param inputFile encrypted input file path to be decrypted
     * @param outputFile decrypted output file path
     * @returns true if success, false if fail
     **/
    virtual bool decryptFile(const std::string& inputFile, const std::string& outputFile) VTD_OVERRIDE;

    /**
     * Decrypt encrypted inputContent and result is written to outputContent.
     * @param inputContent encrypted input content to be decrypted
     * @param outputContent decrypted output content
     * @returns true if success, false if fail
     **/
    virtual bool decryptContent(const std::vector<char>&  inputContent, std::string& outputContent) VTD_OVERRIDE;

    ExampleVtdEncryptionPlugin() { }
    virtual ~ExampleVtdEncryptionPlugin() { }

};


#endif //VTDAPI_EXAMPLEVTDENCRYPTIONPLUGIN_H
