#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

#include <VtdEncryption/VtdEncryption.h>
#include "ExampleVtdEncryptionPlugin/ExampleVtdEncryptionPlugin.h"

/**
 * VTD Encryption Example.
 */
void printHowToUse();
void unloadAndExit(int status);
void printHowToUseAndExit(int status);

class Mode {
public:
    enum Enum
    {
        ENCRYPT,
        DECRYPT,
        ENCRYPTCONTENT,
        DECRYPTCONTENT,
        ENCRYPTFILE,
        DECRYPTFILE,
        UNKNOWN
    };

    static Enum getMode(const std::string& value)
    {
        if( value == "encrypt" ) return ENCRYPT;
        if( value == "encryptContent" ) return ENCRYPTCONTENT;
        if( value == "encryptFile" ) return ENCRYPTFILE;
        if( value == "decrypt" ) return DECRYPT;
        if( value == "decryptContent" ) return DECRYPTCONTENT;
        if( value == "decryptFile" ) return DECRYPTFILE;
        return UNKNOWN;
    }
};

int main(int argc, char** argv)
{
    char* pubKeyFileName;
    char* inputFileName;
    char* inputContent;
    char* outputFileName;

    VTD::VtdEncryption* encryption;
#if _GLIBCXX_USE_CXX11_ABI
    encryption = static_cast<VTD::VtdEncryption*>(VTD::VtdEncryption::load("./ExampleVtdEncryptionPlugin/libExampleVtdEncryptionPlugin.so.cxx11"));
#else
    encryption = static_cast<VTD::VtdEncryption*>(VTD::VtdEncryption::load("./ExampleVtdEncryptionPlugin/libExampleVtdEncryptionPlugin.so.cxx98"));
#endif
    

    if ( !encryption )
    {
        std::cout << "Loading library failed" << std::endl;
        VTD::VtdEncryption::unload();
        exit(EXIT_FAILURE);
    }

    if ( argc < 3 )
    {
        printHowToUseAndExit(EXIT_FAILURE);
    }

    Mode::Enum mode = Mode::getMode(std::string(argv[1]));

    switch (mode)
    {
        case Mode::ENCRYPTFILE:
        {
            if ( argc != 5 )
                printHowToUseAndExit(EXIT_FAILURE);

            pubKeyFileName = argv[2];
            inputFileName = argv[3];
            outputFileName = argv[4];
            if ( encryption->encryptFile(pubKeyFileName, inputFileName, outputFileName) )
            {
                std::cout << "Successfully encrypted the file and saved to the file..." << std::endl;
            }
            else
            {
                VTD::VtdEncryption::unload();
                exit(EXIT_FAILURE);
            }
        } break;
        case Mode::ENCRYPT:
        {
            if ( argc != 5 )
                printHowToUseAndExit(EXIT_FAILURE);

            pubKeyFileName = argv[2];
            inputContent = argv[3];
            outputFileName = argv[4];
            if ( encryption->encrypt(pubKeyFileName, inputContent, outputFileName) )
            {
                std::cout << "Successfully encrypted the content and saved to the file..." << std::endl;
            }
            else
            {
                VTD::VtdEncryption::unload();
                exit(EXIT_FAILURE);
            }
        } break;
        
        case Mode::ENCRYPTCONTENT:
        {
            if ( argc != 4 )
                printHowToUseAndExit(EXIT_FAILURE);

            pubKeyFileName = argv[2];
            inputContent = argv[3];
            std::vector<char> outputContent;
            if ( encryption->encryptContent(pubKeyFileName, inputContent, outputContent) )
            {
                std::cout << "Successfully encrypted the content and saved to the content..." << std::endl;
            }
            else
            {
                VTD::VtdEncryption::unload();
                exit(EXIT_FAILURE);
            }
        } break;
        
        case Mode::DECRYPTFILE:
        {
            if ( argc != 4 )
                printHowToUseAndExit(EXIT_FAILURE);

            inputFileName = argv[2];
            outputFileName = argv[3];
            if ( !VTD::VtdEncryption::checkFileExtension(inputFileName) )
            {
                VTD::VtdEncryption::unload();
                exit(EXIT_FAILURE);
            }
            if ( encryption->decryptFile(inputFileName, outputFileName) )
            {
                std::cout << "Successfully decrypted the file and saved to the file..." << std::endl;
            }  
            else
            {
                VTD::VtdEncryption::unload();
                exit(EXIT_FAILURE);
            }
        } break;
        case Mode::DECRYPT:
        {
            if ( argc != 3 )
                printHowToUseAndExit(EXIT_FAILURE);

            inputFileName = argv[2];
            std::string outputContent;
            if ( !VTD::VtdEncryption::checkFileExtension(inputFileName) )
            {
                VTD::VtdEncryption::unload();
                exit(EXIT_FAILURE);
            }
            if ( encryption->decrypt(inputFileName, outputContent) )
            {
                std::cout << "Successfully decrypted the file and saved to the content..." << std::endl;
                std::cout << "outputContent: \n" << outputContent << std::endl;
            }
            else
            {
                VTD::VtdEncryption::unload();
                exit(EXIT_FAILURE);
            }
        } break;
        
        case Mode::DECRYPTCONTENT:
        {
            if ( argc != 3 )
                printHowToUseAndExit(EXIT_FAILURE);

            std::vector<char> inputVector;
            inputVector.insert(inputVector.end(),argv[2], argv[2]+sizeof(argv[2]));
            std::string outputContent;
            if ( encryption->decryptContent(inputVector, outputContent) )
            {
                std::cout << "Successfully decrypted the file and saved to the content..." << std::endl;
                std::cout << "outputContent: " << std::endl << outputContent << std::endl;
            }
            else
            {
                VTD::VtdEncryption::unload();
                exit(EXIT_FAILURE);
            }
        } break;
        
        case Mode::UNKNOWN:
        default:
            printHowToUseAndExit(EXIT_FAILURE);
    }
    VTD::VtdEncryption::unload();
    std::cout << "Exiting..." << std::endl;
    return 0;
}

void printHowToUse()
{
    std::cout << "Usage: ExampleVtdEncryption <command> <files...>" << std::endl;
    std::cout << "e.g.: ExampleVtdEncryption encrypt <pubKeyFileName> <inputContent>" << std::endl;
    std::cout << "e.g.: ExampleVtdEncryption encryptFile <pubKeyFileName> <inputFileName> <outputFileName>" << std::endl;
    std::cout << "e.g.: ExampleVtdEncryption encryptContent <pubKeyFileName> <inputContent>" << std::endl;
    std::cout << "e.g.: ExampleVtdEncryption decrypt <inputFileName>" << std::endl;
    std::cout << "e.g.: ExampleVtdEncryption decryptFile <inputFileName> <outputFileName>" << std::endl;
    std::cout << "e.g.: ExampleVtdEncryption decryptContent <inputContent>" << std::endl;
}

void unloadAndExit(int status)
{
    if ( !VTD::VtdEncryption::unload() )
        std::cout << "Unloading shared library handler failed." << std::endl;
    exit(status);  
}

void printHowToUseAndExit(int status)
{
    printHowToUse();
    unloadAndExit(status);
}

