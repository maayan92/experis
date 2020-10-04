#ifndef SERVER_TCP_HPP
#define SERVER_TCP_HPP

#include <string>

namespace experis {

class ServerTcp {
public:
    ServerTcp(const std::string& a_ipAddr, size_t a_port);
    ~ServerTcp();

    int SetConnection();
    int GetSockNum() const;

private:
    int openSocket();
    void setSocket();
    void bind(const std::string& a_ipAddr, size_t a_port);
    void listen();

private:
    static const size_t NUM_OF_CLIENTS = 64;

    int m_socketNum;
};

} // experis

#endif