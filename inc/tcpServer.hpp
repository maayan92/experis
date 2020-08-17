#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "tcpClient.hpp"
#include <vector>

namespace kokfikoCDR {

class TcpServer {
public:
    TcpServer(const char* a_ipAddress, size_t a_port);

    int WaitForMessage();
    int GetSocketConnection(int& a_activity);
    void GetData(char* a_buffer, size_t a_bufferSize, int a_clientSocket);

private:
    void setSocket();
    void bindSocket();
    void listenSocket();

private:
    static const size_t NUM_OF_CLIENTS = 50;
    static const size_t NUM_OF_SOCKETS = 1024;
    static const size_t MAX_CLIENTS = 1000;

    TcpClient m_socket;
    std::vector<int> m_clients;
	fd_set m_masterfd;
    fd_set m_watchingfd;
};

} // kokfikoCDR

#endif