#include "ExampleVtdEncryptionPlugin.h"

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <arpa/inet.h>
#include <boost/cast.hpp>

#include "VtdEncryptionCommon.h"
#include <VtdCore/Logging/Log.h>

namespace {
    //RSA Private key
    const char pem[] ="-----BEGIN PRIVATE KEY-----\nMIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQDCmMJo3nvluDQw\n3cc6dYoLt0P7M0v/BID1mz74rwTYIrNNAdYyK8uY0goZsQdRheEZmnlCRU8uv81z\nOkYNOcFCZRmHehjXXyIGPXko//uHw97iXrjlZmh6p5IO58EejZGadVzhwkHnQP8f\n32LKqWJE7rs0vQWU2LMtmOjnHed8zFZoawZpky3vRoPNkUShT+8UzM69riS/Ke3+\nTrQRPI8VQc0liuP/JvNFGuQydwkBKfpqe6dLB1T5RNxFjpg83o/5V2m0Mlt8ixHK\nQmGZdP2GN/+VsFsCmGD4CiY8Wyci2tJ2MzJ5SyBQ89ONIa34sBOU7RYVOsM23gaD\nLmCg5GN/AgMBAAECggEAWwvsEfLelzmbOa3aVDDAWQDzDqoOiY/K4p8zVFlW8+Uw\nbPxKAolZJfRIA4M/gFYaXsdWqroQ9TeKYbpHIlL+aBkzW5611rbNDYxfjt5OClSL\niPB2o+ZJRfH3NYAbbDcig9kbjwk7mn5fn8L9zwJ3Vvc3odI6tUy6cMAVYGUudMW4\n9JgwCOE+2SXymEFtlSzRB/gV3vok5XgGVkyfVXJFs3Hwy/NkBbBGnEoGqwGXscMb\nXyEX45WzAuwvWYElsvms/i6jX5nQJ662Uv3kmD7F3kwL66FUn94qYKP2vLBJfqeF\nCGWTlq93qyvKRxrdbqqARssDottVQQ9bourPlMPUsQKBgQDtz7jYZ4pjNsxDW6GM\nmZgtSBipjGfiJfxwgW+x/XnDYCbKpHdU1g2qVB1nGeZJrIWySZjJz6uRlNd1K3lf\nZDjj/UdULXo92qDYXuRyRH8TjWBVFNGhNtVYMcyTELXbdEm41ebjckkz1zprkIAb\n5rRe9iBhd6l1dbVx1acsjaZGOQKBgQDReuf9sVcyrUiR7Yph1xdGMnMozHQ0bN8D\nSquEAELoPv9oE7BEUi5L4j/Lncs1Vpr4wRRdfR153gsElp4/5mcjrtKU/n1oquY9\n6d3TXLat05c4OjY6SF6rx0gB/MIsNRMYCmPNawSCSA2iPMpolr8tUz2HKEALL6Im\nibD1x5+3dwKBgQCeQ5KRun6Xvp076pxdtM5YvFVlaMKt93fD6/BItRc21iOa0s9z\nzyyzAV28ArmGqGEloOMk06crsLGfEbqpqEpQOHwi4k0rIvfOZ4CDJ2Cmw3yrwros\nHxDmq+WorgNJNF/nubr5/VIIRSFk+nq3ltbNJ+Gu2/MT7608P+MMvIw+yQKBgQCt\nQkexF8W0X4hfUiYbqGhSohWHkBso5UdLFK5pvkGYj8p1jZtD1uj90ILNaZSSaDBD\nQIcUkBAaJOHeCKmY1ntGEymPHDIjqP5IBS94yv05JoGzesoxSHws/eV750++eqNx\nRd6oHzSagPft0PPkr5It7eQ87riRx/MIhuf7UQG0HwKBgQC7+CmyI991CwWrwR1M\nIgp+nlymACDofUEhYEIhsVWVyGYrLuD1kr99JqT7KEfwPAZRNPEpeAxtC/OLwbPj\nomj+AmQk8pxdX0miouA94Hn8+eai92EdoDvLRpNQfH/WWBJniWH3xtL1nWX0btSI\naZQnfZHIvqaZa+4xOOrwHOeRNA==\n-----END PRIVATE KEY-----";
    const size_t VTD_ENC_KEY_LENGTH = 4096;
}

using namespace VTD;

