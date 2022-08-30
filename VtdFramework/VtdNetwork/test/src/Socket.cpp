#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <boost/asio.hpp>
#include <VtdNetwork/message.h>
#include <VtdNetwork/tcp_port.h>

// NOTE:
// This is not a proper, self-contained unit test. It requires a running VTD instance on localhost.
// A proper fix would require rewriting the VtdNetwork classes to use dependency injection,
// so that the boost asio communication classes could be replaced with mocks.
// The next best thing would be to have the test start up its own fake VTD server and send the expected responses.
// This is how it's done for readMessageSplitOverMTUs.

const std::string DEFAULT_HOST = "127.0.0.1";

using namespace VTD;

struct MyClassTestTCP : public ::testing::Test
{
    bool isReceiveScp_;
    bool isReceiveRdb_;
    bool isSendScp_;
    bool isSendRdb_;

    TcpPort *tcpPort;

    void SetUp()
    {
        isReceiveScp_ = false;
        isReceiveRdb_ = false;
        isSendScp_ = false;
        isSendRdb_= false;
        tcpPort = new TcpPort();
    }
    void TearDown(){delete tcpPort;}

    void OnReceiveScp(const boost::system::error_code& ErrorCode, ConnectionHandle& handle)
    {
        isReceiveScp_ = true;
    }

    void OnReceiveRdb(const boost::system::error_code& ErrorCode, ConnectionHandle& handle)
    {
        isReceiveRdb_ = true;
    }

    void OnSendScp(const boost::system::error_code& ErrorCode, ConnectionHandle& handle)
    {
        isSendScp_ = true;
    }

    void OnSendRdb(const boost::system::error_code& ErrorCode, ConnectionHandle& handle)
    {
        isSendRdb_ = true;
    }


};

TEST_F(MyClassTestTCP, connectTCP_RDB)
{
   ConnectionHandle handle = 0;
   tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP, handle);
   ASSERT_NE(handle, 0);
}

TEST_F(MyClassTestTCP, connectTCP_SCP)
{
   ConnectionHandle handle = 0;
   tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_SCP_PORT, Protocols::SCP, handle);
   ASSERT_NE(handle, 0);
}

TEST_F(MyClassTestTCP, connectTCP_RDB_SCP)
{
   ConnectionHandle handleRdb = 0, handleScp = 0;
   tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP, handleRdb);
   tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_SCP_PORT, Protocols::SCP, handleScp);
   ASSERT_NE(handleRdb, 0);
   ASSERT_NE(handleScp, 0);
}

TEST_F(MyClassTestTCP, isConnectTCP_RDB)
{
   ConnectionHandle handle = 0;
   tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP, handle);
   ASSERT_TRUE(tcpPort->isConnected(handle));
}

TEST_F(MyClassTestTCP, isConnectTCP_SCP)
{
   ConnectionHandle handle = 0;
   tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_SCP_PORT, Protocols::SCP, handle);
   ASSERT_TRUE(tcpPort->isConnected(handle));
}

TEST_F(MyClassTestTCP, isConnectTCP_RDB_SCP)
{
   ConnectionHandle handleRdb = 0, handleScp = 0;
   tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP, handleRdb);
   tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_SCP_PORT, Protocols::SCP, handleScp);
   ASSERT_TRUE(tcpPort->isConnected(handleRdb));
   ASSERT_TRUE(tcpPort->isConnected(handleScp));
}

TEST_F(MyClassTestTCP, disconnectTCP_RDB)
{
   ConnectionHandle handle = 0;
   tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP, handle);
   tcpPort->disconnect(handle);
   ASSERT_EQ(handle, 0);
}

TEST_F(MyClassTestTCP, disconnectTCP_SCP)
{
   ConnectionHandle handle = 0;
   tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_SCP_PORT, Protocols::SCP, handle);
   tcpPort->disconnect(handle);
   ASSERT_EQ(handle, 0);
}

TEST_F(MyClassTestTCP, receivingDataScp)
{
    ConnectionHandle handle = 0;
    tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_SCP_PORT, Protocols::SCP, handle);
    tcpPort->setCallbackReadSCP(boost::bind(&MyClassTestTCP::OnReceiveScp, this, boost::asio::placeholders::error, handle));
    tcpPort->startReading();
    EXPECT_TRUE(isReceiveScp_);
}

