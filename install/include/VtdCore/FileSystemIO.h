#ifndef  _VTD_FRAMEWORK_FILE_SYSTEM_IO_H
#define  _VTD_FRAMEWORK_FILE_SYSTEM_IO_H

#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <string>
#include <vector>
#include <map>
#include <sstream>

namespace VTD {

namespace Internal {

class FileSystemIO
{

public:

    const static unsigned int TURN_ON_TIME_OUT = 10;
    const static unsigned int TURN_OFF_TIME_OUT = 1;
    /**
    *	Constructor
    */
	FileSystemIO();

	/**
	*	Destructor
	*/
	~FileSystemIO();

    /**
     * @brief hex2int - conver hex dec number to int
     * @param x - intiger
     * @param str - hex dec number
     */
    static void hex2int(unsigned int& x, const char* str);

    /**
     * @brief setCurrentPath - change current folder
     * @param folderName - folder path
     * @return
     */
    static bool setCurrentPath(const std::string& folderName);

    /**
     * @brief checkIfFolderExist - check if folder exists
     * @param folderName - folder path
     * @return true if folder has been changed successfully
     */
    static bool checkIfFolderExist(const std::string& folderName, bool verbose = false);

    /**
     * @brief createFolder - create folder
     * @param folderName - folder path
     * @return true if folder exists
     */
    static bool createFolder(const std::string& folderName);

    /**
     * @brief setPermissions - set permission on path
     * @param folderName - folder path
     * @param permission - permissions to be set
     * @param includeContent - set permission to included files and folders
     * @return true if permission has been set
     */
    static bool setPermissions(const std::string& path, boost::filesystem::perms permissions , bool includeContent=false);

    /**
     * @brief getAllFilesInDir - get list of all files in folder
     * @param directory - directory path
     * @param fileExtension - file extension to be read
     * @param fileList - vector of string to be fill with files
     * @return true if successful
     */
    static bool getAllFilesInDir(const std::string& directory, const std::string& fileExtension, std::vector<std::string>& fileList, bool verbose = false);

    /**
     * @brief makeApsolutePathFromeRelative - make aplsolute path from relative path
     * @param filePath - file path
     * @return true if successful
     */
    static bool makeAbsolutePathFromRelative(std::string& filePath);

    /**
     * @brief getFileNameFromPath - from whole path return just file name
     * @param path - whole file path folder + file
     * @return file name
     */
    static std::string getFileNameFromPath(const std::string& path, bool verbose = false);

    /**
     * @brief getItemNameFromPath - get item name from path
     * @param path - path
     * @return item name
     */
    static std::string getItemNameFromPath(const std::string& path);

    /**
     * @brief copyFolderAndContents - copy folder and all it contents
     * @param from - path to the source file
     * @param to - path to the target file
     * @return true if successful
     */
    static bool copyFolderAndContents(const std::string& from, const std::string& to);

    /**
     * @brief copyFile - copy file
     * @param from - path to the source file
     * @param to - path to the target file
     * @return true if successful
     */
    static bool copyFile(const std::string& from, const std::string& to);

    /**
     * @brief removeFolder - delete folder
     * @param folderName - file path
     * @return true if successful
     */
    static bool removeFolder(const std::string& fileName);

    /**
     * @brief removeFile - delete file
     * @param fileName - file path
     * @return true if successful
     */
    static bool removeFile(const std::string& fileName);

    /**
     * @brief renameFolder - renaming folder
     * @param oldPath - old folder path
     * @param newPath - new folder path
     */
    static void renameFolder(const std::string& oldPath, const std::string& newPath);

    /**
     * @brief checkIfFileExists - check if file or folder exists
     * @param fileName - file or folder name
     * @return
     */
    static bool checkIfFileExists(std::string fileName,  bool verbose = false);

    #ifdef VTD_OS_LINUX
    /**
     * @brief getIpAdresse - get current IP adresse linux only [TODO] -windows implementation
     * @param IpAdress - ip adresse
     * @param hostName - host name
     */
    static void getIpAdresse(std::string& IpAdress, std::string& hostName);
    #endif

    /**
     * @brief getCurrentPath - get curent folder path
     * @param currentPath
     * @return true if succes
     */
    static bool getCurrentPath(std::string& currentPath);

    /**
     * @brief turnOnVtd - start vtd
     * @param vtdRoot - root folder has to be specified
     * @param setupName - setup name
     * @param projectName - project name
     */
    static bool turnOnVtd(const std::string& vtdRoot, const std::string& setupName, const std::string& projectName, unsigned int timeToWait = TURN_ON_TIME_OUT);

    /**
     * @brief turnOffVtd - shoe down vtd
     * @param vtdRoot - vtd root
     * @param timeToWait - wait after stop is exucuted
     */
    static bool turnOffVtd(const std::string& vtdRoot, unsigned int timeToWait = TURN_OFF_TIME_OUT);

    template<typename T>
    static std::string toString(T value)
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
};

} // Internal

} // VTD
#endif //_VTD_FRAMEWORK_FILE_SYSTEM_IO_H

