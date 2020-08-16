#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <arpa/inet.h> 

namespace kokfikoCDR {

class TcpClient {
public:
    TcpClient();
    ~TcpClient();

    void ConnectToServer();
    void SendMessage(const char* a_msg) const;
    void RecvMessage(int m_clientSocket, char* a_msg, size_t a_msgSize);

    int GetSocketNumber() const { return m_socketNum; }
    struct sockaddr_in& GetSocketAddr() { return m_servAddr; }

private:  
    TcpClient(const TcpClient& a_tcpClient);
    TcpClient& operator=(const TcpClient& a_tcpClient);
    
    void createSockerAddr();

private:
    int m_socketNum;
    struct sockaddr_in m_servAddr;
};

} // kokfikoCDR

#endif