bool 
ExampleVtdEncryptionPlugin::encrypt(const std::string& publicKeyFile, const std::string& inputContent, const std::string& outputFile)
{
    if ( inputContent.empty() )
    {
        VTD_LOG_ERR(" Input content is empty. ");
        return false;
    }

    std::ofstream outFileStream(outputFile.c_str());
    if ( !outFileStream )
    {
        VTD_LOG_ERR(std::strerror(errno) <<" <"+ outputFile+">");
        return false;
    }

    ExampleVtdEncryption::EvpKey evpKey;
    EVP_PKEY *evpPkeyStructure = evpKey.getPKey();
    if ( !getEvpFromPublicKey(publicKeyFile, evpPkeyStructure ) )
    {
        return false;
    }

    ExampleVtdEncryption::EvpCipherCtx evpCipherCtx;
    EVP_CIPHER_CTX * evpCipherContext = evpCipherCtx.getCipherCtx();
    if ( !getEVPCipherCtx(evpCipherContext, evpPkeyStructure, outFileStream) )
    {
        return false;
    }

    // The encrypted data is now written into the output files
    unsigned char buffer[VTD_ENC_KEY_LENGTH];
    unsigned char bufferOut[VTD_ENC_KEY_LENGTH + EVP_MAX_IV_LENGTH];
    int writeLength;
    std::string tmpContent = inputContent; // save the copy of the inputContent
    size_t readLength = tmpContent.size() < VTD_ENC_KEY_LENGTH ? tmpContent.size() : VTD_ENC_KEY_LENGTH;
    while ( memcpy(buffer, tmpContent.c_str(), readLength) )
    {
        if (!EVP_SealUpdate(evpCipherContext, bufferOut, &writeLength, buffer, readLength))
        {
            VTD_LOG_ERR("EVP_SealUpdate function failed.");
            ERR_print_errors_fp(stderr);
            return false;
        }

        outFileStream.write(reinterpret_cast<char*>(bufferOut),writeLength);

        if ( tmpContent.size() < VTD_ENC_KEY_LENGTH ) break;
        tmpContent = tmpContent.substr(VTD_ENC_KEY_LENGTH, tmpContent.size()-VTD_ENC_KEY_LENGTH);
        readLength = tmpContent.size() < VTD_ENC_KEY_LENGTH ? tmpContent.size() : VTD_ENC_KEY_LENGTH;
    }
    
    if (!EVP_SealFinal(evpCipherContext, bufferOut, &writeLength))
    {
        VTD_LOG_ERR("EVP_SealFinal function failed.");
        ERR_print_errors_fp(stderr);
        return false;
    }

    outFileStream.write(reinterpret_cast<char*>(bufferOut),writeLength);
    return true;
}

bool 
ExampleVtdEncryptionPlugin::encryptFile(const std::string& publicKeyFile, const std::string& inputFile, const std::string& outputFile)
{
    std::ifstream inFileStream(inputFile.c_str());
    if ( !inFileStream )
    {
        VTD_LOG_ERR(std::strerror(errno) <<" <"+ inputFile+">");
        return false;
    }

    std::ofstream outFileStream(outputFile.c_str());
    if ( !outFileStream )
    {
        VTD_LOG_ERR(std::strerror(errno) <<" <"+ outputFile+">");
        return false;
    }

    ExampleVtdEncryption::EvpKey evpKey;
    EVP_PKEY *evpPkeyStructure = evpKey.getPKey();
    if ( !getEvpFromPublicKey(publicKeyFile, evpPkeyStructure ) )
        return false;

    ExampleVtdEncryption::EvpCipherCtx evpCipherCtx;
    EVP_CIPHER_CTX * evpCipherContext = evpCipherCtx.getCipherCtx();
    if ( !getEVPCipherCtx(evpCipherContext, evpPkeyStructure, outFileStream) )
        return false;

    size_t readLength;
    int writeLength;
    unsigned char buffer[VTD_ENC_KEY_LENGTH];
    unsigned char bufferOut[VTD_ENC_KEY_LENGTH + EVP_MAX_IV_LENGTH];
    inFileStream.read(reinterpret_cast<char*>(buffer),VTD_ENC_KEY_LENGTH);
    while ( (readLength = inFileStream.gcount()) > 0 )
    {
        if (!EVP_SealUpdate(evpCipherContext, bufferOut, &writeLength, buffer, readLength))
        {
            VTD_LOG_ERR("EVP_SealUpdate function failed.");
            ERR_print_errors_fp(stderr);
            return false;
        }

        outFileStream.write(reinterpret_cast<char*>(bufferOut),writeLength);
        // Read the next buffer
        inFileStream.read(reinterpret_cast<char*>(buffer),VTD_ENC_KEY_LENGTH);
    }

    if (!EVP_SealFinal(evpCipherContext, bufferOut, &writeLength))
    {
        VTD_LOG_ERR("EVP_SealFinal function failed.");
        ERR_print_errors_fp(stderr);
        return false;
    }

    outFileStream.write(reinterpret_cast<char*>(bufferOut),writeLength);
    return true;
}