TEST_F(MyClassTestTCP, receivingDataRdb)
{
    ConnectionHandle handle = 0;
    tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP, handle);
    tcpPort->setCallbackReadRDB(boost::bind(&MyClassTestTCP::OnReceiveRdb, this, boost::asio::placeholders::error, handle));
    tcpPort->startReading();
    EXPECT_TRUE(isReceiveRdb_);
}

TEST_F(MyClassTestTCP, receivingDataRdbScp)
{
   ConnectionHandle handleRdb = 0, handleScp = 0;
   tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP, handleRdb);
   tcpPort->setCallbackReadRDB(boost::bind(&MyClassTestTCP::OnReceiveRdb, this, boost::asio::placeholders::error, handleRdb));
   tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_SCP_PORT, Protocols::SCP, handleScp);
   tcpPort->setCallbackReadSCP(boost::bind(&MyClassTestTCP::OnReceiveScp, this, boost::asio::placeholders::error, handleScp));
   tcpPort->startReading();
   EXPECT_TRUE(isReceiveRdb_);
   EXPECT_TRUE(isReceiveScp_);
}

TEST_F(MyClassTestTCP, sendAndReceiveDataScp)
{
    std::string test = "";
    ConnectionHandle handle = 0;
    tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_SCP_PORT, Protocols::SCP, handle);
    tcpPort->setCallbackWriteSCP(boost::bind(&MyClassTestTCP::OnSendScp, this, boost::asio::placeholders::error, handle));
    tcpPort->setCallbackReadSCP(boost::bind(&MyClassTestTCP::OnReceiveScp, this, boost::asio::placeholders::error, handle));
    tcpPort->writeScpData(test, handle);
    tcpPort->startReading();
    EXPECT_TRUE(isSendScp_);
}

TEST_F(MyClassTestTCP, sendAndReceiveDataRdb)
{
    std::vector<char> test (10,0);
    ConnectionHandle handle = 0;
    tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP, handle);
    tcpPort->setCallbackWriteRDB(boost::bind(&MyClassTestTCP::OnSendRdb, this, boost::asio::placeholders::error, handle));
    tcpPort->setCallbackReadRDB(boost::bind(&MyClassTestTCP::OnReceiveRdb, this, boost::asio::placeholders::error, handle));
    tcpPort->writeRDBData(test, handle);
    tcpPort->startReading();
    EXPECT_TRUE(isSendRdb_);
}

