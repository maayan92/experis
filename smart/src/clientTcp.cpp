#include "clientTcp.hpp"
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <cassert>
#include <stdexcept>
using namespace std;

namespace experis { 

static void CheckErrno()
{
    assert(EACCES != errno);
    assert(EAGAIN != errno);
    assert(EALREADY != errno);
    assert(EBADF != errno);
    assert(EFAULT != errno);
    assert(EISCONN != errno);
    assert(ENOTSOCK != errno);
    
    if(EINTR == errno) {
        throw runtime_error("A signal occurred before any data was transmitted!");
    }
}

static int OpenSocket()
{
    int socketNum = socket(AF_INET, SOCK_STREAM, 0);
    if(socketNum < 0) {
        assert(EINVAL != errno);
        assert(EAFNOSUPPORT != errno);
        assert(EPROTONOSUPPORT != errno);
        if(EACCES == errno) {
            throw runtime_error("Permission to create a socket is denied!");
        }
        if(EMFILE == errno) {
            throw runtime_error("The socket descriptor table is full!");
        }
        if(ENOBUFS == errno || ENOMEM == errno) {
            throw runtime_error("The socket cannot be created until sufficient resources are freed!");
        }
        assert(!"undocumented error for socket!");
    }
    
    return socketNum;
}

ClientTcp::ClientTcp(const string& a_ipAddress, size_t a_port)
: m_socketNum(OpenSocket())
, m_servAddr()
{
    createSockerAddr(a_ipAddress, a_port);
}

ClientTcp::~ClientTcp()
{
    int status = close(m_socketNum);
    assert(0 == status);
}

void ClientTcp::ConnectToServer()
{
    int status = connect(m_socketNum, reinterpret_cast<struct sockaddr*>(&m_servAddr), sizeof(m_servAddr));
    if(0 > status) {
        CheckErrno();
        assert(!"undocumented error for connect!");
    }
}

void ClientTcp::SendMessage(const std::string& a_msg) const
{
    ssize_t sentBytes = send(m_socketNum, a_msg.c_str(), a_msg.size(), 0);
    if(0 > sentBytes) {
        CheckErrno();
        assert(EWOULDBLOCK != errno);
        assert(EDESTADDRREQ != errno);
        assert(EINVAL != errno);
        assert(EMSGSIZE != errno);
        assert(ENOBUFS != errno);
        assert(ENOTCONN != errno);
        assert(EOPNOTSUPP != errno);
        if(ECONNRESET == errno) {
            throw runtime_error("Connection reset!");
        }
        if(ENOMEM == errno) {
            throw runtime_error("No memory available!");
        }
        if(EPIPE == errno) {
            throw runtime_error("The local end has been shut down on a connection oriented socket!");
        }
        
        assert(!"undocumented error for send!");
    }
}

void ClientTcp::RecvMessage(int m_clientSocket, char* a_msg, size_t a_msgSize)
{
    ssize_t readBytes = recv(m_clientSocket, a_msg, a_msgSize, 0);
    if(0 == readBytes) {
        throw runtime_error("client socket is closed!");
    }
    if(0 > readBytes) {
        throw runtime_error("The file failed to open!");
    }
    
    a_msg[readBytes] = '\0';
}

// private functions:

void ClientTcp::createSockerAddr(const string& a_ipAddress, size_t a_port)
{
    memset(&m_servAddr,0,sizeof(m_servAddr));
    m_servAddr.sin_family = AF_INET;
    m_servAddr.sin_addr.s_addr = inet_addr(a_ipAddress.c_str());
    m_servAddr.sin_port = htons(a_port);
}

} // experis