bool 
ExampleVtdEncryptionPlugin::encryptContent(const std::string& publicKeyFile, const std::string& inputContent, std::vector<char>& outputContent)
{
    if ( inputContent.empty() )
    {
        VTD_LOG_ERR("Input content is empty. ");
        return false;
    }

    ExampleVtdEncryption::EvpKey evpKey;
    EVP_PKEY *evpPkeyStructure = evpKey.getPKey();
    if ( !getEvpFromPublicKey(publicKeyFile, evpPkeyStructure ) )
        return false;

    ExampleVtdEncryption::EvpCipherCtx evpCipherCtx;
    EVP_CIPHER_CTX * evpCipherContext = evpCipherCtx.getCipherCtx();
    ExampleVtdEncryption::Buffer keyBufferPointer(EVP_PKEY_size(evpPkeyStructure));
    unsigned char *keyBuffer = keyBufferPointer.getBuffer();
    int keyBufferSize;
    unsigned char initializationVector[EVP_MAX_IV_LENGTH];
    if (!EVP_SealInit(evpCipherContext, EVP_aes_128_cbc(), &keyBuffer, &keyBufferSize, initializationVector, &evpPkeyStructure, 1))
    {
        VTD_LOG_ERR("EVP_SealInit function failed.");
        ERR_print_errors_fp(stderr);
        return false;
    }
    
    // Write out the key buffer size
    unsigned int keyBufferNetworkSize = htonl(keyBufferSize);
    outputContent.insert(outputContent.end(), reinterpret_cast<char*>(&keyBufferNetworkSize), reinterpret_cast<char*>(&keyBufferNetworkSize)+sizeof(unsigned int));

    // Write out the key buffer
    outputContent.insert(outputContent.end(), &keyBuffer[0], &keyBuffer[0]+keyBufferSize);

    // Write out the initializationVector
    int ivLength = EVP_CIPHER_iv_length(EVP_aes_128_cbc());
    outputContent.insert(outputContent.end(), &initializationVector[0], &initializationVector[0]+ivLength);

    // The encrypted data is now written into the output files
    unsigned char buffer[VTD_ENC_KEY_LENGTH];
    unsigned char bufferOut[VTD_ENC_KEY_LENGTH + EVP_MAX_IV_LENGTH];
    int writeLength;
    std::string tmpContent = inputContent;
    size_t readLength = tmpContent.size() < VTD_ENC_KEY_LENGTH ? tmpContent.size() : VTD_ENC_KEY_LENGTH;
    while ( memcpy(buffer, tmpContent.c_str(), readLength) )
    {
        if (!EVP_SealUpdate(evpCipherContext, bufferOut, &writeLength, buffer, readLength))
        {
            VTD_LOG_ERR("EVP_SealUpdate function failed.");
            return false;
        }

        outputContent.insert(outputContent.end(),&bufferOut[0], &bufferOut[0]+writeLength);

        if ( tmpContent.size() < VTD_ENC_KEY_LENGTH ) break;
        tmpContent = tmpContent.substr(VTD_ENC_KEY_LENGTH, tmpContent.size()-VTD_ENC_KEY_LENGTH);
        readLength = tmpContent.size() < VTD_ENC_KEY_LENGTH ? tmpContent.size() : VTD_ENC_KEY_LENGTH;
    }
    
    if (!EVP_SealFinal(evpCipherContext, bufferOut, &writeLength))
    {
        VTD_LOG_ERR("EVP_SealFinal function failed.");
        return false;
    }

    outputContent.insert(outputContent.end(),&bufferOut[0], &bufferOut[0]+writeLength);
    return true;
}

