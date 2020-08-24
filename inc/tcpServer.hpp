#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "tcpClient.hpp"
#include <vector>

namespace kokfikoCDR {

class TcpServer {
public:
    TcpServer(const char* a_ipAddress, size_t a_port);

    void GetSocketConnection(int& a_activity);
    void GetData(char* a_buffer, size_t a_bufferSize);

private:
    void setSocket();
    void bindSocket();
    void listenSocket();

private:
    static const size_t NUM_OF_CLIENTS = 1;

    TcpClient m_socket;
    std::vector<TcpClient*> m_clients;
};

} // kokfikoCDR

#endif