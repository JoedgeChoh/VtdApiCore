#include <VtdCore/FileSystemIO.h>
#include <VtdCore/Logging/Log.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <boost/algorithm/string/replace.hpp>
#include <boost/foreach.hpp>

namespace fs = boost::filesystem;

#ifdef VTD_OS_LINUX
#include <arpa/inet.h>
#include <netdb.h>
#endif

namespace {

    void recursive_copy(const fs::path &src, const fs::path &dst)
    {
        if (fs::exists(dst))
        {
            throw std::runtime_error(dst.generic_string() + " exists");
        }

        if (fs::is_directory(src))
        {
            fs::create_directories(dst);
            BOOST_FOREACH(fs::directory_entry& item, fs::directory_iterator(src))
            {
                recursive_copy(item.path(), dst/item.path().filename());
            }
        }
        else if (fs::is_regular_file(src))
        {
            fs::copy(src, dst);
        }
        else
        {
            throw std::runtime_error(dst.generic_string() + " not dir or file");
        }
    }
}

namespace VTD {
namespace Internal {

/************************ FileSystemIO::setCurrentPath() ************************/
bool FileSystemIO::setCurrentPath(const std::string& folderName)
{
    try
    {
        if (fs::exists(folderName))    // does folderName actually exist?
        {
            if (fs::is_directory(folderName))      // is folderName a directory?
            {
                std::cout << folderName << " directory already exist\n";
                fs::current_path(fs::system_complete(fs::path(folderName)));
                std::cout << fs::current_path().c_str() << std::endl;
                return true;
            }
            else
            {
            std::cout << folderName << " exists, but is neither a regular file nor a directory\n";
            return false;
            }
        }
        else
        {
            std::cout << folderName << " does not exist\n";
            return false;
        }
    }

  catch (const fs::filesystem_error& ex)
  {
    std::cout << ex.what() << '\n';
    return false;
  }
}

/************************ FileSystemIO::checkIfFolderExist() ************************/
bool FileSystemIO::checkIfFolderExist(const std::string& folderName, bool verbose)
{
    try
    {
        if (fs::exists(folderName))    // does  folderName actually exist?
        {
            if (fs::is_directory(folderName))      // is folderName a directory?
            {
                std::cout << folderName << " directory already exist\n";
                return true;
            }
            else
            {
            std::cout << folderName << " exists, but is neither a regular file nor a directory\n";
            return false;
            }
        }
        else
        {
            std::cout << folderName << " does not exist\n";
            if (verbose)
                 VTD_LOG_ERRNO(" " <<  folderName.c_str() << "does not exist.......................................\n");

            return false;
        }
    }

  catch (const fs::filesystem_error& ex)
  {
    std::cout << ex.what() << '\n';
    return false;
  }
}

/************************ FileSystemIO::createFolder() ************************/
bool FileSystemIO::createFolder(const std::string& folderName)
{
    try
    {
        if (fs::create_directory(folderName))
            return true;
        else
            return false;
    }
    catch (fs::filesystem_error &ex)
    {
       std::cout << ex.what() << '\n';
       return false;
    }
}

/************************ FileSystemIO::setPermissions() ************************/
bool FileSystemIO::setPermissions(const std::string& path, boost::filesystem::perms permissions, bool includeContent /*=false*/)
{
    try
    {
        fs::permissions(path, permissions);
    }
    catch(const fs::filesystem_error& ex)
    {
       std::cout << path << ". Cannot set permissions: " << ex.what() << std::endl;
       return false;
    }

    if (includeContent)
    {
        if (fs::is_directory(path))
        {
            fs::directory_iterator end_iter;
            for (fs::directory_iterator dir_itr(path); dir_itr != end_iter; ++dir_itr)
            {
                try
                {
                    if (fs::is_regular_file(dir_itr->status()))
                    {
                        fs::permissions(path, permissions);
                    }
                    else if (fs::is_directory(dir_itr->status()))
                    {
                        setPermissions(dir_itr->path().string(), permissions, includeContent);
                    }

                }
                catch ( const std::exception & ex )
                {
                    std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
                }
            }
        }
    }

    return true;
}

/************************ FileSystemIO::getAllFilesInDir() ************************/
bool FileSystemIO::getAllFilesInDir(const std::string& directory, const std::string& fileExtension, std::vector<std::string>& fileList, bool verbose)
{
    fs::path full_path = fs::system_complete( fs::path(directory) );

    if (!fs::exists(full_path))
    {
        std::cout << "Not found: " << full_path.generic_string() << std::endl;
        return false;
    }

    if (fs::is_directory(full_path))
    {
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(full_path); dir_itr != end_iter; ++dir_itr)
        {
            try
            {
                if (fs::is_regular_file(dir_itr->status()) && dir_itr->path().extension() == fileExtension)
                {
                    fileList.push_back(dir_itr->path().leaf().string());
                    if (verbose)
                        std::cout << "Adding: " << dir_itr->path().leaf() << std::endl;
                }

            }
            catch ( const std::exception & ex )
            {
                std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Path is not a directory: " << full_path.generic_string() << std::endl;
    }

    if (fileList.empty())
        return false;
    else
        return true;
}

/************************ FileSystemIO::makeAbsolutePathFromRelative() ************************/
bool FileSystemIO::makeAbsolutePathFromRelative(std::string& filePath)
{
   fs::path filePathRel(filePath);
   fs::path cPath = fs::current_path();
   fs::path absolute_path;

   if (filePathRel.is_relative())
   {
       try
       {
          absolute_path = fs::canonical(filePathRel,cPath);
          std::cout << absolute_path.string() << '\n';

       }
       catch (fs::filesystem_error &ex)
       {
          std::cout << ex.what() << '\n';
          std::cout << "Enter valid relative path" << '\n';
          return false;
       }
   }
   else
   {
       absolute_path = filePathRel;
   }

   std::cout << filePathRel.string() << std::endl;
   filePath = absolute_path.string();
   return true;
}

/************************ FileSystemIO::checkIfFileExists() ************************/
bool FileSystemIO::checkIfFileExists(std::string fileName, bool verbose)
{

   boost::filesystem::path p(fileName);

   if (exists(p))    // does path p actually exist?
   {
      if (is_regular_file(p))        // is path p a regular file?
      {
         if(verbose)
            std::cout << p << " size is " << file_size(p) << '\n';
      }
      else if (is_directory(p))      // is path p a directory?
      {
         if(verbose)
            std::cout << p << " is a directory\n";
      }
      else
      {
         if(verbose)
            std::cout << p << " exists, but is not a regular file or directory\n";
      }
   }
   else
   {
      std::cout << p << " does not exist\n";
      if (verbose)
           VTD_LOG_ERRNO("file" << p.c_str() << " does not exist.......................................");

      return false;
   }
   return true;
}

/************************ FileSystemIO::getFileNameFromPath() ************************/
std::string FileSystemIO::getFileNameFromPath(const std::string& path, bool verbose)
{
    try
    {
        if (fs::exists(path))    // does  folderName actually exist?
        {
            if (fs::is_directory(path))      // is p a directory?
            {
                std::cout << path << " directory already exist \n";
                return path;
            }

            else
            {
                if (!fs::is_regular_file(path))
                    std::cout << path << " exists, but is neither a regular file nor a directory\n";

                return getItemNameFromPath(path);
            }
        }
        else
        {
            std::cout << path << " does not exist\n";
            if (verbose)
                 VTD_LOG_ERRNO("path " << path.c_str() << "does not exist.......................................");

            return path;
       }
   }
   catch (const fs::filesystem_error& ex)
   {
      std::cout << ex.what() << '\n';
      return path;
   }
}

/************************ FileSystemIO::getItemNameFromPath() ************************/
std::string FileSystemIO::getItemNameFromPath(const std::string& path)
{
    fs::path p(path);
    return p.filename().string();
}


/************************ FileSystemIO::copyFolderAndContents() ************************/
bool FileSystemIO::copyFolderAndContents(const std::string& from, const std::string& to)
{
    fs::path pathFrom(from);
    fs::path pathTo(to);

    try
    {
        recursive_copy(pathFrom, pathTo);
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        std::cerr << "VtdCore: Error: " << e.what() << std::endl;
        return false;
    }

    return true;
}

/************************ FileSystemIO::copyFile() ************************/
bool FileSystemIO::copyFile(const std::string& from, const std::string& to)
{
    fs::path fileFrom(from);
    fs::path fileTo(to);

    try
    {
        fs::copy_file(fileFrom, fileTo);
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        std::cerr << "VtdCore: Error: " << e.what() << std::endl;
        return false;
    }

    return true;
}


/************************ FileSystemIO::removeFolder() ************************/
bool FileSystemIO::removeFolder(const std::string& folderName)
{
    fs::path path(folderName);

    try
    {
         fs::remove_all(path);
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
         std::cerr << "VtdCore: Error: " << e.what() << std::endl;
         return false;
    }

    return true;
}

/************************ FileSystemIO::removeFile() ************************/
bool FileSystemIO::removeFile(const std::string& fileName)
{
       fs::path file(fileName);

       try
       {
            fs::remove(file);
       }
       catch (const boost::filesystem::filesystem_error& e)
       {
            std::cerr << "VtdCore: Error: " << e.what() << std::endl;
            return false;
       }

       return true;
}

/************************ FileSystemIO::renameFolder() ************************/
void FileSystemIO::renameFolder(const std::string& oldPath, const std::string& newPath)
{
    fs::path sourceDir(oldPath);
    fs::path destinationDir(newPath);
    fs::rename(sourceDir, destinationDir);
}

#ifdef VTD_OS_LINUX
/************************ FileSystemIO::getIpAdresse() ************************/
void FileSystemIO::getIpAdresse(std::string& IpAdress, std::string& hostName)
{
    // linux only
    char hostname[128];
    struct hostent *he;
    gethostname(hostname, sizeof hostname);
    printf("My hostname: %s\n", hostname);
    hostName = hostname;
    he = gethostbyname(hostname);

    if (he == NULL)
    { // do some error checking
      herror("gethostbyname"); // herror(), NOT perror()
      return;
    }
    //print information about this host:
    printf("Official name is: %s\n", he->h_name);

    printf("IP address: %s\n", inet_ntoa(*(struct in_addr*)he->h_addr));
    IpAdress = inet_ntoa(*(struct in_addr*)he->h_addr);
}
#endif

/************************ FileSystemIO::getCurrentPath() ************************/
bool FileSystemIO::getCurrentPath(std::string& currentPath)
{
    try
    {
        currentPath = fs::current_path().string();
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        std::cerr << "VtdCore: Error: " << e.what() << std::endl;
        return false;
    }

    return true;
}

/************************ FileSystemIO::turnOnVtd() ************************/
bool FileSystemIO::turnOnVtd(const std::string& vtdRoot, const std::string& setupName, const std::string& projectName, unsigned int timeToWait)
{
    std::string currentPath;
    getCurrentPath(currentPath);
    // check if folder exists if yes change folder
    if (currentPath != vtdRoot)
        if (!setCurrentPath(vtdRoot))
        {
            std::cout << "Invalide path :" << vtdRoot << std::endl;
            return false;
        }
        else
            getCurrentPath(currentPath);
    else
        currentPath = vtdRoot;

    if (!checkIfFileExists(currentPath + "/bin/vtdStop.sh"))
    {
        std::cout << "Invalide VTD root path :" << vtdRoot << " could not find VtdStart.sh" <<std::endl;
        return false;
    }
    // Start Vtd
    std::string fileName = currentPath + "/bin/vtdStart.sh -project=" + projectName + " -setup=" + setupName +  " -autoConfig >& debug.txt";
    if (system(fileName.c_str()) < 0)
    {
        std::cout << "Could not start VTD: " << strerror(errno) << std::endl;
    }

    boost::this_thread::sleep_for(boost::chrono::seconds(timeToWait));
    return true;
}

/************************ FileSystemIO::turnOffVtd() ************************/
bool FileSystemIO::turnOffVtd(const std::string& vtdRoot, unsigned int timeToWait)
{
    std::string currentPath;
    getCurrentPath(currentPath);
    // check if folder exists if yes change folder
    if (currentPath != vtdRoot)
        if (!setCurrentPath(vtdRoot))
        {
            std::cout << "Invalide path :" << vtdRoot << std::endl;
            return false;
        }
        else
            getCurrentPath(currentPath);
    else
        currentPath = vtdRoot;

    if (!checkIfFileExists(currentPath + "/bin/vtdStart.sh"))
    {
        std::cout << "Invalide VTD root path :" << vtdRoot << " could not find VtdStart.sh" <<std::endl;
        return false;
    }

    // Stop Vtd
    std::string fileName = currentPath + "/bin/vtdStop.sh";
    if (system(fileName.c_str()) != 0)
    {
        std::cout << "Could not stop VTD: " << std::endl;
        std::cout << "Program will not executed without valid root path." << std::endl;
    }

    boost::this_thread::sleep_for(boost::chrono::seconds(timeToWait));
    return true;
}

} // Internal

} // VTD