bool 
ExampleVtdEncryptionPlugin::decrypt(const std::string& inputFile, std::string& outputContent)
{
    std::ifstream inFileStream(inputFile.c_str());
    if ( !inFileStream )
    {
        VTD_LOG_ERR(std::strerror(errno) <<" <"+ inputFile+">");
        return false;
    }

    ExampleVtdEncryption::EvpKey evpKey;
    EVP_PKEY *evpPkeyStructure = evpKey.getPKey();
    if ( !getEvpFromPrivateKey(pem, evpPkeyStructure) )
        return false;

    ExampleVtdEncryption::EvpCipherCtx evpCipherCtx;
    EVP_CIPHER_CTX *evpCipherContext = evpCipherCtx.getCipherCtx();
    if ( !getEVPCipherCtx(evpCipherContext, evpPkeyStructure, inFileStream) )
        return false;

    size_t readLength;
    int writeLength;
    unsigned char buffer[VTD_ENC_KEY_LENGTH];
    unsigned char bufferOut[VTD_ENC_KEY_LENGTH + EVP_MAX_IV_LENGTH];
    inFileStream.read(reinterpret_cast<char*>(buffer),VTD_ENC_KEY_LENGTH);
    while ( (readLength = inFileStream.gcount()) > 0 )
    {
        if (!EVP_OpenUpdate(evpCipherContext, bufferOut, &writeLength, buffer, readLength))
        {
            VTD_LOG_ERR("EVP_OpenUpdate function failed.");
            ERR_print_errors_fp(stderr);
            return false;
        }

        outputContent.insert(outputContent.end(),&bufferOut[0], &bufferOut[0]+writeLength);
        // Read the next buffer
        inFileStream.read(reinterpret_cast<char*>(buffer),VTD_ENC_KEY_LENGTH);
    }

    if (!EVP_OpenFinal(evpCipherContext, bufferOut, &writeLength))
    {
        VTD_LOG_ERR("EVP_OpenFinal function failed.");
        ERR_print_errors_fp(stderr);
        return false;
    }

    outputContent.insert(outputContent.end(),&bufferOut[0], &bufferOut[0]+writeLength);
    return true;
}

bool 
ExampleVtdEncryptionPlugin::decryptFile(const std::string& inputFile, const std::string& outputFile)
{
    std::ifstream inFileStream(inputFile.c_str());
    if ( !inFileStream )
    {
        VTD_LOG_ERR(std::strerror(errno) <<" <"+ inputFile+">");
        return false;
    }

    std::ofstream outFileStream(outputFile.c_str());
    if ( !outFileStream )
    {
        VTD_LOG_ERR(std::strerror(errno) <<" <"+ outputFile+">");
        return false;
    }

    ExampleVtdEncryption::EvpKey evpKey;
    EVP_PKEY *evpPkeyStructure = evpKey.getPKey();
    if ( !getEvpFromPrivateKey(pem, evpPkeyStructure) )
        return false;

    ExampleVtdEncryption::EvpCipherCtx evpCipherCtx;
    EVP_CIPHER_CTX *evpCipherContext = evpCipherCtx.getCipherCtx();
    if ( !getEVPCipherCtx(evpCipherContext, evpPkeyStructure, inFileStream) )
        return false;

    size_t readLength;
    int writeLength;
    unsigned char buffer[VTD_ENC_KEY_LENGTH];
    unsigned char bufferOut[VTD_ENC_KEY_LENGTH + EVP_MAX_IV_LENGTH];
    inFileStream.read(reinterpret_cast<char*>(buffer),VTD_ENC_KEY_LENGTH);
    while ( (readLength = inFileStream.gcount()) > 0 )
    {
        if (!EVP_OpenUpdate(evpCipherContext, bufferOut, &writeLength, buffer, readLength))
        {
            VTD_LOG_ERR("EVP_OpenUpdate function failed.");
            ERR_print_errors_fp(stderr);
            return false;
        }

        outFileStream.write(reinterpret_cast<char*>(bufferOut),writeLength);
        // Read the next buffer
        inFileStream.read(reinterpret_cast<char*>(buffer),VTD_ENC_KEY_LENGTH);
    }

    if (!EVP_OpenFinal(evpCipherContext, bufferOut, &writeLength))
    {
        VTD_LOG_ERR("EVP_OpenFinal function failed.");
        ERR_print_errors_fp(stderr);
        return false;
    }

    outFileStream.write(reinterpret_cast<char*>(bufferOut),writeLength);
    return true;
}

