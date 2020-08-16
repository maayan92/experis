#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "socket.hpp"
#include <arpa/inet.h> 

namespace kokfikoCDR {

class TcpClient {
public:
    TcpClient();
    //TcpClient(const TcpClient& a_tcpClient) = default;
    ~TcpClient();
    //TcpClient& operator=(cons t TcpClient& a_tcpClient) = default;

    void ConnectToServer();
    void SendMessage(const char* a_msg) const;

private:  
    void createSockerAddr();

private:
    int m_socketNum;
    struct sockaddr_in m_servAddr;
};

} // kokfikoCDR

#endif