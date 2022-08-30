/* ===================================================
 *  file:       Wrapper.hh
 * ---------------------------------------------------
 *  purpose:	this class wraps a module's dso so
 *              that it can be accessed in an easy
 *              manner
 * ---------------------------------------------------
 *  first edit:	08.01.2008 by M. Dupuis @ VIRES GmbH
 *  last mod.:  08.01.2008 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_WRAPPER_HH
#define _FRAMEWORK_WRAPPER_HH

/* ====== INCLUSIONS ====== */
#include <string>
#include "BaseClass.hh"


namespace Com {
    class ComHandler;
}

namespace Framework
{
// forward declarations
class Plugin;
class Iface;

class Wrapper : public BaseClass
{
    public:
        static const char MAKE_FUNC[];
        
    private: 
        /**
        * keep the handle to the dynamic library
        */
        void* mDlHandle;
        
        /**
        * keep a pointer to the object
        */
        Plugin* mPlugin;
        
        /**
        * factory function for the module
        */
        Plugin* (*mpMaker) ( void );
        
        /** 
        * keep the status of the wrapper
        */
        bool mOperable;

    public:
        /**
        * constructor
        * @param myError    an external error handler
        * @param file       name of the module file
        * @param name       name of the wrapper
        * @param isolateNamespace isolate the namespace of the plugin, ticket #11409
        **/
        explicit Wrapper( Util::ErrorBase *myError,
                          const std::string & file,
                          const std::string & name,
                          bool isolateNamespace = false );

        /**
        * Destroy the class. 
        */
        virtual ~Wrapper();
        
        /**
        * load a new module
        * @param  name of the sensor we are loading
        , 
        * @return the return value of the library's init function
        */
        bool loadPlugin( const std::string & module, bool isolateNamespace = false );
        
        /**
        * unLoad a sen sensor
        * @return the return value of the library's unload function
        */
        bool unloadPlugin();
        
        /**
        * set data in the wrapped module from given interface data
        * @param frameNo    calling framework's internal frame number
        * @param data       interface data
        * @param force      update data even if same frame is sent again
        * @return the return value of the library's message handling function
        */
        int setData( const unsigned int & mFrameNo, Iface *data, bool force = false );
        
        /**
        * update the wrapped module from given interface data
        * @param frameNo    calling framework's internal frame number
        * @param data       interface data
        * @return the return value of the library's message handling function
        */
        int update( const unsigned int & mFrameNo, Iface *data );
        
        /**
        * reset the wrapped module
        * @param  simTime the simulation time used as reset time
        * @return true if successful
        */
        bool reset( const double & simTime );
        
        /**
        * let me know whether the wrapper is operable
        * @return   operability of the wrapper
        */
        bool isOperable() const;
        
        /**
        * get the pointer to the plugin
        * @return   plugin pointer
        */
        Plugin* getPlugin();
        
        /**
        * check whether the plugin referred to by the wrapper is
        * persistent
        * @return true if plugin referred to is persistent
        */
        bool pluginIsPersistent();
};

} // end namespace Framework

#endif /* _FRAMEWORK_WRAPPER_HH */
