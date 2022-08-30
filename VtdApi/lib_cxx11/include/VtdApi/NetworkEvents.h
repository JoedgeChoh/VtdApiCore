#ifndef VTDAPI_NETWORK_EVENTS_H
#define VTDAPI_NETWORK_EVENTS_H

#include <VtdCore/EventHandler.h>
#include <VtdApi/IVtdApi.h>

namespace VTD {

class ConnectionEvent : public Event {
public:
    ConnectionEvent(const ConnectionHandle& handle, bool isConnected)
        : handle_(handle)
        , type_(isConnected ? CONNECT : DISCONNECT)
    { /**/ }

    enum Enum {
        UNDEFINED = 0,
        CONNECT,
        DISCONNECT
    };

    const Enum getType() const { return type_; }

private:
    ConnectionHandle handle_;
    Enum type_;
};
}//namespace VTD

#endif //VTDAPI_NETWORK_EVENTS_H
