#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>

#include <iostream>
#include <unistd.h>

using namespace VTD;

namespace
{
    // default host local ip where VTD is running
    const std::string DEFAULT_HOST = "127.0.0.1";
}

class ScpCallback : public Message<MESSAGE_SCP>
{
public:
    virtual void operator() (const ReceiveSCP* receiveSCP)
    {
        //std::cout << msg.getHeaderData() << ": " << msg->getDataString() << std::endl << "###############################################" << std::endl;

        // due to compiler optimizations in release builds the header has to be copied
        const SCP_MSG_HDR_t msgHdr = *(reinterpret_cast<const SCP_MSG_HDR_t*>(receiveSCP->getHeaderData().data()));
        std::cout<< "  sender: " << msgHdr.sender << "  receiver: " << msgHdr.receiver  << std::endl << "###############################################" << std::endl;
    }
};

/**
 * This sample showcases the use of the EventCallbackBase class to receive Scp (or RDB) messages
 * and print them to stdout.
 */
int main()
{
    ScpCallback callback;

    VtdApi api;

    ConnectionHandle handle = 0;

    handle = api.connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);

    if (handle == 0)
    {
            std::cout << "SCP Connection Failed." << std::endl;
            std::cout << "Start VTD with Standard setup and sample project" << std::endl;
            exit(1);
    }

    api.registerEventFunc<ScpCallback, ReceiveSCP>(&callback, &ScpCallback::operator(), handle);

    boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));

    while (api.isConnected(handle))
    {
        api.update();
    }

    api.deregisterEventFunc<ScpCallback, ReceiveSCP>(&callback, &ScpCallback::operator(), handle);

    std::cout << "Exiting..." << std::endl;

    api.disconnectSCP(handle);

    return 0;
}
