#include <VtdApi/VtdApi.h>
#include <gtest/gtest.h>

#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>

#include <cstdio>

namespace
{
    std::string g_command_line_arg;
}

using namespace VTD;

class RdbReceiverMock {
public:
    RdbReceiverMock(VtdApi* vtdApi, const ConnectionHandle& scpHandle, const ConnectionHandle& rdbHandle)
        : vtdApi_ (vtdApi)
        , scpHandle_ (scpHandle)
        , rdbHandle_ (rdbHandle)
        , isScpReceived_ (false)
        , isRdbReceived_ (false)
    {
        vtdApi_->registerEventFunc<RdbReceiverMock, ReceiveRDB>(this, &RdbReceiverMock::handleRdbMessage, rdbHandle_);
        vtdApi_->registerEventFunc<RdbReceiverMock, ReceiveSCP>(this, &RdbReceiverMock::handleScpMessage, scpHandle_);
    }

    ~RdbReceiverMock()
    {
        vtdApi_->deregisterEventFunc<RdbReceiverMock, ReceiveRDB>(this, &RdbReceiverMock::handleRdbMessage, rdbHandle_);
        vtdApi_->deregisterEventFunc<RdbReceiverMock, ReceiveSCP>(this, &RdbReceiverMock::handleScpMessage, scpHandle_);
    }

    void handleRdbMessage(const ReceiveRDB* msg)
    {
        unsigned int noElements = 0;
        RDB_OBJECT_STATE_t* objState = reinterpret_cast<RDB_OBJECT_STATE_t*> (Framework::RDBHandler::getFirstEntry(&msg->getData(), RDB_PKG_ID_OBJECT_STATE, noElements, true));

        if (!noElements) return;

        if (!isRdbReceived_)
            isRdbReceived_ = true;

        while ( noElements )
        {
            if (noElements--) {
                ++objState;
            }
        }
     }

    void handleScpMessage(const ReceiveSCP* msg)
    {        
        if (!isScpReceived_)
            isScpReceived_ = true;

        SCP_MSG_HDR_t* header = reinterpret_cast<SCP_MSG_HDR_t*>(msg->getHeaderData().data());
        std::cout << header->sender << ": " << msg->getDataString() << std::endl << "###############################################" << std::endl;
    }

    const bool getIsRdbReceived () const { return isRdbReceived_; }
    const bool getIsScpReceived () const { return isScpReceived_; }

private:
    VtdApi* vtdApi_;
    ConnectionHandle scpHandle_;
    ConnectionHandle rdbHandle_;
    bool isScpReceived_, isRdbReceived_;

};

class MyTestEnvironment : public testing::Environment {
 public:
  explicit MyTestEnvironment(const std::string &command_line_arg) {
    g_command_line_arg = command_line_arg;
  }
};

