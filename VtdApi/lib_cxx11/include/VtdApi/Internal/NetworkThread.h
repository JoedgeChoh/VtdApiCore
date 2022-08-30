#ifndef VTDAPI_NETWORKTHREAD_H
#define VTDAPI_NETWORKTHREAD_H

#include <VtdApi/IVtdApi.h>

#ifndef VTD_API_BOOST
#include <VtdThreads/CriticalSection.h>
#include <VtdThreads/Thread.h>
#endif

#include <VtdToolkit/scpIcd.h>
#include <VtdToolkit/viRDBIcd.h>

#include <map>
#include <sigslot/sigslot.h>

namespace VTD {

#ifndef VTD_API_BOOST
class ConnectionEvent;

namespace Internal {

//fwd declerations
class AsyncEventHandler;
class NetworkHandler;
typedef IVtdApi::ConnectionHandle ConnectionHandle;
typedef IVtdApi::Protocol Protocol;

/**
 * Thread class to manage connections, send outgoing packages and handle incoming packages using
 * the NetworkHandler singleton as a basis.
 */
class NetworkThread : public Thread, public sigslot::has_slots<> {
public:
    NetworkThread(Internal::AsyncEventHandler* scpHandler);
    virtual ~NetworkThread();

    ConnectionHandle connectScp(const std::string& hostname, UInt portNumber);
    ConnectionHandle connectRdb(const std::string& hostname, UInt portNumber, Protocol::Enum protocol);

    bool isConnectedScp(const ConnectionHandle& handle);
    bool isConnectedRdb(const ConnectionHandle& handle);

    /**
     * @brief disconnectScp - close SCP connection
     * @param handle -the connection handle to which the messages shall be sent.
     */

    void disconnectScp(ConnectionHandle& handle);

    void disconnectRdb(ConnectionHandle& handle);

    bool sendScpCommand(const ConnectionHandle& handle, const std::string& cmd);
    bool sendRdbMessage(const ConnectionHandle& handle, RDB_MSG_t& msg);

    /**
     * @brief stop update loop
     */
    void stop();
    bool isRunning() const { return isRunning_; }

private:
    friend class NetworkHandler;

    Internal::NetworkHandler* networkHandler_;
    Internal::AsyncEventHandler* eventHandler_;
    UInt sleepTimeMus_;
    bool isRunning_;

    void handleRdb(RDB_MSG_t* msg, size_t size, const std::string& partner);
    void handleScp(SCP_MSG_HDR_t* msg, void* data, const std::string& partner);
    void handleConnectionEvent(ConnectionEvent* event);

    virtual void run();
};

} //namespace Internal
#endif
} //namespace VTD

#endif //_VTDAPI_NETWORKTHREAD_H
