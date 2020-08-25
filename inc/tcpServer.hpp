#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "tcpClient.hpp"
#include "uncopyable.hpp"
#include <vector>

namespace kofiko {

class TcpServer : private experis::Uncopyable {
public:
    TcpServer(const char* a_ipAddress, size_t a_port);

    void SetSocketConnection();
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

} // kofiko

#endif