#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "uncopyable.hpp"
#include <arpa/inet.h>

namespace kokfikoCDR {

class TcpClient : private experis::Uncopyable{
public:
    TcpClient(const char* a_ipAddress, size_t a_port);
    explicit TcpClient(int a_socketNum);
    ~TcpClient();

    void ConnectToServer();
    void SendMessage(const char* a_msg) const;
    void RecvMessage(char* a_msg, size_t a_msgSize);

    int GetSocketNumber() const;
    struct sockaddr_in GetSocketAddr() const;

private:  
    void createSocketAddr(const char* a_ipAddress, size_t a_port);
    static int openSocket();

private:
    int m_socketNum;
    struct sockaddr_in m_servAddr;
    bool m_isConnected;
};

} // kokfikoCDR

#endif