#ifndef VtdEncryption_MAIN_H
#define VtdEncryption_MAIN_H

#include <VtdCore/Macros.h>
#include <string>
#include <iostream>
#include <vector>

namespace VTD {

/**
 *  VtdEncryption interface class 
 *  load function is implemented to load the VtdEncryption plugin instance
 *  decryptFile and encryptFile functions must be implemented by the plugin which is inherited from this class
 */
 
class VtdEncryption
{

public:

    /**
     * Load and return an instance of a VtdEncryption plugin
     * @param pluginPath the path for the plugin's shared library file
     * @return VtdEncryption plugin instance loaded from the shared library file
     */
    static VtdEncryption* load(const std::string& pluginPath);

    /**
     * Unload the instance of a VtdEncryption plugin
     * @return true if there is nothing to unload or it is unloaded successfully, false if it can not unload(dlclose fails).
     */
    static bool unload();

    /**
     * Check for the file extension for encrypted file
     * @param filename name or path of the file to be encrypted
     * @returns true if success, false if fail
     **/
    static bool checkFileExtension(const std::string& filename);

    virtual bool encrypt(const std::string& publicKeyFile, const std::string& inputContent, const std::string& outputFile) = 0;

    virtual bool encryptFile(const std::string& publicKeyFile, const std::string& inputFile, const std::string& outputFile) = 0;

    virtual bool encryptContent(const std::string& publicKeyFile, const std::string& inputContent, std::vector<char>& outputContent) = 0;

    virtual bool decrypt(const std::string& inputFile, std::string& outputContent) = 0;

    virtual bool decryptFile(const std::string& inputFile, const std::string& outputFile) = 0;

    virtual bool decryptContent(const std::vector<char>&  inputContent, std::string& outputContent) = 0;

protected:
    VtdEncryption() {}
    virtual ~VtdEncryption() {}
    
};

/*  \var typedef VtdEncryption* VtdEncryptionFactoryFunction
 *  \brief A type definition for the create factory function of VtdEncryption.
 */
typedef VtdEncryption* VtdEncryptionFactoryFunction();
/*  \var typedef void* VtdEncryptionFactoryDestroyFunction
 *  \brief A type definition for the destroy factory function of VtdEncryption.
*/
typedef void VtdEncryptionFactoryDestroyFunction(VtdEncryption*); 

} // namespace VTD

#endif // VtdEncryption_MAIN_H


