/* ===================================================
 *  file:       Communicator.hh
 * ---------------------------------------------------
 *  purpose:	manages communication in the framework
 * ---------------------------------------------------
 *  first edit:	08.01.2008 by M. Dupuis @ VIRES GmbH
 *  last mod.:  08.01.2008 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_COMMUNICATOR_HH
#define _FRAMEWORK_COMMUNICATOR_HH

#include "CallbackIface.hh"
#include "BaseClass.hh"
#include <vector>

// forward declaration
namespace Com
{
    class ComHandler;
}

namespace Framework
{

// forward declaration
class Controller;
class ShdMem;

class Communicator : public Com::CallbackIface, public BaseClass
{
    public:
       static const unsigned int sConnTypeUDP          = 1;
       static const unsigned int sConnTypeTCP          = 2;
       static const unsigned int sConnTypeLoopback     = 3;
       static const unsigned int sConnTypeTCPClient    = 4;
       static const unsigned int sConnTypeSharedMemory = 5;
       static const unsigned int sConnTypeUDPReceive   = 6;
       static const unsigned int sConnTypeUDPSend      = 7;
       static const unsigned int sConnTypeMcastSend    = 8;
       static const unsigned int sConnTypeMcastReceive = 9;
       
    protected:
        /**
        * pointer to communication handler
        */
        Com::ComHandler* mComHandler;
    
        /**
        * pointer to controller for callback mechanism
        */
        Controller *mController;

        /**
        * remember whether communicator has been initialized
        */
        bool mInitialized;

        /**
        * set the communication interface
        */
        std::string mInterface;
        
        /**
        * save information about the individual connections
        */
        typedef struct
        {
            unsigned int                mPortNo;
            Com::PortBase::PortProtocol mProtocol;
            unsigned int                mType;
            std::string                 mServer;
            std::string                 mName;
            bool                        mConnected;
            unsigned int                mShmKey;
            unsigned int                mShmSize;
            unsigned int                mShmCurrentBuffer;
            unsigned int                mShmReleaseMask;
            Framework::ShdMem*          mpShm;
            bool                        mCanSend;
            bool                        mCanReceive;
        } ConnStruct;
        
        std::vector< ConnStruct > mConnVec;
        
        /**
        * counter for checking connections
        */
        unsigned int mCheckCount;
        
        /**
        * frequency for checking connections
        */
        unsigned int mCheckFreq;
        
        /**
        * remember the simulation time
        */
        double mSimTime;
        
    private:
        /**
        * buffer for outgoing messages
        */
        typedef struct
        {
            std::string    mConnName;
            double         mTgtSimTime;
            unsigned char* mData;
            unsigned int   mSize;
        } MsgBufferEntry_t;
        
        /**
        * keep a vector of buffered messages
        */
        std::vector< MsgBufferEntry_t > mMsgBufferOut;
        
    public:
        /**
        * this class should be singleton within each module
        * so, here's a means to control this
        */
        static Communicator* sInstance;
    
        /**
        * constructor
        *   @param  name    name under which data is managed
        *   @param  ctrlr   pointer to controller object
        *   @param  myError error handler
        *   @param  interface name of the communication interface
        */
        explicit Communicator( const std::string & name, 
                               Controller* ctrlr,
                               Util::ErrorBase *myError = 0,
                               const std::string & interface = "eth0" );

        /**
        * Destroy the class. 
        */
        virtual ~Communicator();
        
        /**
        * init communication
        * @return   success/failure
        */
        bool init();

        /**
        * read incoming messages
        * @param simTime    current simulatio time
        */
        void update( const double & simTime );

        /**
        * action called for incoming raw data
        *   @param  pkg     the package that was received
        */
        void incomingPackage( const Com::NetPackage & pkg );
        
        /**
        * create a single connection for UDP sending 
        * @param name           the name of the connection
        * @param no             number of the port
        * @param targetAddress  target address that is to be used in case of unicast
        * @return true if connection was established (i.e. connected has changed to true)
        */
        bool createConnectionUDPSend( const std::string & name, unsigned int no, const std::string & targetAddress = std::string( "" ) );
        
        /**
        * create a single connection for UDP receiving 
        * @param name  the name of the connection
        * @param no    number of the port
        * @return true if connection was established (i.e. connected has changed to true)
        */
        bool createConnectionUDPReceive( const std::string & name, unsigned int no );
        
        /**
        * create a single connection for MultiCast sending 
        * @param name           the name of the connection
        * @param no             number of the port
        * @param targetAddress  target address that is to be used in case of unicast
        * @param interface      interface which is to be used by the connection
        * @param loop           set to true if sender shall be able to loop
        * @return true if connection was established (i.e. connected has changed to true)
        */
        bool createConnectionMulticastSend( const std::string & name, unsigned int no, const std::string & targetAddress = std::string( "" ), std::string interface = std::string( "eth0" ), bool loop = false );
        
        /**
        * create a single connection for MultiCast receiving 
        * @param name           the name of the connection
        * @param no             number of the port
        * @param targetAddress  target address that is to be used in case of unicast
        * @param interface      interface which is to be used by the connection
        * @return true if connection was established (i.e. connected has changed to true)
        */
        bool createConnectionMulticastReceive( const std::string & name, unsigned int no, const std::string & targetAddress = std::string( "" ), std::string interface = std::string( "eth0" ) );
        
        /**
        * create a single connection for loopback sending 
        * @param name  the name of the connection
        * @param no    number of the port
        * @return true if connection was established (i.e. connected has changed to true)
        */
        bool createConnectionLoopbackSend( const std::string & name, unsigned int no );
        
        /**
        * create a single server for TCP sending, accepting up to 5 clients 
        * @param name  the name of the connection
        * @param no    number of the port
        * @return true if connection was established (i.e. connected has changed to true)
        */
        bool createConnectionTCPServer( const std::string & name, unsigned int no );
        
        /**
        * create a TCP client connection 
        * @param name   the name of the connection
        * @param no     number of the port
        * @param server name of the server
        * @return true if connection was established (i.e. connected has changed to true)
        */
        bool createConnectionTCPClient( const std::string & name, unsigned int no, const std::string & server = "127.0.0.1" );
        
        /**
        * create an SHM connection 
        * @param name   the name of the connection
        * @param shmKey shared memory key
        * @param shmSize size of the shared memory
        * @param shmDoubleBuffer true if double-buffered shm shall be created
        * @param shmReleaseMask  release mask which is to be set after shm has been written
        * @return true if connection was established (i.e. connected has changed to true)
        */
        bool createConnectionShm( const std::string & name, const unsigned int & shmKey, const unsigned int & shmSize,
                                  const bool & shmDoubleBuffer = false, const unsigned int & shmReleaseMask = 0x0, bool canSend = true, bool canReceive = true );
        /**
        * send a message via a given connection 
        * @param name  the name of the connection
        * @param data  pointer to the data
        * @param size  size of the package
        * @param delay delay this package by the given time [s]
        * @return true if data could be sent
        */
        virtual bool sendViaConnection( const std::string & name, void* data, unsigned int size, const double & delay = 0.0 );
        
        /**
        * terminate an existing connection 
        * @param name  the name of the connection
        */
        void terminateConnection( const std::string & name );
        
        /**
        * set the protocol for a given connection
        * @param name  the name of the connection
        * @param protocol   identifier of the protocol
        */
        void setProtocol( const std::string & name, const Com::PortBase::PortProtocol & protocol );
        
        /**
        * check a single connection
        * @param name      the name of the connection
        * @param connected the last known state of the connection
        * @param showMsg   show a reconnect message in the console
        * @param protocol  the protocol of the connection
        * @return true if connection has been established (i.e. connected has changed to true)
        */
        bool checkConnection( const std::string & Name, bool & connected, bool showMsg, const Com::PortBase::PortProtocol & protocol );
        
        /**
        * create a decription string from the given connection type
        * @param type   type of the connection
        * @return string identifier
        */
        std::string connType2string( unsigned int type );
        
        /**
        * creata a connection based on the arguments provided
        * @param name            unique name of the connection
        * @param portNo          number of the communication port
        * @param type            type of the communication port
        * @param protocol        communication protocol
        * @param server          for client ports> address of server
        * @param shmKey          for shm connection: key
        * @param shmSize         for shm connection: size
        * @param shmDoubleBuffer true if double-buffered shm shall be created
        * @param shmReleaseMask  release mask which is to be set after shm has been written
        * @return true if connection could be created
        */
        bool createConnection( const std::string & name, unsigned int portNo, unsigned int type,
                               Com::PortBase::PortProtocol protocol = Com::PortBase::protoRaw, const std::string & server = "127.0.0.1",
                               const unsigned int & shmKey = 0, const unsigned int & shmSize = 0, const bool & shmDoubleBuffer = false, 
                               const unsigned int & shmReleaseMask = 0x0, bool canSend = true, bool canReceive = true );
        
        /**
        * set the frequency for checking connections
        * @param freq   frequency (looop count between two checks)
        */
        void setCheckFrequency( int freq );
        
    protected:
        /**
        * establish network connections
        */
        virtual void establishConnections();
        
        /**
        * check the network connections
        */
        virtual void checkConnections();
        
        /**
        * check the for the sending of delayed messages
        */
        virtual void checkDelayedMessages();
        
        /**
        * check whether an environment variable has been set for a given port and
        * use this value instead of the default if applicable
        * @param  defaultValue   the default value of the port
        * @param  envName   name of the environment variable which needs to be set
        * @return port number (either default or environment value)
        */
        int getPortFromEnv( int defaultValue, const char* envName );
        
        /**
        * add a connection to the list of known connections
        * @param name           unique name of the connection
        * @param portNo         number of the communication port
        * @param type           type of the communication port
        * @param connected      status of the connection
        * @param protocol       communication protocol
        * @param server         for client ports: address of server
        * @param shmKey         for shm connection: key
        * @param shmSize        for shm connection: size
        * @param shmPtr         for shm connection: pointer to shm object
        * @param shmReleaseMask release mask which is to be set after shm has been written
        * @return true if conection could be registered
        */
        bool registerConnection( const std::string & name, unsigned int portNo, unsigned int type, bool connected = false,
                                 Com::PortBase::PortProtocol protocol = Com::PortBase::protoRaw, const std::string & server = "127.0.0.1",
                                 const unsigned int & shmKey = 0, const unsigned int & shmSize = 0, ShdMem* shmPtr = 0,
                                 const unsigned int & shmReleaseMask = 0x0, bool canSend = true, bool canReceive = true );
        
        /**
        * remove a conection from the list of known connections
        * @param name       unique name of the connection
        * @return true if connection has previously been registered
        */
        bool removeConnection( const std::string & name );
};
} // namespace Framework

#endif /* _FRAMEWORK_COMMUNICATOR_HH */
