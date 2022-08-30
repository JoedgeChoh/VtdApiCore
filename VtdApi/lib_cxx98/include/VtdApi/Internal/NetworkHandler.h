#ifndef VTDAPI_NETWORKHANDLER_H
#define VTDAPI_NETWORKHANDLER_H

#include <VtdApi/IVtdApi.h>

#include <CallbackIface.hh>
#include <NetPackage.hh>

#include <VtdToolkit/scpIcd.h>
#include <VtdThreads/CriticalSection.h>


#include <sigslot/sigslot.h>

namespace VTD {

#ifndef VTD_API_BOOST
class ConnectionEvent;

namespace Internal {

typedef IVtdApi::ConnectionHandle ConnectionHandle;

/**
 * @brief Threadsafe network handler singleton.
 * Thread safety is bound to the condition that the underlying ComHandler singleton is not used directly.
 */
class NetworkHandler : public Com::CallbackIface, public sigslot::has_signals<NetworkHandler>
{
public:
    typedef Com::CallbackIface Base;

    static NetworkHandler* getInstance();
    virtual ~NetworkHandler();

    ConnectionHandle connect(const std::string& address, UInt port, VTD::IVtdApi::Protocol::Enum protocol);

    /**
     * @brief disconnectSCP - close SCP connection
     * @param handle - the connection handle to which the messages shall be sent.
     */
    void disconnectSCP(ConnectionHandle& handle);

    /**
     * @brief disconnectRDB - close RDB connection
     * @param handle - the connection handle to which the messages shall be sent.
     */
    void disconnectRDB(ConnectionHandle& handle);

    void update();

    bool writeRdb(const ConnectionHandle& handle, RDB_MSG_t* message);
    bool writeScp(const ConnectionHandle& handle, SCP_MSG_HDR_t* message, size_t totalSize);
    bool isConnected(const ConnectionHandle& handle);

    virtual void incomingPackage(const Com::NetPackage& netPkg, const std::string& partner) VTD_OVERRIDE;

    template<class T> void registerForRdb(T* obj, void (T::*function)(RDB_MSG_t*, size_t, const std::string&)) {
        rdbMessageSignal_.connect(obj, function);
    }

    template<class T> void registerForScp(T* obj, void (T::*function)(SCP_MSG_HDR_t*, void*, const std::string&)) {
        scpMessageSignal_.connect(obj, function);
    }

    template<class T> void registerForConnectionEvent(T* obj, void (T::*function)(ConnectionEvent*)) {
        connectionStateSignal_.connect(obj, function);
    }

private:
    struct ConnectionState {
        bool isConnected;
    };
    typedef std::map<ConnectionHandle, ConnectionState> ConnectionStateMap;

    static Com::ComHandler* comHandler_;
    CriticalSection cs_;
    sigslot::signal<RDB_MSG_t*, size_t, const std::string&> rdbMessageSignal_;
    sigslot::signal<SCP_MSG_HDR_t*, void*, const std::string&> scpMessageSignal_;
    sigslot::signal<ConnectionEvent*> connectionStateSignal_;
    ConnectionStateMap scpConnectionStates_; ///< keep connection states for SCP protocol only.

    NetworkHandler();

    void handleSCPMessage(void* data, size_t size, const std::string& partner);
    void handleMessage(void* data, size_t size, int protocol,  const std::string& partner);

    static UInt generateHandle(const std::string& hostname, unsigned int port, VTD::IVtdApi::Protocol::Enum protocol);
};

} //namespace Internal
#endif
} //namespace VTD

#endif //VTDAPI_NETWORKHANDLER_H
