/* ===================================================
 *  file:       Controller.hh
 * ---------------------------------------------------
 *  purpose:	framework controller
 * ---------------------------------------------------
 *  first edit:	08.01.2008 by M. Dupuis @ VIRES GmbH
 *  last mod.:  08.01.2008 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_CONTROLLER_HH
#define _FRAMEWORK_CONTROLLER_HH

// ====== INCLUSIONS ======
#include "BaseClass.hh"
#include <map>

namespace Framework
{

// forward declaration
class Communicator;
class Wrapper;
class Iface;
class Plugin;
    
class Controller : public BaseClass
{
    public:
        /**
        * constructor
        *   @param  name    name under which data is managed
        *   @param  myError error handler
        */
        explicit Controller( const std::string & name, 
                             Util::ErrorBase *myError = 0 );

        /**
        * Destroy the class. 
        */
        virtual ~Controller();
        
        /**
        * init the class
        * @return   success/failure
        */
        bool init();

        /**
        * periodic update routines
        * @param    simTime current simulation time
        * @return   success/failure
        */
        virtual bool update( const double & simTime );

        /**
        * reset execution
        * @param    simTime current simulation time
        * @return   success/failure
        */
        bool reset( const double & simTime );
        
        /**
        * handle a message that arrived via network
        * @param data     pointer to the message data
        * @param size     size of the message
        * @param protocol protocol type of the message (-1 for unknown)
        */
        virtual void handleMessage( void* data, size_t size, int protocol = -1 ) = 0;
        
        /**
        * handle an SCP message that arrived via network
        * @param data   pointer to the message data
        * @param size   size of the message
        * @param port   id of the port which received the data
        */
        virtual void handleSCPMessage( void* data, size_t size );
        
        /**
        * get the interface
        * @return pointer to current iface
        */
         Iface* getIface();
         
         /**
         * enable / disable performance debugging
         * @param enable    if true, performance debugging is ON
         */
         void setPerformanceDebug( bool enable );
         
         /**
         * check for enabled performance debugging
         * @return true if performance debugging is ON
         */
         bool performanceDebugActive() const;

    protected:
        /**
        * load a plugin from the given filename
        * @param name       the name of the plugin
        * @param objName    name of the executable object (dso)
        * @param objDir     directory where the object can be found
        * @param callPrio   call priority of the object
        * @param isolateNamespace isolate the namespace of the plugin, ticket #11409
        * @return   success/failure
        */
        bool loadPlugin( const std::string & name, const std::string & objName, const std::string & objDir, const unsigned int & callPrio = 10000, bool isolateNamespace = false );
        
        /**
        * set a plugin's call priority
        * @param name       the name of the plugin
        * @param callPrio   call priority of the plugin
        * @return   success/failure
        */
        bool prioritizePlugin( const std::string & name, const unsigned int & callPrio = 10000 );

        /**
        * set the interface
        * @param iface  pointer to allocated iface space
        */
        void setIface( Iface* iface );
        
        /**
        * get a pointer to the plugin
        * @param name   name of the plugin
        * @return pointer to plugin
        */
        Plugin* getPlugin( const std::string & name );
        
        /**
        * get a pointer to the plugin at the given index
        * in the internal plugin map
        * @param  index index position for which to get the plugin
        * @return pointer to plugin or 0 if index is invalid
        */
        Plugin* getPlugin( int index );
        
        /**
        * set the communicator
        * @param comm   pointer to the communicator
        */
        void setCommunicator( Communicator* comm );
        
        /**
        * update all registered wrappers
        * @param    forceDataUpdate  if true, update the incoming data, also if the frame number didn't change
        * @return   success/failure
        */
        void updateWrappers( bool forceDataUpdate = false );
        
        /**
        * reset all registered wrappers
        * @param    simTime the simulation time used as reset time
        * @return   success/failure
        */
        void resetWrappers( const double & simTime );
        
        /**
        * delete all registered wrappers
        */
        void deleteWrappers();
        
        /**
        * delete a plugin and the associated wrapper
        * @param    plugin  plugin to pointer which is to be deleted
        * @param    deactivateOnly if true, just de-register the plugin, don't really delete
        */
        void deletePlugin( Plugin* plugin, bool deactivateOnly = false );
        
        /**
        * forward messages to plugins
        * @param data   pointer to the message data
        * @param size   size of the message
        * @param protocol protocol type of the message (-1 for unknown)
        */
        void forwardMessageToWrappers( void* data, size_t size, int protocol );
        
    private:
        /**
        * hold a list of wrappers for plugin parameters
        * the registered plugin priority is held vs. the wrapper for the plugin
        */
        typedef std::multimap < unsigned int, Wrapper* > WrapMap;
        WrapMap mWrapMap;
        
    protected:
        /**
        * keep an eye on simulation time
        */
        double mSimTime;
        
        /**
        * count the frames
        */
        unsigned long mFrameNo;
        
        /**
        * hold a pointer to an interface
        */
        Iface* mIface;
        
        /**
        * calculate the registered wrappers
        */
        bool mCalcWrappers;
        
        /**
        * measure performance
        */
        bool mDebugPerformance;

    private:
        /**
        * someone needs to handle the communication
        */
        Communicator* mCommunicator;

        /**
        * add a wrapper from a given configuration
        * @param name       the name of the sensor
        * @param objName    name of the executable object (dso)
        * @param objDir     directory where the object can be found
        * @param callPrio   call priority for the wrapper
        * @param isolateNamespace isolate the namespace of the plugin, ticket #11409
        * @return   success/failure
        */
        bool addWrapper( const std::string & name, const std::string & objName, const std::string & objDir, const unsigned int & callPrio, bool isolateNamespace );

        /**
        * remove a wrapper from a given sensor name
        * @param name   the name of the sensor
        * @return   success/failure
        */
        bool removeWrapper( const std::string & name );
};
} // namespace Framework

#endif /* _FRAMEWORK_CONTROLLER_HH */
