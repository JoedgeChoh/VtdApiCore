#include <VtdNetwork/tcp_port.h>
#include <VtdCore/Logging/Log.h>
using boost::asio::ip::tcp;

namespace VTD
{

TcpPort::TcpPort() : readingRdbBody_(false), readingScpBody_(false), isScpConnected_(false)
{
    io_service_ = boost::shared_ptr<boost::asio::io_service> (new boost::asio::io_service);
}

TcpPort::~TcpPort()
{
    if(!io_service_->stopped())
        io_service_->stop();
}

void TcpPort::disconnect(ConnectionHandle& handle)
{
    boost::mutex::scoped_lock scoped_lock(connectionLock_);

    TcpSocketMap::iterator socketEntry = socketMap_.find(handle);
    if (socketEntry == socketMap_.end())
    {
        VTD_LOG("VtdNetwork: Handle does not exist::disconnected");
        return;
    }

    if (isConnected(handle) && socketMap_.count(handle) != 0)
    {
        close(socketEntry->second);
        socketMap_.erase(socketEntry);
        handle = 0;
    }
}

void TcpPort::connectToPort(const std::string& hostname, unsigned int portNumber, Protocols::Enum typeOfConnection, ConnectionHandle& handle, bool sendBlock, bool receiveBlock)
{
    if (sendBlock || receiveBlock)
          VTD_LOG("VtdNetwork: Tcp port could not block sending or receiving");

    handle = generateHandle(hostname, portNumber, typeOfConnection);
    boost::shared_ptr<tcp::socket> socket(new tcp::socket (*io_service_));
    boost::asio::ip::tcp::resolver::iterator tcpEndPoint;

    if (!getEndPoint(hostname, portNumber, tcpEndPoint))
    {
        handle = 0;
        return;
    }

    if (!connectToSocket(socket, tcpEndPoint))
    {
        handle = 0;
        return;
    }

    setHandles(typeOfConnection, handle, tcpEndPoint, socket);

    socketMap_.insert(std::make_pair(handle, socket));
}

void TcpPort::OnReceiveSCP(const boost::system::error_code& ErrorCode, ConnectionHandle& handle)
{
    if (ErrorCode.value() == 0)
    {

        SCP_MSG_HDR_t* msgHeader = reinterpret_cast<SCP_MSG_HDR_t*> (bufferScpHdr_.data());

        if (readingScpBody_)
        {
            updateSCPdeque(bufferScpData_, bufferScpHdr_, handle);
            // clean header buffer
            bufferScpHdr_.fill(0);
            readingScpBody_ = false;
            readData(bufferScpHdr_, socketMap_.find(handle)->second, funcSCPRead_);
        }
        else
        {
            bufferScpData_.resize(msgHeader->dataSize);
            readingScpBody_ = true;
            readData(bufferScpData_, socketMap_.find(handle)->second, funcSCPRead_);
        }
    }
    else if (ErrorCode.value() == boost::asio::error::eof)
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
        if (socketMap_.count(handle) == 0)
        {
            disconnect(handle);
        }
        else
        {
            boost::shared_ptr<ConnectionEvent> event(new ConnectionEvent(handle, false));
            connEvent_(event.get());
            // if error is end of file
            isScpConnected_ = false;
            reconnectSCPPort(handle);
        }
    }
    else
    {
        // disconnect if error is shutdown socket
        disconnect(handle);
    }
}

void TcpPort::OnSendSCP(const boost::system::error_code& ErrorCode, const ConnectionHandle& handle)
{
    if (ErrorCode.value() != 0)
    {
        std::cerr << "VtdNetwork: Handle "<< handle << "Error::Sending SCP Message::" << ErrorCode.message() << std::endl;;
    }
}

void TcpPort::OnSendRDB(const boost::system::error_code& ErrorCode, const ConnectionHandle& handle)
{
    if (ErrorCode.value() != 0)
    {
        std::cerr << "VtdNetwork: Handle "<< handle <<" Error::Sending RDB Message::" << ErrorCode.message() << std::endl;;
    }
}


