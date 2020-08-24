#include "tcpClient.hpp"
#include "exceptions.hpp"
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <cassert>
using namespace exceptions;

namespace kokfikoCDR {

static void CheckErrno() {
    assert(EACCES != errno);
    assert(EAGAIN != errno);
    assert(EALREADY != errno);
    assert(EBADF != errno);
    assert(EFAULT != errno);
    assert(EISCONN != errno);
    assert(ENOTSOCK != errno);

    if(EINTR == errno) {
        throw ExcSignalOccurred();
    }
}

TcpClient::TcpClient(const char* a_ipAddress, size_t a_port)
: m_socketNum(openSocket())
, m_servAddr()
, m_isConnected(false)
{
    createSocketAddr(a_ipAddress, a_port);
}

TcpClient::TcpClient(int a_socketNum)
: m_socketNum(a_socketNum)
, m_isConnected(true)
{
}

TcpClient::~TcpClient() {
    int status = close(m_socketNum);
    assert(0 == status);
}

void TcpClient::ConnectToServer() {
    int status = connect(m_socketNum, reinterpret_cast<struct sockaddr*>(&m_servAddr), sizeof(m_servAddr));
    if(0 > status) {
       throw ExcConnetionFailed();
    }
    m_isConnected = true;
}

void TcpClient::SendMessage(const char* a_msg) const {
    if(!m_isConnected) {
        throw ExcCantSendNotConnected();
    }
    ssize_t sentBytes = send(m_socketNum, a_msg, strlen(a_msg), 0);
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
            throw ExcConnectionReset();
        }
        if(ENOMEM == errno) {
            throw ExcNoMemory();
        }
        if(EPIPE == errno) {
            throw ExcLocalHasBeenShutDown();
        }
        assert(!"undocumented error for send!");
    }
}

void TcpClient::RecvMessage(char* a_msg, size_t a_msgSize) {
    ssize_t readBytes = recv(m_socketNum, a_msg, a_msgSize, 0);
    if(0 == readBytes) {
        throw ExcSocketIsClosed();
    }
    if(0 > readBytes) {
        throw ExcRecieveFailed();
    }

    a_msg[readBytes] = '\0';
}

int TcpClient::GetSocketNumber() const {
    return m_socketNum;
}

struct sockaddr_in TcpClient::GetSocketAddr() const {
    return m_servAddr;
}

// private functions:

int TcpClient::openSocket() {
    int socketNum = socket(AF_INET, SOCK_STREAM, 0);
    if(socketNum < 0) {
        assert(EINVAL != errno);
        assert(EAFNOSUPPORT != errno);
        assert(EPROTONOSUPPORT != errno);

        if(EACCES == errno) {
            throw ExcPermissionDenied();
        }
        if(EMFILE == errno) {
            throw ExcDescriptorTableFull();
        }
        if(ENOBUFS == errno || ENOMEM == errno) {
            throw ExcNotEnoughSpace();
        }
        assert(!"undocumented error for socket!");
    }
    return socketNum;
}

void TcpClient::createSocketAddr(const char* a_ipAddress, size_t a_port) {
    memset(&m_servAddr,0,sizeof(m_servAddr));
    
    m_servAddr.sin_family = AF_INET;
    m_servAddr.sin_addr.s_addr = inet_addr(a_ipAddress);
    m_servAddr.sin_port = htons(a_port);
}

} // kokfikoCDR