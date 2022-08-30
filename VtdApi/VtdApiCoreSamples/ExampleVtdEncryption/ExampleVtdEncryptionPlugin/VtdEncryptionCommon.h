#ifndef VTDENCRYPTIONCOMMON_H
#define VTDENCRYPTIONCOMMON_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <arpa/inet.h>
#include <boost/cast.hpp>

#include <VtdCore/Logging/Log.h>

namespace ExampleVtdEncryption{
    class EvpKey {
    public:
        EvpKey() 
            : pkey_(EVP_PKEY_new()) 
        { }

        ~EvpKey() {
            if(pkey_) {
                EVP_PKEY_free(pkey_);
                pkey_ = NULL;
            }
        }

        EVP_PKEY* getPKey() { return pkey_; }
    private:
        EVP_PKEY* pkey_;
    };

    class EvpCipherCtx {
    public:
        EvpCipherCtx() 
            : ctx_(EVP_CIPHER_CTX_new()) 
        { }

        ~EvpCipherCtx() {
            if(ctx_) {
                EVP_CIPHER_CTX_free(ctx_);
                ctx_ = NULL;
            }
        }

        EVP_CIPHER_CTX* getCipherCtx() { return ctx_; }
    private:
        EVP_CIPHER_CTX* ctx_;
    };

    // Class for unsigned char array pointer
    class Buffer {
    public:
        Buffer(size_t size)
            : charArray_(new unsigned char[size]) 
        { }

        ~Buffer() {
            delete[] charArray_; 
            charArray_ = NULL;
        }

        unsigned char* getBuffer() { return charArray_; }
    private:
        unsigned char* charArray_;
    };




} // namespace ExampleVtdEncryption

bool getEvpFromPrivateKey(const char* privateKey, EVP_PKEY* evpPkeyStructure)
{
    BIO *mem = BIO_new_mem_buf(const_cast<char*>(privateKey), -1);
    RSA *rsa = PEM_read_bio_RSAPrivateKey(mem, NULL, NULL, NULL );
    BIO_free( mem );
    if (!EVP_PKEY_assign_RSA(evpPkeyStructure, rsa))
    {
        VTD_LOG_ERR("EVP_PKEY_assign_RSA function failed.");
        ERR_print_errors_fp(stderr);
        return false;
    }
    return true;
}

bool getEvpFromPublicKey(std::string publicKeyFile, EVP_PKEY* evpPkeyStructure)
{
    FILE *rsaPubkeyFile = fopen(publicKeyFile.c_str(), "rb");
    if ( !rsaPubkeyFile )
    {
        VTD_LOG_ERR("Error opening RSA public key file. <"+ publicKeyFile+">");
        return false;
    }
    RSA *rsaPkey = NULL;
    // Reads public key from rsaPubkeyFile to rsaPkey 
    if ( !PEM_read_RSA_PUBKEY(rsaPubkeyFile, &rsaPkey, NULL, NULL) )
    {
        VTD_LOG_ERR("Error loading RSA public key file. <"+ publicKeyFile+">");
        ERR_print_errors_fp(stderr);
        fclose(rsaPubkeyFile);
        return false;
    }
    fclose(rsaPubkeyFile);

    // Assigns the RSA key to EVP Pkey Structure
    if ( !EVP_PKEY_assign_RSA(evpPkeyStructure, rsaPkey) )
    {
        VTD_LOG_ERR("EVP_PKEY_assign_RSA function failed.");
        ERR_print_errors_fp(stderr);
        return false;
    }

    return true;
}

bool getEVPCipherCtx(EVP_CIPHER_CTX* evpCipherContext, EVP_PKEY* evpPkeyStructure, std::ofstream& outFileStream)
{
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

    // The key buffer size, key buffer and initializationVector are written into the output file
    unsigned int keyBufferNetworkSize = htonl(keyBufferSize);
    outFileStream.write(reinterpret_cast<char*>(&keyBufferNetworkSize),sizeof(unsigned int));

    outFileStream.write(reinterpret_cast<char*>(&keyBuffer[0]),keyBufferSize);

    outFileStream.write(reinterpret_cast<char*>(initializationVector),EVP_CIPHER_iv_length(EVP_aes_128_cbc()));
    return true;
}

bool getEVPCipherCtx(EVP_CIPHER_CTX* evpCipherContext, EVP_PKEY* evpPkeyStructure, std::ifstream& inFileStream)
{
    // Fetch the key buffer size
    unsigned int keyBufferNetworkSize;
    inFileStream.read(reinterpret_cast<char*>(&keyBufferNetworkSize),sizeof(unsigned int));

    unsigned int keyBufferSize = ntohl(keyBufferNetworkSize);
    if (keyBufferSize > boost::numeric_cast<unsigned int>(EVP_PKEY_size(evpPkeyStructure)))
    {
        VTD_LOG_ERR("Bad encrypted key length.");
        return false;
    }

    ExampleVtdEncryption::Buffer keyBufferPointer(EVP_PKEY_size(evpPkeyStructure));
    unsigned char *keyBuffer = keyBufferPointer.getBuffer();
    // Fetch the key buffer
    inFileStream.read(reinterpret_cast<char*>(&keyBuffer[0]),keyBufferSize);

    // Fetch the initializationVector
    unsigned char initializationVector[EVP_MAX_IV_LENGTH];
    inFileStream.read(reinterpret_cast<char*>(initializationVector),EVP_MAX_IV_LENGTH);

    if (!EVP_OpenInit(evpCipherContext, EVP_aes_128_cbc(), keyBuffer, keyBufferSize, initializationVector, evpPkeyStructure))
    {
        VTD_LOG_ERR("EVP_OpenInit function failed.");
        ERR_print_errors_fp(stderr);
        return false;
    }

    return true;
}

/**
 * return and pop the last element of vector
 * @param vec input vector
 * @returns the last element of the input vector  
 **/
template<typename T>
T returnAndPopBack(std::vector<T>& vec)
{
    assert(!vec.empty());
    T returnValue =vec.back();
    vec.pop_back();
    return returnValue;
}

#endif // VTDENCRYPTIONCOMMON_H
