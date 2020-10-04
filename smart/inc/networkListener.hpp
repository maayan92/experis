#ifndef NETWORK_LISTENER_HPP
#define NETWORK_LISTENER_HPP

#include <sys/epoll.h>
#include <fstream>
#include "uncopyable.hpp"
#include "iMessageHandler.hpp"
#include "serverTcp.hpp"
#include "fileLog.hpp"

namespace experis {

class NetworkListener : private experis::Uncopyable {
public:
    NetworkListener(const std::string& a_ipAddr, size_t a_port, IMessageHandler& a_msgHandler);
    ~NetworkListener();

    void ListenEvents();

private:
    bool createEpoll();
    bool setNonBlocking(int a_socket);
    bool addEntry(int a_socket);
    void removeEntry(int a_socket);
    void receiveMsg(int a_socket);

private:
    static const size_t MAX_EVENTS = 16;

    IMessageHandler& m_msgHandler;
    ServerTcp m_server;
    FileLog m_logFile;
    struct epoll_event m_epollEv;
    int m_epollFd;
};

} // experis

#endif