TEST_F(MyClassTestTCP, sendAndReceiveDataRdbScp)
{
    std::vector<char> testRdb (10,0);
    std::string test = "";
    ConnectionHandle handleRdb = 0, handleScp = 0;
    tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP, handleRdb);
    tcpPort->setCallbackWriteRDB(boost::bind(&MyClassTestTCP::OnSendRdb, this, boost::asio::placeholders::error, handleRdb));
    tcpPort->setCallbackReadRDB(boost::bind(&MyClassTestTCP::OnReceiveRdb, this, boost::asio::placeholders::error, handleScp));
    tcpPort->writeRDBData(testRdb, handleRdb);
    tcpPort->connectToPort(DEFAULT_HOST, DEFAULT_SCP_PORT, Protocols::SCP, handleScp);
    tcpPort->setCallbackWriteSCP(boost::bind(&MyClassTestTCP::OnSendScp, this, boost::asio::placeholders::error, handleScp));
    tcpPort->setCallbackReadSCP(boost::bind(&MyClassTestTCP::OnReceiveScp, this, boost::asio::placeholders::error, handleScp));
    tcpPort->writeScpData(test, handleScp);
    tcpPort->startReading();
    EXPECT_TRUE(isSendRdb_);
    EXPECT_TRUE(isSendScp_);
    EXPECT_TRUE(isReceiveRdb_);
    EXPECT_TRUE(isReceiveScp_);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Copied from boost tutorial (https://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/tutorial/tutdaytime3/src.html) and adapted
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/
using boost::asio::ip::tcp;

class tcp_connection
  : public boost::enable_shared_from_this<tcp_connection>
{
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new tcp_connection(io_service));
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void sendAsync(std::vector<char> message)
  {
    boost::asio::async_write(socket_, boost::asio::buffer(message),
        boost::bind(&tcp_connection::handle_write, shared_from_this(),
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

private:
  tcp_connection(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  void handle_write(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
      if (error)
      {
          std::cerr << "VtdNetwork: Write error: " << error.message() << std::endl;
      }
  }

  tcp::socket socket_;
  std::string message_;
};

class tcp_server
{
public:
  tcp_server(boost::asio::io_service& io_service, const std::string& host, unsigned short port)
    : acceptor_(io_service, tcp::endpoint(boost::asio::ip::address::from_string(host), port))
  {
    start_accept();
  }

  void sendAsync(std::vector<char> message) {
      if (connection_) {
          connection_->sendAsync(message);
      } else {
          std::cerr << "VtdNetwork: No connection to send on" << std::endl;
      }
  }
  
private:
  void start_accept()
  {
    tcp_connection::pointer new_connection =
      tcp_connection::create(acceptor_.get_io_service());

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&tcp_server::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
  }

  void handle_accept(tcp_connection::pointer new_connection,
      const boost::system::error_code& error)
  {
    connection_ = new_connection;
    start_accept();
  }

  tcp::acceptor acceptor_;
  tcp_connection::pointer connection_;
};

void runIoService(boost::asio::io_service& io_service)
{
    io_service.run();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// End copied/adapted from boost
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct ReceiveRDBFixture : public MyClassTestTCP
{
public:
    void CbReceiveRDB(const ReceiveRDB* receiveRDB)
    {
        isReceiveRdb_ = true;
        received_ = receiveRDB->data_;
        
        tcpPort->stopReading();
    }
    void registerCb(const ConnectionHandle& handle)
    {
        tcpPort->registerEventFunc(this, &ReceiveRDBFixture::CbReceiveRDB, handle);
    }
    void deregisterCb(const ConnectionHandle& handle)
    {
        tcpPort->deregisterEventFunc(this, &ReceiveRDBFixture::CbReceiveRDB, handle);
    }
    void OnReceiveRdb(const boost::system::error_code& ErrorCode, ConnectionHandle& handle)
    {
        tcpPort->OnReceiveRDB(ErrorCode, handle);
        tcpPort->update();
    }
protected:
    boost::asio::io_service io_service;
    std::vector<char> received_;
};

void sendMessages(tcp_server& server, std::vector<std::vector<char>> messages, uint32_t msToWaitBetween)
{
    std::vector<std::vector<char>>::const_iterator it;
    for (it = messages.begin(); it != messages.end(); ++it)
    {
        server.sendAsync(*it);
        boost::this_thread::sleep_for(boost::chrono::milliseconds(msToWaitBetween));
    }
}

TEST_F(ReceiveRDBFixture, readMessageSplitOverMTUs)
{
    const unsigned short port = RDB_DEFAULT_PORT + 1000;  // Add offset so as not to collide with the running VTD required by test cases above

    tcp_server server(io_service, DEFAULT_HOST, port);

    boost::thread t(boost::bind(&runIoService, boost::ref(io_service)));
    boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
    ConnectionHandle handle = 0;
    tcpPort->connectToPort(DEFAULT_HOST, port, Protocols::RDB_TCP, handle);
    ASSERT_NE(handle, 0);
    registerCb(handle);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(5));  // Wait to make sure the connection is up and ready to send on
    const uint32_t dataSize = 2000;
    const uint32_t mtuPayload = 1460;
    std::vector<char> fullMessage;
    std::vector<char> message1;
    std::vector<char> message2;
    RDB_MSG_HDR_t hdr;
    hdr.magicNo = RDB_MAGIC_NO;
    hdr.version = RDB_VERSION;
    hdr.headerSize = sizeof hdr;
    hdr.dataSize = dataSize;
    hdr.frameNo = 0;
    hdr.simTime = 0.0;
    
    const char* p = reinterpret_cast<const char*>(&hdr);
    std::copy(p, p + sizeof hdr, std::back_inserter(fullMessage));
    size_t n;
    for (n = 0; n < dataSize; ++n) {
        fullMessage.push_back(n%256);
    }
    message1.insert(message1.end(), fullMessage.begin(), fullMessage.begin() + mtuPayload);
    message2.insert(message2.end(), fullMessage.begin() + mtuPayload, fullMessage.end());
    std::vector<std::vector<char>> messages;
    messages.push_back(message1);
    messages.push_back(message2);

    boost::thread t2(boost::bind(&sendMessages, boost::ref(server), messages, 10));

    tcpPort->setCallbackReadRDB(boost::bind(&ReceiveRDBFixture::OnReceiveRdb, this, boost::asio::placeholders::error, handle));
    tcpPort->startReading();
    EXPECT_TRUE(isReceiveRdb_);
    EXPECT_THAT(received_, ::testing::ElementsAreArray(fullMessage));
    deregisterCb(handle);
    io_service.stop();
    t.join();
    t2.join();
}

struct ReceiveSCPFixture : public MyClassTestTCP
{
public:
    void CbReceiveSCP(const ReceiveSCP* receiveSCP)
    {
        isReceiveScp_ = true;
        received_.push_back(receiveSCP->getDataString());
        
        if (--numScpToRead_ == 0)
        {
            tcpPort->stopReading();
        }
    }
    void registerCb(const ConnectionHandle& handle)
    {
        tcpPort->registerEventFunc(this, &ReceiveSCPFixture::CbReceiveSCP, handle);
    }
    void deregisterCb(const ConnectionHandle& handle)
    {
        tcpPort->deregisterEventFunc(this, &ReceiveSCPFixture::CbReceiveSCP, handle);
    }
    void OnReceiveScp(const boost::system::error_code& ErrorCode, ConnectionHandle& handle)
    {
        tcpPort->OnReceiveSCP(ErrorCode, handle);
    }
protected:
    boost::asio::io_service  io_service;
    int                      numTcpReads_;
    int                      numScpToRead_;
    std::vector<std::string> received_;
};

// Delay call to update() until both SCPs have been queued
void callTcpUpdateAfterSleep(TcpPort& tcpPort, uint32_t msToWait)
{
    boost::this_thread::sleep_for(boost::chrono::milliseconds(msToWait));
    tcpPort.update();
}

TEST_F(ReceiveSCPFixture, readQueuedScpInCorrectOrder)
{
    const unsigned short port = SCP_DEFAULT_PORT + 1000;  // Add offset so as not to collide with the running VTD required by test cases above
    numScpToRead_ = 2;
    numTcpReads_ = 2*numScpToRead_-1;

    tcp_server server(io_service, DEFAULT_HOST, port);

    boost::thread t(boost::bind(&runIoService, boost::ref(io_service)));
    boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
    ConnectionHandle handle = 0;
    tcpPort->connectToPort(DEFAULT_HOST, port, Protocols::SCP, handle);
    ASSERT_NE(handle, 0);
    registerCb(handle);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(5));  // Wait to make sure the connection is up and ready to send on
    std::vector<char> message;
    SCP_MSG_HDR_t hdr;
    hdr.magicNo = SCP_MAGIC_NO;
    hdr.version = SCP_VERSION;
    strncpy(hdr.sender, "server", sizeof hdr.sender);
    strncpy(hdr.receiver, "test", sizeof hdr.receiver);
    hdr.dataSize = 1;
    
    const char* p = reinterpret_cast<const char*>(&hdr);
    std::copy(p, p + sizeof hdr, std::back_inserter(message));
    message.push_back('1');
    std::copy(p, p + sizeof hdr, std::back_inserter(message));
    message.push_back('2');

    server.sendAsync(message);
    boost::thread t2(boost::bind(&callTcpUpdateAfterSleep, boost::ref(*tcpPort), 3));

    tcpPort->setCallbackReadSCP(boost::bind(&ReceiveSCPFixture::OnReceiveScp, this, boost::asio::placeholders::error, handle));
    tcpPort->startReading();
    EXPECT_TRUE(isReceiveScp_);
    ASSERT_EQ(received_.size(), 2);
    EXPECT_EQ(received_.front(), std::string("1"));
    EXPECT_EQ(received_.back(), std::string("2"));
    deregisterCb(handle);
    io_service.stop();
    t.join();
}
