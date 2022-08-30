#ifndef _TCP_PORT_H_
#define _TCP_PORT_H_

#include <iostream>
#include <stdint.h>

#include "service_port.h"

namespace VTD
{
/**
 * @brief The UdpPort - take care of udp protocol client communication, it is not copyable
 */
class TcpPort : public ServicePort, public boost::noncopyable
{
    public:
        // tcp socket map
        typedef std::pair<ConnectionHandle, boost::shared_ptr<boost::asio::ip::tcp::socket> > TcpSocketEntry;
        typedef std::map<TcpSocketEntry::first_type, TcpSocketEntry::second_type> TcpSocketMap;
        /**
        * @brief TcpPort constructor
        */
        explicit TcpPort();

        explicit TcpPort(const TcpPort& other);

        /**
        * @brief ~TcpPort destructor
        */
        virtual ~TcpPort();

        /**
        * @brief disconnect disconnect socket
        * @param handle communication handle
        */
        virtual void disconnect(ConnectionHandle& handle);

        /**
         * @brief connectToPort connect socket
         * @param hostname host name
         * @param portNumber port number
         * @param typeOfConnection type of connection
         * @param handle communication handle
         * @param sendBlock block sending
         * @param receiveBlock block receiving
         */
        virtual void connectToPort(const std::string& hostname, unsigned int portNumber, Protocols::Enum typeOfConnection, ConnectionHandle& handle, bool sendBlock = false, bool receiveBlock = false);

        /**
         * @brief OnReceiveSCP callback call on recive data
         * @param ErrorCode error code
         * @param handle communication handle
         */
        virtual void OnReceiveSCP(const boost::system::error_code& ErrorCode, ConnectionHandle& handle);

        /**
         * @brief OnReceiveRDB callback call on recive data
         * @param ErrorCode error code
         * @param handle communication handle
         */
        virtual void OnReceiveRDB(const boost::system::error_code& ErrorCode, ConnectionHandle& handle);

        /**
         * @brief isConnected check is socket open
         * @param handle communication handle
         * @return true if it is open
         */
        virtual bool isConnected(const ConnectionHandle& handle);

        /**
        * @brief OnSendSCP - async function call after data have been send
        * @param ErrorCode - error code
        */
        virtual void OnSendSCP(const boost::system::error_code& ErrorCode, const ConnectionHandle& handle);

        /**
        * @brief OnSendRDB - async function call after data have been send
        * @param ErrorCode - error code
        */
        virtual void OnSendRDB(const boost::system::error_code& ErrorCode, const ConnectionHandle& handle);

        /**
         * @brief OnConnectSCP call after connecting
         * @param ErrorCode  error code
         * @param handle handle
         */
        virtual void OnConnectSCP(const boost::system::error_code& ErrorCode, const ConnectionHandle& handle);

        /**
        * @brief startReading - start io service
        */
        virtual void startReading();

        /**
        * @brief stopReading stop io service
        */
        virtual void stopReading();

        /**
        * @brief readData read scp data
        * @param buffer template buffer it could be either array or vector
        * @param socket socket from which we will receive data
        * @param handle communication handle
        */
        template<typename T> void readData(T& buffer, boost::shared_ptr<boost::asio::ip::tcp::socket>& socket, const ConnectionHandle& handle)
        {
            if (!socket)
            {
                throw std::runtime_error("readData: socket is NULL!");
            }
            boost::asio::async_read(*socket, boost::asio::buffer(buffer, buffer.size())
                                , boost::bind(&TcpPort::OnReceiveSCP
                                                , this
                                                , boost::asio::placeholders::error
                                                , handle));
        }

        /**
        * @brief readData read data
        * @param buffer template buffer it could be either array or vector
        * @param socket socket from which we will receive data
        * @param callback calllback function whichn will be called after receiving data
        * @param handle communication handle
        */
        template<typename T>
        void readData(T& buffer, boost::shared_ptr<boost::asio::ip::tcp::socket>& socket, Callback& callback)
        {
            if (!socket)
            {
                throw std::runtime_error("readData: socket is NULL!");
            }
            boost::asio::async_read(*socket, boost::asio::buffer(buffer, buffer.size()), callback);

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
         * @brief setCallbackReadSCP
         * @param cb callback function
         */
        inline void setCallbackReadSCP(Callback cb) {funcSCPRead_ = cb;}

        /**
         * @brief setCallbackReadRDB
         * @param cb callback function
         */
        void setCallbackReadRDB(Callback cb) {funcRDBRead_ = cb;}

        /**
         * @brief setCallbackWriteSCP
         * @param cb callback function
         */
        void setCallbackWriteSCP(Callback cb) {funcSCPWrite_ = cb;}

        /**
         * @brief setCallbackWriteRDB
         * @param cb callback function
         */
        void setCallbackWriteRDB(Callback cb) {funcRDBWrite_ = cb;}

        /**
         * @brief close connection
         * @param socket
         */
        void close(boost::shared_ptr<boost::asio::ip::tcp::socket>& socket);

        /**
         * @brief getTcpSocket pointer to socket
         * @param handle communication handle
         * @return socket sheared pointer
         */
        virtual boost::shared_ptr<boost::asio::ip::tcp::socket> getTcpSocket (const ConnectionHandle& handle) const {return socketMap_.find(handle)->second;}

    protected:
        // tcp socket map
        TcpSocketMap socketMap_;
    private:

          bool getEndPoint(const std::string& hostname, const unsigned int& portNumber, boost::asio::ip::tcp::resolver::iterator& tcpEndPoint);

          bool connectToSocket(boost::shared_ptr<boost::asio::ip::tcp::socket>& socket, const boost::asio::ip::tcp::resolver::iterator& tcpEndPoint);

          bool setHandles(Protocols::Enum typeOfConnection, const ConnectionHandle& handle, const boost::asio::ip::tcp::resolver::iterator& tcpEndPoint, boost::shared_ptr<boost::asio::ip::tcp::socket>& socket);

    private:
        bool readingRdbBody_;  //!< whether we're trying to read rdb body or header
        bool readingScpBody_;  //!< whether we're trying to read scp body or header
        bool isScpConnected_;  //!< check if scp is connected
        // general call back function for scp and rdb
        Callback funcSCPRead_;
        Callback funcRDBRead_;
        Callback funcSCPWrite_;
        Callback funcRDBWrite_;
        // reconenct if user use config stage
        void reconnectSCPPort(const ConnectionHandle& handle);
        // scp end point
        boost::asio::ip::tcp::resolver::iterator scpPortIter_;
        // mutex
        boost::mutex connectionLock_;
};
    // tcp port
    typedef boost::shared_ptr<TcpPort> TcpPort_ptr;
}
#endif // TCP_PORT