void TcpPort::OnReceiveRDB(const boost::system::error_code& ErrorCode, ConnectionHandle& handle)
{
    boost::unique_lock<boost::mutex> lck(connectionLock_, boost::defer_lock);

    if (ErrorCode.value() == 0)
    {
        RDB_MSG_HDR_t* header = reinterpret_cast<RDB_MSG_HDR_t*>(bufferRDBHdr_.data());

        if (readingRdbBody_)
        {
            bufferRDBData_.insert(bufferRDBData_.begin(), bufferRDBHdr_.begin(), bufferRDBHdr_.end());
            updateRDBdeque(bufferRDBData_, handle);
            bufferRDBHdr_.fill(0);
            readingRdbBody_ = false;
            readData(bufferRDBHdr_, socketMap_.find(handle)->second, funcRDBRead_);
        }
        else
        {
            bufferRDBData_.resize(header->dataSize);
            readingRdbBody_ = true;
            readData(bufferRDBData_, socketMap_.find(handle)->second, funcRDBRead_);
        }
    }
    else
    {
        disconnect(handle);
    }
}

void TcpPort::startReading()
{
    io_service_->run();
}

void TcpPort::stopReading()
{
    if(!io_service_->stopped())
        io_service_->stop();
}

void TcpPort::close(boost::shared_ptr<tcp::socket>& socket)
{
    boost::system::error_code errorcode;
    // Reconnect scp port after sending config stage
    std::cout << "VtdNetwork: Disconnect from " << socket->remote_endpoint() << std::endl;
    socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, errorcode);

    if (errorcode)
    {
        std::cerr << "VtdNetwork: TcpPort::close() shutdown: socket.shutdown error: " << errorcode.message() << std::endl;
        return;
    }
    // deallocate socket.  will close any open descriptors
    socket->close(errorcode);
    if (errorcode)
    {
        std::cerr << "VtdNetwork: TcpPort::close() close: socket.close error: " << errorcode.message() << std::endl;
        return;
    }
}

bool TcpPort::isConnected(const ConnectionHandle& handle)
{
    if (socketMap_.count(handle) == 0)
        return false;

    return handle ? socketMap_.find(handle)->second->is_open() : false;

}

void TcpPort::writeScpData(const std::string& buffer, const ConnectionHandle& handle, const char* senderName, const char* receiverName)
{
    boost::mutex::scoped_lock scoped_lock(connectionLock_);
    bufferScpHdrSend_.resize(sizeof(SCP_MSG_HDR_t));
    SCP_MSG_HDR_t* msg  = reinterpret_cast<SCP_MSG_HDR_t*>(bufferScpHdrSend_.data());
    // fill the header information
    msg->magicNo  = SCP_MAGIC_NO;
    msg->version  = SCP_VERSION;
    msg->dataSize = boost::numeric_cast<uint32_t>( buffer.size() );
    memcpy(msg->sender, senderName, SCP_NAME_LENGTH);
    memcpy(msg->receiver, receiverName, SCP_NAME_LENGTH);
    memcpy(bufferScpHdrSend_.data(), msg, sizeof(SCP_MSG_HDR_t));
    std::copy (buffer.begin(), buffer.end(), std::back_inserter(bufferScpHdrSend_));
    socketMap_.find(handle)->second->async_send(boost::asio::buffer(bufferScpHdrSend_, bufferScpHdrSend_.size()), funcSCPWrite_);
}

void TcpPort::writeRDBData(const std::vector<char>& bufferRDB, const ConnectionHandle& handle)
{
    // Check if socket map is empty
    if (socketMap_.empty()) return;
    boost::mutex::scoped_lock scoped_lock(connectionLock_);
    // nessecery for windows
    sendBuffer_ = boost::move(bufferRDB);
    socketMap_.find(handle)->second->async_send(boost::asio::buffer(sendBuffer_, sendBuffer_.size()), funcRDBWrite_);
}

void TcpPort::reconnectSCPPort(const ConnectionHandle& handle)
{
    if (socketMap_.count(handle) == 0)
        return;

    boost::system::error_code errorcode;
    // Reconnect scp port after sending config stage
    TcpSocketMap::iterator entry = socketMap_.find(handle);
    if (entry != socketMap_.end())
    {
        entry->second->shutdown(boost::asio::ip::tcp::socket::shutdown_both, errorcode);
        if (errorcode)
        {
            std::cerr << "VtdNetwork: TcpPort::reconnectSCPPort() shutdown: socket.shutdown error: " << errorcode.message() << std::endl;
        }

        // deallocate socket.  will close any open descriptors
        entry->second->close(errorcode);
        if (errorcode)
        {
            std::cerr << "VtdNetwork: TcpPort::reconnectSCPPort() close: socket.shutdown error: " << errorcode.message() << std::endl;
        }

        entry->second->async_connect(scpPortIter_->endpoint(), boost::bind(&TcpPort::OnConnectSCP
                                                                           , this
                                                                           , boost::asio::placeholders::error
                                                                           , handle));
    }
}

