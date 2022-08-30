#include <VtdEncryption/VtdEncryption.h>
#include <VtdCore/Logging/Log.h>

#ifdef __linux__
    #include <dlfcn.h>
#elif _WIN32
    #include <windows.h>
#endif
namespace VTD
{
#ifdef __linux__
	static void* handle = 0;
#elif _WIN32
	static HMODULE handle = 0;
#endif
	VtdEncryption* VtdEncryption::load(const std::string& pluginPath)
    {
        if ( pluginPath.empty() )
        {
            VTD_LOG_ERR( "VtdEncryption: Plugin path is empty! ");
            return NULL;
        }

#ifdef __linux__
            handle = dlopen( pluginPath.c_str(), RTLD_LAZY );
#elif _WIN32
            handle = LoadLibrary(pluginPath.c_str());
#else
            VTD_LOG_ERR("VtdEncryption: OS Platform is not supported");
            return NULL;
#endif
        if ( handle == NULL )
        {
#ifdef __linux__
            VTD_LOG_ERR( dlerror() << "VtdEncryption:  could not open the shared library. ");
#elif _WIN32
            VTD_LOG_ERR("VtdEncryption: could not open the shared library. ");
#endif
            return NULL;
        }
#ifdef __linux__
        if (VtdEncryptionFactoryFunction* createEncryption = (VtdEncryptionFactoryFunction*)(dlsym( handle, "createVtdEncryptionPlugin")))
#elif _WIN32
        if (VtdEncryptionFactoryFunction* createEncryption = (VtdEncryptionFactoryFunction*)(GetProcAddress(handle, "createVtdEncryptionPlugin")))
#endif
        {
            return createEncryption();
        }

#ifdef __linux__
        VTD_LOG_ERR( dlerror() << ". VtdEncryption:  Please define createVtdEncryptionPlugin factory function. " );
        if ( dlclose(handle) )
        {
            VTD_LOG_ERR( dlerror() );
        }
#elif _WIN32
        VTD_LOG_ERR("VtdEncryption:  Please define createVtdEncryptionPlugin factory function. ");
        if (!FreeLibrary(handle))
        {
            VTD_LOG_ERR("VtdEncryption: The library could not be freed");
        }
#endif
        return NULL;
    }

    bool VtdEncryption::unload()
    {
        if ( !handle )
        {
            VTD_LOG_ERR("VtdEncryption: There is nothing to unload. It might have already been unloaded." );
            return true;
        }
#ifdef __linux__            
        if ( dlclose(handle) )
        {
            VTD_LOG_ERR( dlerror() );
            return false;
        }
#elif _WIN32
        if (!FreeLibrary(handle))
        {
            VTD_LOG_ERR("VtdEncryption: The library could not be freed");
            return false;
        }
#endif
        return true;
    }

    bool VtdEncryption::checkFileExtension(const std::string& filename)
    {
        std::string fileExtension = filename.substr(filename.find_last_of(".") + 1);

        if ( fileExtension.empty() )
        {
            //VTD_LOG_ERR("VtdEncryption: Missing extension. File should have an extension starting with letter 'e' !");
            return false;  
        }

        if ( fileExtension[0] != 'e' )
        {
            //VTD_LOG_ERR("VtdEncryption: Wrong extension. File extension should start with letter 'e' !");
            return false;
        }
        return true;
    }

} // namespace VTD

