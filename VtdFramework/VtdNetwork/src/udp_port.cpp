#include <VtdNetwork/udp_port.h>

using boost::asio::ip::udp;

namespace VTD
{
UdpPort::UdpPort()
{
    io_service_ = boost::shared_ptr<boost::asio::io_service> (new boost::asio::io_service);
    headerBuffer_ = boost::shared_ptr<RDB_MSG_HDR_t> (new RDB_MSG_HDR_t);
}

UdpPort::~UdpPort()
{
    if(!io_service_->stopped())
        io_service_->stop();
}

void UdpPort::disconnect(ConnectionHandle& handle)
{
    boost::mutex::scoped_lock scoped_lock(connectionLock_);

    if (socketMap_.find(handle) == socketMap_.end())
    {
        std::cout << "VtdNetwork: Handle does not exist::disconnected" << std::endl;
        return;
    }

    if (isConnected(handle) && socketMap_.count(handle) != 0)
    {
          close(socketMap_.find(handle)->second.socket);
          socketMap_.erase(socketMap_.find(handle));
          handle = 0;
    }
}

void UdpPort::connectToPort(const std::string& hostname
                            , unsigned int portNumber
                            , Protocols::Enum typeOfConnection
                            , ConnectionHandle& handle
                            , bool sendBlock
                            , bool receiveBlock)
{
    handle = generateHandle(hostname, portNumber, typeOfConnection);
    UdpConnection_t udpConnection_t;
    // create socket
    udpConnection_t.socket = boost::shared_ptr<udp::socket>(new udp::socket(*io_service_));
    // open socket
    udpConnection_t.socket->open( boost::asio::ip::udp::v4());
    // get end-point
    if (!getEndPoint(udpConnection_t, hostname, portNumber))
    {
        handle = 0;
        return;
    }
    // connect to port
    if (!connectToPortUdp(udpConnection_t, typeOfConnection, sendBlock, receiveBlock))
    {
        handle = 0;
        return;
    }

    socketMap_.insert(std::make_pair(handle, udpConnection_t));
    // Register callback general function
    if (typeOfConnection == Protocols::RDB_UDP || typeOfConnection == Protocols::RDB_UDP_RECEIVE_ONLY)
    {
        setCallbackRDB(boost::bind(&UdpPort::OnReceiveRDB
                             , this, boost::asio::placeholders::error
                             , handle));
        readDataUdp(bufferRDBHdr_, handle, funcRDB_);
    }
}
 
bool UdpPort::connectToPortUdp(UdpConnection_t& udpConnection_t
                            , Protocols::Enum typeOfConnection
                            , bool sendBlock
                            , bool receiveBlock)
{
    boost::system::error_code ec;
    udpConnection_t.receiveBlock = receiveBlock;
    udpConnection_t.sendBlock = sendBlock;
    std::cout << "VtdNetwork: Connecting to port " << udpConnection_t.endpoint.port() << "...\n";
    try
    {
        switch (static_cast<int>(typeOfConnection))
        {
            case Protocols::RDB_UDP_SEND_ONLY:
            {
                boost::asio::ip::udp::socket::reuse_address ra(true);
                udpConnection_t.socket->set_option(ra);
                udpConnection_t.socket->set_option(boost::asio::socket_base::broadcast(true));
                udpConnection_t.socket->bind(udpConnection_t.endpoint);
                udpConnection_t.socket->connect(udpConnection_t.endpoint, ec);

            }break;

            case Protocols::RDB_UDP_RECEIVE_ONLY:
            {
                boost::asio::ip::udp::socket::reuse_address ra(true);
                udpConnection_t.socket->set_option(ra);
                udpConnection_t.socket->bind(udpConnection_t.endpoint);
            }break;

            case Protocols::RDB_UDP:
            {
                boost::asio::ip::udp::socket::reuse_address ra(true);
                udpConnection_t.socket->set_option(ra);
                udpConnection_t.socket->set_option(boost::asio::socket_base::broadcast(true));
                udpConnection_t.socket->bind(udpConnection_t.endpoint);
                udpConnection_t.socket->connect(udpConnection_t.endpoint, ec);
            }break;
        }

        std::cout << "VtdNetwork: Connected to port: " << udpConnection_t.endpoint.port() << "\n";
        return true;
    }
    catch (const boost::system::system_error& ex)
    {
        std::cout << "VtdNetwork: Could not connected to port: " << udpConnection_t.endpoint.port() << "\n";
        std::cout << "VtdNetwork: Exception: " << ex.what() << "\n";
        return false;
    }
}

bool UdpPort::getEndPoint(UdpConnection_t& udpConnection_t, const std::string& hostname, const unsigned int& portNumber)
{
    try
    {
        boost::asio::ip::udp::resolver resolver(*io_service_);
        boost::asio::ip::udp::resolver::query queryA(hostname, boost::lexical_cast<std::string> (portNumber));
        boost::asio::ip::udp::resolver::iterator udpEndPoint = resolver.resolve(queryA);
        udpConnection_t.endpoint = *udpEndPoint;
        return true;
    }
    catch (const boost::system::system_error& ex)
    {
        std::cout << "VtdNetwork: Could not resolve hostname: " << hostname << " and port" << portNumber <<"\n";
        std::cout << "VtdNetwork: Exception: " << ex.what() << "\n";
        return false;
    }
}

void UdpPort::OnReceiveRDB(const boost::system::error_code& ErrorCode, ConnectionHandle& handle)
{
    if (ErrorCode.value() == 0)
    {
        if (socketMap_.find(handle)->second.socket->available() == 0)
        {
            socketMap_.find(handle)->second.socket->async_receive(boost::asio::null_buffers(), funcRDB_);
        }
        else
        {
            bufferRDBData_.resize(socketMap_.find(handle)->second.socket->available());
            readDataUdp(bufferRDBData_, handle, funcRDB_);
            decodeRDBMessageUDP(handle);
        }
    }
    else
    {
        disconnect(handle);
    }
}

bool UdpPort::isConnected(const ConnectionHandle& handle)
{
    if (socketMap_.empty())
        return false;

    return handle ? socketMap_.find(handle)->second.socket->is_open() : false;

}

void UdpPort::setCallbackRDB(Callback cb)
{
       funcRDB_ = cb;
}

void UdpPort::writeScpData(const std::string& buffer, const ConnectionHandle& handle, const char* SENDER_NAME_MY, const char* RECEIVER_NAME_MY)
{
    boost::mutex::scoped_lock scoped_lock(connectionLock_);
    bufferScpHdrSend_.resize(sizeof(SCP_MSG_HDR_t));
    SCP_MSG_HDR_t* msg  = reinterpret_cast<SCP_MSG_HDR_t*>(bufferScpHdrSend_.data());
    // fill the header information
    msg->magicNo  = SCP_MAGIC_NO;
    msg->version  = SCP_VERSION;
    msg->dataSize = boost::numeric_cast<uint32_t>( buffer.size() );
    memcpy(msg->sender, SENDER_NAME_MY, SCP_NAME_LENGTH);
    memcpy(msg->receiver, RECEIVER_NAME_MY, SCP_NAME_LENGTH);
    memcpy(bufferScpHdrSend_.data(), msg, sizeof(SCP_MSG_HDR_t));
    std::copy (buffer.begin(), buffer.end(), std::back_inserter(bufferScpHdrSend_));
    socketMap_.find(handle)->second.socket->async_send(boost::asio::buffer(bufferScpHdrSend_, bufferScpHdrSend_.size())  , boost::bind(&UdpPort::OnSendSCP
                                                                                                        , this, boost::asio::placeholders::error));
}

void UdpPort::writeRDBData(const std::vector<char>& bufferRDB, const ConnectionHandle& handle)
{
    // Check if socket map is empty
    if (socketMap_.empty()) return;

    boost::mutex::scoped_lock scoped_lock(connectionLock_);
    // nessecery for windows
    sendBuffer_ = boost::move(bufferRDB);
    socketMap_.find(handle)->second.socket->async_send_to(boost::asio::buffer(bufferRDB, bufferRDB.size())
                                                    , socketMap_.find(handle)->second.endpoint
                                                    , boost::bind(&UdpPort::OnSendRDB
                                                                  , this, boost::asio::placeholders::error));
}

void UdpPort::startReading()
{
    io_service_->run();
}

void UdpPort::stopReading()
{
    io_service_->stop();
}

void UdpPort::decodeRDBMessageUDP(const ConnectionHandle& handle)
{
    if (bufferRDBData_.empty())
        return;

    memcpy (headerBuffer_.get(), bufferRDBData_.data(), sizeof(RDB_MSG_HDR_t));
    if (headerBuffer_->magicNo == sMagicNoRDB)
        if (bufferRDBData_.size() == headerBuffer_->dataSize + headerBuffer_->headerSize)
            updateRDBdeque(bufferRDBData_, handle);

}

void UdpPort::close(boost::shared_ptr<udp::socket>& socket)
{
    boost::system::error_code errorcode;
    // Reconnect scp port after sending config stage
    socket->shutdown(boost::asio::ip::udp::socket::shutdown_both, errorcode);
    if (errorcode)
    {
        std::cerr << "VtdNetwork: UdpPort::close() shutdown: socket.shutdown error: " << errorcode.message() << std::endl;
        return;
    }

    // deallocate socket.  will close any open descriptors
    socket->close(errorcode);
    if (errorcode)
    {
        std::cerr << "VtdNetwork: UdpPort::close() close: socket.close error: " << errorcode.message() << std::endl;
        return;
    }
}

void UdpPort::OnSendRDB(const boost::system::error_code& ErrorCode)
{
    if (ErrorCode.value() != 0)
    {
        std::cerr << "VtdNetwork: Error::Sending RDB Message::" << ErrorCode.message() << std::endl;;
    }
}

void UdpPort::OnSendSCP(const boost::system::error_code& ErrorCode)
{
    if (ErrorCode.value() != 0)
    {
        std::cerr << "VtdNetwork: Error::Sending SCP Message::" << ErrorCode.message() << std::endl;;
    }
}
}
