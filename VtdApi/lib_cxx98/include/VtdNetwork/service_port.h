#ifndef _SERVICE_PORT_H_
#define _SERVICE_PORT_H_

#include <iostream>
#include <stdint.h>

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/chrono.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/viSCPIcd.h>

#include "message.h"
#include "MessageCallback.h"

/**************************************************************************************/
/******  both tcp and udp use synchron connect to match with old interface ************/
/******  receiving and sending is async ***********************************************/
/**************************************************************************************/

namespace VTD
{
/**
 * @brief The Protocols struct
 */
struct Protocols
{
    enum Enum
    {
          SCP = 0               // SCP TCP
        , RDB_TCP               // RDB TCP
        , RDB_UDP               // RDB UDP
        , RDB_UDP_SEND_ONLY     // RDB UDP block sending
        , RDB_UDP_RECEIVE_ONLY  // RDB UDP block receiving
    };
};
/**
* the magic numbers for different protocols
*/
static const unsigned short sMagicNoSCP = 40108;  // simulation control protocol
static const unsigned short sMagicNoRDB = 35712;  // run-time data bus

// Callback function
typedef boost::function<void(const boost::system::error_code&, const ConnectionHandle&)> Callback;

/**
 * @brief The ServicePort class define basic parameters common for all ports in boost asio
 */
class ServicePort : public MessageCallback
{
    public:
         /**
         * @brief constructor
         */
        ServicePort();

        /**
        * @brief destructor
        */
        virtual ~ServicePort();

        /**
         * @brief connectSCP - connect to receive scp messages
         * @param hostname - host name
         * @param portNumber - port number for scp is always constant
         * @return
         */
        ConnectionHandle connectSCP(const std::string& hostname, unsigned int portNumber);

        /**
         * @brief connectRDB - connect to receive rdb messages
         * @param hostname - host name
         * @param portNumber - port number
         * @param typeOfConnection - type of connection, important for UDP
         * @param sendBlock - blocking sending
         * @param receiveBlock - blocking receiving
         * @return communication handle
         */
        ConnectionHandle connectRDB(const std::string& hostname, unsigned int portNumber, Protocols::Enum typeOfConnection, bool sendBlock = false, bool receiveBlock = false);

        /**
         * @brief connectToPort - connect to port
         * @param hostname - host name
         * @param portNumber - port name
         * @param typeOfConnection - type of connection, important for UDP
         * @param handle - communication handle
         * @param sendBlock - blocking sending
         * @param receiveBlock - blocking receiving
         */
        virtual void connectToPort(const std::string& hostname
                                        , unsigned int portNumber
                                        , Protocols::Enum typeOfConnection
                                        , ConnectionHandle& handle
                                        , bool sendBlock = false
                                        , bool receiveBlock = false) = 0;

        /**
         * @brief isConnected is port opened
         * @param handle - communication handle
         * @return true if port is opened
         */
        virtual bool isConnected(const ConnectionHandle& handle) = 0;

        /**
         * @brief disconnect - disconnect from port
         * @param handle - communication
         */
        virtual void disconnect(ConnectionHandle& handle) = 0;

        /**
         * @brief generateHandle - generate handle number
         * @param hostname - host name
         * @param port - port number
         * @param protocol - type of protocol
         * @return
         */
        virtual ConnectionHandle generateHandle(const std::string& hostname, unsigned int port, Protocols::Enum protocol);

        /**
         * @brief startReading - start boost asio io_service
         */
        virtual void startReading() = 0;

        /**
         * @brief stopReading - stop boost asio io_service
         */
        virtual void stopReading() = 0;

        /**
         * @brief writeScpData - write scp data
         * @param buffer - string buffer or SCP message
         * @param handle - communication handle
         * @param SENDER_NAME_MY - sender with default parameter
         * @param RECEIVER_NAME_MY - reciver with default parameter
         */
        virtual void writeScpData(const std::string& buffer
                                    , const ConnectionHandle& handle
                                    , const char* senderName = "VtdApi"
                                    , const char* receiverName = "TaskControl") = 0;

        /**
         * @brief writeRDBData - write RDBdata
         * @param bufferRDB - data buffer
         * @param handle - communication hnadle
         */
        virtual void writeRDBData(const std::vector<char>& bufferRDB, const ConnectionHandle& handle) = 0;

 protected:
        // buffer for scp and rdb data
        boost::array<char, SCP_HEADER_SIZE> bufferScpHdr_;
        std::vector<char> bufferScpData_;
        boost::array<char, RDB_HEADER_SIZE> bufferRDBHdr_;
        std::vector<char> bufferRDBData_;
        // necessery for windows
        std::vector<char> sendBuffer_;
        std::vector<char> bufferScpHdrSend_;
        // boost asio io services
        boost::shared_ptr<boost::asio::io_service> io_service_;

private:
        /**
         * @brief queryAddress - query ip adresse
         * @param hostname - host name
         * @param portNumber - port number
         * @param typeOfConnection - type of connection
         * @param handle - communication handle
         * @param sendBlock - send block
         * @param receiveBlock - receive block
         */
        void queryAddress(const std::string& hostname
                                , unsigned int portNumber
                                , Protocols::Enum typeOfConnection
                                , ConnectionHandle& handle
                                , bool sendBlock = false
                                , bool receiveBlock = false);

};
    // service port pointers
    typedef boost::shared_ptr<ServicePort> ServicePort_ptr;
}
#endif // SERVICE_PORT