bool 
ExampleVtdEncryptionPlugin::decryptContent(const std::vector<char>&  inputContent, std::string& outputContent)
{
    if ( inputContent.empty() )
    {
        VTD_LOG_ERR(" Input content is empty. ");
        return false;
    }

    ExampleVtdEncryption::EvpKey evpKey;
    EVP_PKEY *evpPkeyStructure = evpKey.getPKey();
    if ( !getEvpFromPrivateKey(pem, evpPkeyStructure) )
    {
        return false;
    }

    std::vector<char> tmpContent = inputContent;
    std::reverse(tmpContent.begin(),tmpContent.end()); // reverse the vector in order to read from the back(returnAndPopBack)
    
    // Fetch the key buffer size
    char keyBufferSizeChar[ sizeof(unsigned int) ];
    for ( int i = 0; i < sizeof(unsigned int); i++ )
        keyBufferSizeChar[i] = returnAndPopBack( tmpContent );
    
    unsigned int keyBufferNetworkSize;
    if ( !memcpy( &keyBufferNetworkSize, keyBufferSizeChar, sizeof(keyBufferNetworkSize) ) )
    {
        VTD_LOG_ERR("Could not read keyBufferNetworkSize ");
        return false;
    }
    unsigned int keyBufferSize = ntohl(keyBufferNetworkSize);
    if (keyBufferSize > boost::numeric_cast<unsigned int>(EVP_PKEY_size(evpPkeyStructure)))
    {
        VTD_LOG_ERR("Bad encrypted key length.");
        return false;
    }
    
    // Fetch the key buffer
    ExampleVtdEncryption::Buffer keyBufferPointer(keyBufferSize);
    unsigned char *keyBuffer = keyBufferPointer.getBuffer();
    for (int i = 0; i < keyBufferSize; i++) 
        keyBuffer[i] = returnAndPopBack(tmpContent);

    // Fetch the initializationVector 
    unsigned char initializationVector[EVP_MAX_IV_LENGTH];
    for (int i = 0; i < EVP_MAX_IV_LENGTH; i++)
        initializationVector[i] = returnAndPopBack(tmpContent);  
    
    ExampleVtdEncryption::EvpCipherCtx evpCipherCtx;
    EVP_CIPHER_CTX *evpCipherContext = evpCipherCtx.getCipherCtx();
    if (!EVP_OpenInit(evpCipherContext, EVP_aes_128_cbc(), keyBuffer, keyBufferSize, initializationVector, evpPkeyStructure))
    {
        VTD_LOG_ERR("EVP_OpenInit function failed.\n");
        ERR_print_errors_fp(stderr);
        return false;
    }
    
    int writeLength;
    unsigned char buffer[VTD_ENC_KEY_LENGTH];
    unsigned char bufferOut[VTD_ENC_KEY_LENGTH + EVP_MAX_IV_LENGTH];
    unsigned char tmpBuffer[VTD_ENC_KEY_LENGTH];
    size_t readLength = tmpContent.size() < VTD_ENC_KEY_LENGTH ? tmpContent.size() : VTD_ENC_KEY_LENGTH;
    for (int i = 0; i < readLength; i++) tmpBuffer[i] = returnAndPopBack(tmpContent);
    while ( memcpy(buffer, tmpBuffer, readLength) )
    {
        if (!EVP_OpenUpdate(evpCipherContext, bufferOut, &writeLength, buffer, readLength))
        {
            VTD_LOG_ERR("EVP_SealUpdate function failed.");
            ERR_print_errors_fp(stderr);
            return false;
        }

        outputContent.insert(outputContent.end(),&bufferOut[0], &bufferOut[0]+writeLength);

        if ( tmpContent.empty() ) break;
        readLength = tmpContent.size() < VTD_ENC_KEY_LENGTH ? tmpContent.size() : VTD_ENC_KEY_LENGTH;
        for (int i = 0; i < readLength; i++) tmpBuffer[i] = returnAndPopBack(tmpContent);        
    }
    
    if (!EVP_OpenFinal(evpCipherContext, bufferOut, &writeLength)) 
    {
        VTD_LOG_ERR("EVP_OpenFinal function failed.");
        ERR_print_errors_fp(stderr);
        return false;
    }
    
    outputContent.insert(outputContent.end(),&bufferOut[0], &bufferOut[0]+writeLength);
    return true;
}

// Factory function for creating ExampleVtdEncryptionPlugin instance from VTD::VtdEncryption pointer
// see VtdEncryption::load function -> dlsym( mDlHandle, "createVtdEncryptionPlugin")
extern "C" VTD::VtdEncryption* createVtdEncryptionPlugin() {
 return new ExampleVtdEncryptionPlugin;
}
