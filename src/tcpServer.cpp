#include "tcpServer.hpp"
#include "exceptions.hpp"
#include <sys/time.h>
#include <sys/select.h>
using namespace exceptions;

namespace kokfikoCDR {

TcpServer::TcpServer(const char* a_ipAddress, size_t a_port)
: m_socket(a_ipAddress, a_port)
, m_clients()
{
    setSocket();
    bindSocket();
    listenSocket();
}

void TcpServer::SetSocketConnection() {
    struct sockaddr_in sin;
    socklen_t addrLen = sizeof(sin);
    int clientSocket = accept(m_socket.GetSocketNumber(),reinterpret_cast<struct sockaddr*>(&sin), &addrLen);
    if(0 > clientSocket) {
        throw ExcAcceptFailed();
    }
    m_clients.push_back(new TcpClient(clientSocket));
}

void TcpServer::GetData(char* a_buffer, size_t a_bufferSize) {
    m_clients[0]->RecvMessage(a_buffer, a_bufferSize);
}

// private functions

void TcpServer::setSocket() {
    int optval = 1;
    if (setsockopt(m_socket.GetSocketNumber(), SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
		throw ExcSetSocketFailed();
	}
}

void TcpServer::bindSocket() {
    struct sockaddr_in srvAddr = m_socket.GetSocketAddr();
    int status = bind(m_socket.GetSocketNumber(), reinterpret_cast<struct sockaddr*>(&srvAddr), sizeof(m_socket.GetSocketAddr()));
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