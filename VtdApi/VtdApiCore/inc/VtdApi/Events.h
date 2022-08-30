#ifndef VTDAPI_EVENTS_H
#define VTDAPI_EVENTS_H

#include <VtdApi/IVtdApi.h>

#include <VtdCore/EventHandler.h>
#include <VtdToolkit/scpIcd.h>
#include <VtdToolkit/viRDBIcd.h>

#include <cstring>
#include <cstdlib>

namespace VTD {
#ifndef VTD_API_BOOST
class ScpMessage : public Event {
public:
    ScpMessage(const SCP_MSG_HDR_t& header, const std::string& msgStr)
        : header_(header)
        , msgStr_(msgStr)
    { /**/ }

    const std::string& getDataString() const { return msgStr_; }
    const SCP_MSG_HDR_t& getHeader() const { return header_; }

private:
    SCP_MSG_HDR_t header_;
    std::string msgStr_;
};

class RdbMessage : public Event {
public:
    RdbMessage(const RDB_MSG_t& msg, size_t size)
        : msgSize_(size)
    {
        msgData_ = std::malloc(size);
        if (!msgData_)
                std::abort();

        std::memcpy(msgData_, &msg, size);
    }

    ~RdbMessage(void)
    {
        std::free(msgData_);
    }

    const RDB_MSG_t& getData() const { return *reinterpret_cast<RDB_MSG_t*>(msgData_); }
    const size_t getSize() const { return msgSize_; }

private:
    void* msgData_;
    size_t msgSize_;
};
#endif
}//namespace VTD

#endif //VTDAPI_EVENTS_H
