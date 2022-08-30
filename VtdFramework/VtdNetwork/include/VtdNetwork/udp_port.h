#ifndef _UDP_PORT_H_
#define _UDP_PORT_H_

#include <iostream>
#include <stdint.h>

#include "service_port.h"

namespace VTD
{
// have to made since we have to define receiving point where we should get data
typedef struct UDP_CONNECTION
{
   ConnectionHandle handle;
   bool receiveBlock;
   bool sendBlock;
   boost::shared_ptr<boost::asio::ip::udp::socket> socket;
   boost::asio::ip::udp::endpoint endpoint;
}UdpConnection_t;

/**
 * @brief The UdpPort - take care of udp protocol client communication, it is not copyable
 */
class UdpPort :  public ServicePort, public boost::noncopyable
{
    public:
        // map of udp sockets
        typedef std::map<ConnectionHandle, UdpConnection_t> UdpSocketMap;
         /**
         * @brief UdpPort - constructor
         */
        UdpPort();

        /**
         * @brief ~UdpPort - destructor
         */
        virtual ~UdpPort();

        /**
         * @brief disconnect - disconnect connection
         * @param handle - communcation handle
         */
        virtual void disconnect(ConnectionHandle& handle);

        /**
         * @brief connectToPort
         * @param hostname
         * @param portNumber
         * @param typeOfConnection - typeofConnection for example send, receive or snd and receive
         * @param handle - communication handle
         * @param sendBlock - blocking send
         * @param receiveBlock - blocking receive
         */
        virtual void connectToPort(const std::string& hostname, unsigned int portNumber, Protocols::Enum typeOfConnection, ConnectionHandle& handle, bool sendBlock = false, bool receiveBlock = false);

        /**
         * @brief OnReceiveRDB - async callback function
         * @param errorCode - error code if 0 no error data received succesufully
         * @param handle - communication handle
         */
        virtual void OnReceiveRDB(const boost::system::error_code& ErrorCode, ConnectionHandle& handle);

        /**
         * @brief isConnected - check if socket is open
         * @param handle - communication handle
         * @return  true is socket is open
         */
        virtual bool isConnected(const ConnectionHandle& handle);

        /**
         * @brief OnSendRDB - async function call after data have been send
         * @param ErrorCode - error code
         */
        void OnSendRDB(const boost::system::error_code& ErrorCode);

        /**
         * @brief readDataUdp - read udp data
         * @param buffer - buffer either std::vector, std::array, or boost::array
         * @param handle - communication handle
         * @param callback - callback function to be called if reading is successful
         */
        template<typename T>
        void readDataUdp(T& buffer, const ConnectionHandle& handle, Callback& callback)
        {
           socketMap_.find(handle)->second.socket->async_receive(boost::asio::buffer(buffer, buffer.size()), callback);
        }

        /**
         * @brief writeScpData - write scp data
         * @param buffer - string buffer with scp data
         * @param handle - communication handler
         * @param senderName - sender name
         * @param receiverName - reciver  name
         */
        virtual void writeScpData(const std::string& buffer, const ConnectionHandle& handle, const char* senderName = "VtdApi", const char* receiverName = "TaskControl");

        /**
         * @brief writeRDBData - write rdb data
         * @param bufferRDB - vector with rdb data
         * @param handle - communication handle
         */
        virtual void writeRDBData(const std::vector<char>& bufferRDB, const ConnectionHandle& handle);

        /**
         * @brief startReading - start io service
         */
        virtual void startReading();

        /**
         * @brief stopReading stop io service
         */
        virtual void stopReading();

        /**
         * @brief set_callbackRDB
         * @param cb callback function
         */
        virtual void setCallbackRDB(Callback cb);

        /**
         * @brief close - close port disconnect
         * @param socket - udp boost asio udp socket
         */
        virtual void close(boost::shared_ptr<boost::asio::ip::udp::socket>& socket);

 protected:

        // socket map
        UdpSocketMap socketMap_;
        // boost asio io service
        boost::shared_ptr<boost::asio::io_service> io_service_;
        // udp conection structure
        UdpConnection_t udpConnection_;

private:
        /**
         * @brief connectToPortUdp - connect to udp port
         * @param udpConnection_t - udp connection struct
         * @param typeOfConnection - type of connection such read only, receive only, etc....
         * @param sendBlock - block sending
         * @param receiveBlock - block receiving
         * @return
         */
        bool connectToPortUdp(UdpConnection_t& udpConnection_t
                           , Protocols::Enum typeOfConnection
                           , bool sendBlock
                           , bool receiveBlock);

        /**
         * @brief decodeRDBMessageUDP - decode rdb message
         * @param handle - communication handle
         */
        void decodeRDBMessageUDP(const ConnectionHandle& handle);

        /**
         * @brief getEndPoint - get end point
         * @param udpConnection_t - udp connection struct
         * @param hostname - host name
         * @param portNumber - port number
         * @return true if succes
         */
        bool getEndPoint(UdpConnection_t& udpConnection_t, const std::string& hostname, const unsigned int& portNumber);

        /**
         * @brief OnSendSCP - on send scp callback
         * @param ErrorCode - error code
         */
        void OnSendSCP(const boost::system::error_code& ErrorCode);

    private:
        // callback function
        Callback funcRDB_;
        // header buffer
        boost::shared_ptr<RDB_MSG_HDR_t> headerBuffer_;
        // connection mutex
        boost::mutex connectionLock_;
};
        // udp port
        typedef boost::shared_ptr<UdpPort> UdpPort_ptr;
}


#endif // UDP_PORT
