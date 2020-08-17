#include "tcpServer.hpp"
#include "exceptions.hpp"
#include <sys/time.h>
#include <sys/select.h>
using namespace exceptions;

namespace kokfikoCDR {

TcpServer::TcpServer()
: m_socket()
, m_masterfd()
, m_watchingfd()
{
    setSocket();
    bindSocket();
    listenSocket();
    FD_SET(m_socket.GetSocketNumber(), &m_masterfd);
    FD_ZERO(&m_masterfd);
}

int TcpServer::WaitForMessage() {
    FD_SET(m_socket.GetSocketNumber(), &m_masterfd);
    m_watchingfd = m_masterfd;
    return select(NUM_OF_SOCKETS, &m_watchingfd, 0, 0, 0);
}

int TcpServer::GetSocketConnection(int& a_activity) {
    if(FD_ISSET(m_socket.GetSocketNumber(), &m_masterfd) && MAX_CLIENTS > m_clients.size()) {
        struct sockaddr_in sin;
        socklen_t addrLen = sizeof(sin);
        return accept(m_socket.GetSocketNumber(),reinterpret_cast<struct sockaddr*>(&sin), &addrLen);
    }
    return -1;
}

void TcpServer::GetData(char* a_buffer, size_t a_bufferSize, int a_clientSocket) {
    if(FD_ISSET(a_clientSocket, &m_watchingfd)) {
        m_socket.RecvMessage(a_clientSocket, a_buffer, a_bufferSize);
    }
}

// private functions

void TcpServer::setSocket() {
    int optval = 1;
    if (setsockopt(m_socket.GetSocketNumber(), SOL_SOCKET, SO_REUSEADDR,&optval, sizeof(optval)) < 0) {
		throw ExcSetSocketFailed();
	}
}

void TcpServer::bindSocket() {
    int status = bind(m_socket.GetSocketNumber(), reinterpret_cast<struct sockaddr*>(&m_socket.GetSocketAddr()), sizeof(m_socket.GetSocketAddr()));
    if (0 > status) {
		throw ExcServerBindFailed();
	}
}

void TcpServer::listenSocket() {
    int status = listen(m_socket.GetSocketNumber(), NUM_OF_CLIENTS);
	if(0 > status) {
		throw ExcServerListenFailed();
	}
}

} // kokfikoCDR