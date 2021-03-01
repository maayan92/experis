#include "networkListener.hpp"
#include <cassert>
#include <cerrno>
#include <unistd.h>
#include <stdexcept>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
using namespace std;

namespace experis {

static void HandleEpollCtlError() {
    assert(EBADF == errno);
    assert(EINVAL == errno);
    assert(ELOOP == errno);
    assert(EPERM == errno);
    assert(!"undocumented error for epoll_ctl");
}

NetworkListener::NetworkListener(const std::string& a_ipAddr, size_t a_port, IMessageHandler& a_msgHandler)
: m_msgHandler(a_msgHandler)
, m_server(a_ipAddr, a_port)
, m_log(advcpp::Singleton<FileLog>::Instance())
, m_logFile("network_log.txt", ios::app)
, m_epollEv()
, m_epollFd()
{
    if(!createEpoll()) {
        throw runtime_error("failed to create epoll!");
    }

    m_epollEv.events = EPOLLIN;
    if(!addEntry(m_server.GetSockNum())) {
        ::close(m_epollFd);
        throw runtime_error("failed to set server to epoll!");
    }
}

NetworkListener::~NetworkListener()
{
    int status = ::close(m_epollFd);
    assert(-1 == status);
}

void NetworkListener::ListenEvents()
{
    struct epoll_event events[MAX_EVENTS];

    for (;;) {
        int numOfEvents = ::epoll_wait(m_epollFd, events, MAX_EVENTS, -1);
        if (numOfEvents == -1) {
            LOGINFO(m_log, m_logFile, "epoll_wait failed!");
        }

        for (int i = 0; i < numOfEvents; ++i) {
            if (events[i].data.fd == m_server.GetSockNum()) {
                int clientSock = m_server.SetConnection();
                if (clientSock == -1) {
                    LOGINFO(m_log, m_logFile, "Client connection failed, with socket number: " + clientSock);
                    continue;
                }
                
                if(setNonBlocking(clientSock)) {
                    m_epollEv.events = EPOLLIN | EPOLLET;
                    addEntry(clientSock);
                }

            } else {
                receiveMsg(events[i].data.fd);
            }
        }
    }
}

// private functions:

bool NetworkListener::createEpoll()
{
    m_epollFd = ::epoll_create1(0);
    if(-1 == m_epollFd) {
        assert(EINVAL == errno);
        assert(EMFILE == errno);

        if(ENFILE == errno) {
            LOGINFO(m_log, m_logFile, "Reached the limit of the total number of open files!");
            return false;
        }
        if(ENOMEM == errno) {
            LOGINFO(m_log, m_logFile, "Insufficient memory to create the kernel object!");
            return false;
        }
        assert(!"undocumented error for epoll_create1");
    }
    LOGINFO(m_log, m_logFile, "epoll created successfully!");
    return true;
}

bool NetworkListener::setNonBlocking(int a_socket)
{
    int flags = ::fcntl(a_socket, F_GETFL);
	if (-1 == flags) {
        LOGINFO(m_log, m_logFile, "failed to get file access mode and file status flags, with socket number: " + a_socket);
        return false;
	}

    int status = ::fcntl(a_socket, F_SETFL, flags | O_NONBLOCK);
	if(-1 == status) {
		LOGINFO(m_log, m_logFile, "failed to set file descriptor as non blocking, with socket number: " + a_socket);
        return false;
	}

    return true;
}

bool NetworkListener::addEntry(int a_socket)
{
    m_epollEv.data.fd = a_socket;
    int status = ::epoll_ctl(m_epollFd, EPOLL_CTL_ADD, a_socket, &m_epollEv);
    if (-1 == status) {
        if(EEXIST == errno) {
            LOGINFO(m_log, m_logFile, "The file descriptor is already registered with this epoll instance, with socket number: " + a_socket);
            return false;
        }
        if(ENOMEM == errno) {
            LOGINFO(m_log, m_logFile, "There was insufficient memory to add the file descriptor, with socket number: " + a_socket);
            return false;
        }
        if(ENOSPC == errno) {
            LOGINFO(m_log, m_logFile, "Imposed limit was encountered while trying to register a new file descriptor, with socket number: " + a_socket);
            return false;
        }
        assert(ENOENT == errno);
        HandleEpollCtlError();
    }
    LOGINFO(m_log, m_logFile, "client connected successfully!");
    return true;
}

void NetworkListener::removeEntry(int a_socket)
{
    m_epollEv.data.fd = a_socket;
    int status = ::epoll_ctl(m_epollFd, EPOLL_CTL_DEL, a_socket, &m_epollEv);
    if (-1 == status) {
        if(ENOENT == errno) {
            LOGINFO(m_log, m_logFile, "The file descriptor is not registered with this epoll instance, with socket number: " + a_socket);
            return;
        }
        assert(EEXIST == errno);
        assert(ENOMEM == errno);
        assert(ENOSPC == errno);
        HandleEpollCtlError();
    }
    LOGINFO(m_log, m_logFile, "client closed successfully!");
}

void NetworkListener::receiveMsg(int a_socket)
{
    size_t DATA_SIZE = 100;
    char buffer[DATA_SIZE];

    ssize_t read_bytes = ::recv(a_socket, buffer, DATA_SIZE, 0);

    if(0 == read_bytes) {
        removeEntry(a_socket);
        return;
    }

    else if(0 > read_bytes) {
        assert(EBADF == errno);
        assert(ECONNREFUSED == errno);
        assert(EFAULT == errno);
        assert(EINVAL == errno);
        assert(ENOTCONN == errno);
        assert(ENOTSOCK == errno);

        if(EINTR == errno) {
            LOGINFO(m_log, m_logFile, "The receive was interrupted by a signal before any data was available, with socket number: " + a_socket);
        }
    }

    buffer[read_bytes] = '\0';
    m_msgHandler.HandleMsg(buffer);
}

} // experis