void TcpPort::OnConnectSCP(const boost::system::error_code& ErrorCode, const ConnectionHandle& handle)
{
    if (ErrorCode.value() == 0) // Successful connected
    {
         isScpConnected_ = true;
         TcpSocketMap::iterator socket = socketMap_.find(handle);
         if (socket != socketMap_.end())
             readData(bufferScpHdr_, socket->second, funcSCPRead_);
    }
    else if (scpPortIter_ != tcp::resolver::iterator())
    {
        TcpSocketMap::iterator socket = socketMap_.find(handle);
        if (socket == socketMap_.end())
            return;

        socket->second->close(); // FIXME [BB] crashes every now an then, may the result of multiple VtdApi instances used

        socket->second->async_connect(scpPortIter_->endpoint()
                                        , boost::bind(&TcpPort::OnConnectSCP
                                        , this, boost::asio::placeholders::error
                                        , handle));
    }
    else
    {
        std::cerr << "VtdNetwork: socket.shutdown error: " << ErrorCode.message() << std::endl;
    }
}

bool TcpPort::getEndPoint(const std::string& hostname, const unsigned int& portNumber, tcp::resolver::iterator& tcpEndPoint)
{
    try
    {
        tcp::resolver resolver(*io_service_);
        tcp::resolver::query queryA(hostname, boost::lexical_cast<std::string> (portNumber));
        tcpEndPoint = resolver.resolve(queryA);
        return true;
    }
    catch (const boost::system::system_error& ex)
    {
        std::cout << "VtdNetwork: Could not resolve hostname '" << hostname << "' and port " << portNumber << ": " << ex.what() << "\n";
        return false;
    }
}

bool TcpPort::connectToSocket(boost::shared_ptr<tcp::socket>& socket, const tcp::resolver::iterator& tcpEndPoint)
{
    std::cout << "VtdNetwork: Trying to connect to " << tcpEndPoint->endpoint() << "...\n";
    try
    {
        socket->connect(tcpEndPoint->endpoint());
        socket->set_option(tcp::no_delay(true));

        std::cout << "VtdNetwork: Successfully connected to " << tcpEndPoint->endpoint() << std::endl;
        return true;
    }
    catch (const boost::system::system_error& ex)
    {
        std::cout << "VtdNetwork: Could not connect to " << tcpEndPoint->endpoint() << ": " << ex.what() << "\n";
        return false;
    }
}

bool TcpPort::setHandles(Protocols::Enum typeOfConnection, const ConnectionHandle& handle, const tcp::resolver::iterator& tcpEndPoint, boost::shared_ptr<tcp::socket>& socket)
{
    switch(static_cast<int>(typeOfConnection))
    {
        case Protocols::SCP:
        {
            setCallbackReadSCP(boost::bind(&TcpPort::OnReceiveSCP
                                , this, boost::asio::placeholders::error
                                , handle));
            setCallbackWriteSCP(boost::bind(&TcpPort::OnSendSCP
                                            , this, boost::asio::placeholders::error
                                            , handle));
            scpPortIter_ = tcpEndPoint;
            
            readingScpBody_ = false;
            readData(bufferScpHdr_, socket, funcSCPRead_);
            isScpConnected_ = true;
        } return true;

        case Protocols::RDB_TCP:
        {
            setCallbackReadRDB(boost::bind(&TcpPort::OnReceiveRDB
                                , this, boost::asio::placeholders::error
                                , handle));
            setCallbackWriteRDB(boost::bind(&TcpPort::OnSendRDB
                                            , this, boost::asio::placeholders::error
                                            , handle));
            readingRdbBody_ = false;
            readData(bufferRDBHdr_, socket, funcRDBRead_);
            
        } return true;
    }

    return false;
}
}
