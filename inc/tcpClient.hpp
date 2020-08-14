#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "socket.hpp"
#include <string>
#include <arpa/inet.h> 

namespace kokfikoCDR {

class TcpClient {
public:
    TcpClient();
    //TcpClient(const TcpClient& a_tcpClient) = default;
    //~TcpClient() = default;
    //TcpClient& operator=(cons t TcpClient& a_tcpClient) = default;

    void SendMessage(const char* a_msg) const;

private:  
    void createSockerAddr();
    void connectToServer();

private:
    tcp::Socket m_socket;
    struct sockaddr_in m_servAddr;
};

} // kokfikoCDR

#endif