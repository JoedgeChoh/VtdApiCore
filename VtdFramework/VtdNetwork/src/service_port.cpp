#include <VtdNetwork/service_port.h>

namespace VTD
{

ServicePort::ServicePort(){}

ServicePort::~ServicePort()
{
}

 ConnectionHandle ServicePort::connectSCP(const std::string& hostname, unsigned int portNumber)
 {
     ConnectionHandle handle = 0;
     queryAddress(hostname,portNumber, Protocols::SCP, handle);
     return handle;
 }

 ConnectionHandle ServicePort::connectRDB(const std::string& hostname, unsigned int portNumber, Protocols::Enum typeOfConnection, bool sendBlock, bool receiveBlock)
 {
     ConnectionHandle handle;

     queryAddress(hostname, portNumber, typeOfConnection, handle, sendBlock, receiveBlock);

     return handle;
 }

 void ServicePort::queryAddress(const std::string& hostname, unsigned int portNumber, Protocols::Enum typeOfConnection, ConnectionHandle& handle, bool sendBlock, bool receiveBlock)
 {
     switch (typeOfConnection)
     {
        case Protocols::SCP:
        {
           connectToPort(hostname, portNumber, typeOfConnection, handle);
        }
        break;

        case Protocols::RDB_TCP:
        {
            connectToPort(hostname, portNumber, typeOfConnection, handle);
        }
        break;

        case Protocols::RDB_UDP:
        case Protocols::RDB_UDP_RECEIVE_ONLY:
        case Protocols::RDB_UDP_SEND_ONLY:
        {
            connectToPort(hostname, portNumber, typeOfConnection, handle, sendBlock, receiveBlock);

        }break;

     default:
     break;
     }
 }

ConnectionHandle ServicePort::generateHandle(const std::string& hostname, unsigned int port, Protocols::Enum protocol)
{
    ConnectionHandle handle = protocol;
    handle = port + (handle << 6) + (handle << 16) - handle;
    const ConnectionHandle length = boost::numeric_cast<ConnectionHandle>( hostname.length() );
    for (ConnectionHandle i = 0; i < length; ++i)
    {
        handle = boost::numeric_cast<unsigned int>( hostname[i] )  + (handle << 6) + (handle << 16) - handle;
    }
    return handle;
}

}
