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
: m_socketNum(openSocket())
{
    setSocket();
    bind(a_ipAddr, a_port);
    listen();
}

ServerTcp::~ServerTcp()
{
    int status = ::close(m_socketNum);
    assert(0 == status);
}

int ServerTcp::SetConnection()
{
    struct sockaddr_in sin;
    socklen_t addrLen = sizeof(sin);
    int clientSocket = accept(m_socketNum,reinterpret_cast<struct sockaddr*>(&sin), &addrLen);
    if(0 > clientSocket) {
        throw runtime_error(""); // LOG FILE
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
        if(EACCES == errno) {
            throw runtime_error("Connection reset!"); /// LOG FILE
        }
        if(EMFILE == errno) {
            throw runtime_error("No memory available!"); /// LOG FILE
        }
        if(ENOBUFS == errno || ENOMEM == errno) { /// LOG FILE
            throw runtime_error("The local end has been shut down on a connection oriented socket!");
        }
        assert(!"undocumented error for socket!");
    }

    return socketNum;
}

void ServerTcp::setSocket()
{
    int optval = 1;
    if (::setsockopt(m_socketNum, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        throw runtime_error(""); /// LOG FILE
    }
}

void ServerTcp::bind(const string& a_ipAddr, size_t a_port)
{
    struct sockaddr_in srvAddr;
	
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = inet_addr(a_ipAddr.c_str());
	srvAddr.sin_port = htons(a_port);

    int status = ::bind(m_socketNum, reinterpret_cast<struct sockaddr*>(&srvAddr), sizeof(srvAddr));
    if (0 > status) {
        throw runtime_error(""); /// LOG FILE
    }
}

void ServerTcp::listen()
{
    int status = ::listen(m_socketNum, NUM_OF_CLIENTS);
    if(0 > status) {
        throw runtime_error(""); /// LOG FILE
    }
} 

} // experis