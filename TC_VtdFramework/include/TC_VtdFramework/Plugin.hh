/* ===================================================
 *  file:       Plugin.hh
 * ---------------------------------------------------
 *  purpose:	base class for module loadable
 *              by controller
 * ---------------------------------------------------
 *  first edit:	08.01.2008 by M. Dupuis @ VIRES GmbH
 *  last mod.:  08.01.2008 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_PLUGIN_HH
#define _FRAMEWORK_PLUGIN_HH

/* ====== INCLUSIONS ====== */
#include <string>

// actual class declaration for access via shared mechanisms
// is hidden behind this little function; make sure, this
// function is included in all data accesss libraries
#define VTD_MAKE_MODULE_DEFINITION(pluginName) \
extern "C" { \
    Framework::Plugin* makeModule() { return new pluginName(); } \
}

namespace Framework
{

// forward declarations
class Iface;
class ScpParser;

class Plugin
{
    public:
        /**
        * factory function for creating a new object, derived from ParamIface
        */
        static Plugin* makeIface();

    public:
        /**
        * constructor
        *   @param  myName networking name of the module
        **/
        explicit Plugin();

        /**
        * Destroy the class.
        */
        virtual ~Plugin();

        /**
        * initialize interface
        * @return success/failure
        */
        virtual bool init() = 0;

        /**
        * copy incoming interface data; will be called for all plugins before calling
        * any update routine
        * @param frameNo the current frame number
        * @param data    interface data
        * @param force   force the data update even if the frame number didn't change
        * @return return code
        */
        virtual int setData( const unsigned long & frameNo, Iface* data, bool force = false ) = 0;

        /**
        * handle an incoming message
        * @param frameNo the current frame number
        * @param data    interface data
        * @return return code
        */
        virtual int update( const unsigned long & frameNo, Iface* data ) = 0;

        /**
        * terminate the module plugin
        * @return success/failure
        */
        virtual bool unload();

        /**
        * set the name of the module plugin
        * @param name    name of the module
        */
        virtual bool setName( const std::string & name );

        /**
        * set the (preferably) unique ID of the plugin
        * @param id     new id of the plugin
        */
        void setId( unsigned long id );

        /**
        * get the (preferably) unique ID of the plugin
        * @return id of the plugin
        */
        unsigned long getId() const;

        /**
        * add / clear a debug mask to the existing mask
        * @param mask   additional mask
        * @param add    set to true in order to really add the mask, otherwise it will be removed
        */
        void addDebugMask( unsigned long mask, bool add = true );

        /**
        * clear the entire debugging mask
        */
        void clearDebugMask();

        /**
        * check whether a certain debug flag is valid within the plugin
        * @param flag   the debug flag to check for
        * @return true if flag is set
        */
        bool hasDebugFlag( unsigned long flag ) const;

        /**
        * get the plugin's name
        * @return name of the plugin
        */
        const std::string & getName() const;

        /**
        * enable/disable persistency of this plugin. If it's persistent,
        * it's not supposed to be unloaded by the respective manager
        * @param enable the new persistency status
        */
        void setPersistent( bool enable );

        /**
        * retrieve the persistency property of the plugin
        * @return true if plugin is persistent
        */
        bool isPersistent() const;

        /**
        * reset a plugin (called when simulation re-starts)
        * @param    simTime the simulation time used as reset time
        * @return true if successful
        */
        virtual bool reset( const double & simTime );

        /**
        * handle directly a message that arrived via network
        * @param data   pointer to the message data
        * @param size   size of the message
        * @param protocol protocol type of the message (-1 for unknown)
        */
        virtual void handleMessage( void* data, size_t size, int protocol = -1 );

        /**
        * handle directly an SCP element
        * @param parser pointer to the ScpParser which contains the SCP element
        * @return true if element could be handled
        */
        virtual bool handleSCPElement( ScpParser* parser );

        /**
        * set activity of a plug-in
        * @param enable if true, plug-in is active
        */
        virtual void setEnabled( bool enable = true );

        /**
        * check whether a plug-in is active
        * @return true if plug-in is active
        */
        bool isEnabled() const;

        /**
        * query whether the frame of the plug-in has been completed
        * @return true if plugin reports that internal frame has been completed
        */
        virtual bool isFrameComplete();

        /**
        * provide information about a plugin's software revision
        */
        const std::string & getRevisionInfo() const;

    protected:
        /**
        * my own name
        */
        std::string mName;

        /**
        * my own numeric id
        */
        unsigned long mId;

        /**
        * set debug mask
        */
        unsigned long mDebugMask;

        /**
        * is this plugin persistent? If so, it should not
        * be unloaded
        */
        bool mPersistent;

        /**
        * is this plugin active?
        */
        bool mEnabled;

        /**
        * is the frame complete?
        */
        bool mFrameComplete;

        /**
        * revision string identifier
        */
        std::string mRevisionStr;
};

} // namespace Framework
#endif /* _FRAMEWORK_PLUGIN_HH */
