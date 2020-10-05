#include "serverTcp.hpp"
#include <cassert>
#include <stdexcept>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>
using namespace std;

namespace experis {

ServerTcp::ServerTcp(const string& a_ipAddr, size_t a_port)
: m_logFile("server_log.txt")
, m_socketNum(openSocket())
{
    setSocket();
    bind(a_ipAddr, a_port);
    listen();
}

ServerTcp::~ServerTcp()
{
    int status = ::close(m_socketNum);
    assert(0 == status);
    LOGINFO(m_logFile, "server closed");
}

int ServerTcp::SetConnection()
{
    struct sockaddr_in sin;
    socklen_t addrLen = sizeof(sin);
    int clientSocket = ::accept(m_socketNum,reinterpret_cast<struct sockaddr*>(&sin), &addrLen);
    if(0 > clientSocket) {
        assert(EAGAIN == errno);
        assert(EBADF == errno);
        assert(EFAULT == errno);
        assert(EINVAL == errno);
        assert(ENOTSOCK == errno);
        assert(EOPNOTSUPP == errno);
        assert(EPROTO == errno);

        switch(errno) {
            case ECONNABORTED:
                LOGINFO(m_logFile, "A connection has been aborted.");
                break;
            case EINTR:
                LOGINFO(m_logFile, "There was a signal interrupt before a valid connection arrived");
                break;
            case EMFILE:
                LOGINFO(m_logFile, "Reached the limit of open file descriptors");
                break;
            case (ENOBUFS || ENOMEM):
                LOGINFO(m_logFile, "Not enough free memory");
                break;

            default:
                LOGINFO(m_logFile, "undocumented error for accept!");
                assert(!"undocumented error for accept!");
                break;
        }
    }
    else {
        LOGINFO(m_logFile, "A connection occurred");
    }

    return clientSocket;
}

int ServerTcp::GetSockNum() const
{
    return m_socketNum;
}

// private functions:

int ServerTcp::openSocket()
{
    int socketNum = ::socket(AF_INET, SOCK_STREAM, 0);
    if(socketNum < 0) {
        assert(EINVAL != errno);
        assert(EAFNOSUPPORT != errno);
        assert(EPROTONOSUPPORT != errno);
        switch(errno) {
            case EACCES:
                LOGINFO(m_logFile, "Connection reset!");
                break;

            case EMFILE:
                LOGINFO(m_logFile, "No memory available!");
                break;

            case ENOBUFS: 
                LOGINFO(m_logFile, "The local end has been shut down on a connection oriented socket!");
                break;

            default:
                LOGINFO(m_logFile, "undocumented error for socket!");
                assert(!"undocumented error for socket!");
                break;
        }
        throw runtime_error("failed to open socket");
    }

    LOGINFO(m_logFile, "socket opened for the server");
    return socketNum;
}

void ServerTcp::setSocket()
{
    int optval = 1;
    int status = ::setsockopt(m_socketNum, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (0 > status) {
        LOGINFO(m_logFile, "Set options on the server socket failed!");
        throw runtime_error("Set options on the server socket failed!");
    }

    LOGINFO(m_logFile, "set socket options for the server");
}

void ServerTcp::bind(const string& a_ipAddr, size_t a_port)
{
    struct sockaddr_in srvAddr;
	
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = inet_addr(a_ipAddr.c_str());
	srvAddr.sin_port = htons(a_port);

    int status = ::bind(m_socketNum, reinterpret_cast<struct sockaddr*>(&srvAddr), sizeof(srvAddr));
    if (0 > status) {
        assert(EACCES == errno);
        assert(EBADF == errno);
        assert(EINVAL == errno);
        assert(ENOTSOCK == errno);

        if(EADDRINUSE == errno) {
            LOGINFO(m_logFile, "The given address is already in use!");
        }
        else {
            LOGINFO(m_logFile, "undocumented error for bind!");
            assert(!"undocumented error for bind!");
        }
        throw runtime_error("failed to bind server");
    }

    LOGINFO(m_logFile, "bind server socket");
}

void ServerTcp::listen()
{
    int status = ::listen(m_socketNum, NUM_OF_CLIENTS);
    if(0 > status) {
        assert(EBADF == errno);
        assert(ENOTSOCK == errno);
        assert(EOPNOTSUPP == errno);
        if(EADDRINUSE == errno) {
            LOGINFO(m_logFile, "Another socket is already listening on the same port!");
        }
        else {
            LOGINFO(m_logFile, "undocumented error for listen!");
            assert(!"undocumented error for listen!");
        }
        throw runtime_error("server failed to listen");
    }

    LOGINFO(m_logFile, "set server to listen for connections");
}

} // experis