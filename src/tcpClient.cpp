#include "tcpClient.hpp"
#include "exceptions.hpp"
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <cassert>
using namespace exceptions;

static const int PORT = 1234;
static const char* IP_ADDR = "127.0.0.1";

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

TcpClient::TcpClient()
: m_socket()
, m_servAddr() {
    createSockerAddr();
    connectToServer();
}

void TcpClient::SendMessage(const char* a_msg) const {
    ssize_t status = send(m_socket.GetSocketNumber() , a_msg, strlen(a_msg), 0);
    if(0 > status) {
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

// private functions:

void TcpClient::createSockerAddr() {
    memset(&m_servAddr,0,sizeof(m_servAddr));
    
    m_servAddr.sin_family = AF_INET;
    m_servAddr.sin_addr.s_addr = inet_addr(IP_ADDR);
    m_servAddr.sin_port = htons(PORT);
}

void TcpClient::connectToServer() {
    int status = connect(m_socket.GetSocketNumber(), (struct sockaddr *)&m_servAddr, sizeof(m_servAddr));
    if(0 > status) {
        CheckErrno();
        // no:
        // EPERM
        // EADDRINUSE
        // EADDRNOTAVAIL
        // EAFNOSUPPORT
        // ECONNREFUSED
        // EINPROGRESS
        // ENETUNREACH
        // EPROTOTYPE
        // ETIMEDOUT
        assert(!"undocumented error for connect!");
    }
}

} // kokfikoCDR