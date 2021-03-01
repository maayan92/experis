#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <arpa/inet.h>
#include <string>
#include "uncopyable.hpp"

namespace experis {

class ClientTcp : private Uncopyable {
public:
    ClientTcp(const std::string& a_ipAddress, size_t a_port);
    ~ClientTcp();
    
    void ConnectToServer();
    void SendMessage(const std::string& a_msg) const;
    void RecvMessage(int m_clientSocket, char* a_msg, size_t a_msgSize);

private:
    void createSockerAddr(const std::string& a_ipAddress, size_t a_port);
    
private:
    int m_socketNum;
    struct sockaddr_in m_servAddr;
    
};

} // experis

#endif