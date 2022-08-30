#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <poll.h>

#include <VtdNetwork/Socket.h>
#include <VtdCore/Logging/Log.h>

namespace VTD {

Socket::Socket(const std::string& hostname, unsigned int port) :
    m_hostname(hostname),
    m_port(port),
    m_client(-1)
{/**/}

Socket::~Socket()
{
    close();
}

bool Socket::connect()
{
    const char* hostname = m_hostname.c_str();
    unsigned int port = m_port;
    
    struct sockaddr_in server;
    struct hostent* host = NULL;

    // Create the socket, and attempt to connect to the server
    int client = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (client == -1) {
        VTD_LOG_ERRNO("VtdToolkit: socket failed:");
        return false;
    }

    int opt = 1;
    ::setsockopt(client, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));

    server.sin_family      = AF_INET;
    server.sin_port        = htons(static_cast<uint16_t>(port));
    server.sin_addr.s_addr = ::inet_addr(hostname);

    // If the supplied server address wasn't in the form
    // "aaa.bbb.ccc.ddd" it's a hostname, so try to resolve it
    if (server.sin_addr.s_addr == INADDR_NONE) {
        host = ::gethostbyname(hostname);
        if (host == NULL) {
            VTD_LOG_ERR("VtdToolkit: gethostbyname(): Unable to resolve server " << hostname);
            return false;
        }
        memcpy( &server.sin_addr, host->h_addr_list[0], host->h_length );
    }

    if ( ::connect( client, (struct sockaddr *)&server, sizeof( server ) ) == -1 ) {
        VTD_LOG_ERRNO("VtdToolkit: Connect failed:");
        ::close(client);
        return false;
    }
    m_client = client;
    return true;
}

void Socket::close()
{
    ::close(m_client);
    m_client = -1;
}

bool Socket::send(const unsigned char *data, size_t size) {

    std::ptrdiff_t retVal = ::send(m_client, data, size, MSG_NOSIGNAL);
    if (retVal == -1) {
        VTD_LOG_ERRNO("VtdToolkit: Could not send data on socket:");
        return false;
    }
    return true;
}

std::ptrdiff_t Socket::receive(unsigned char *data, size_t size, bool isBlocking) {

    int flags = MSG_NOSIGNAL | ((isBlocking) ? 0x0 : MSG_DONTWAIT);
    std::ptrdiff_t retVal = ::recv(m_client, data, size, flags);
    if (retVal == -1) {
        VTD_LOG_ERRNO("VtdToolkit: Could not receive data on socket:");
    }
    return retVal;
}

std::ptrdiff_t Socket::peek(unsigned char *data, size_t size,  bool isBlocking) {

    int flags = MSG_PEEK | MSG_NOSIGNAL | ((isBlocking) ? 0x0 : MSG_DONTWAIT);
    std::ptrdiff_t retVal = ::recv(m_client, data, size, flags);
    if (retVal == -1) {
        VTD_LOG_ERRNO("VtdToolkit: Could not receive data on socket:");
    }
    return retVal;
}

bool Socket::hasData() {
    struct pollfd fd;
    fd.fd = m_client;
    fd.events = POLLIN;
    int retVal = poll(&fd, 1, 0);
    if (retVal == -1) {
        VTD_LOG_ERRNO("VtdToolkit: Could not poll data on socket:");
    }
    return retVal > 0;
}

} //namespace VTD
