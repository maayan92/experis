#ifndef SOCKET_H
#define SOCKET_H

namespace tcp {

class Socket {
public:
    Socket(unsigned int a_port);
    //Socket(const Socket& a_socket) = default;
    ~Socket();
    //Socket& operator=(const Socket& a_socket) = default;

    int GetSocketNumber() const { return m_socketNum; }

private:
    int m_socketNum;
};

} // tcp

#endif