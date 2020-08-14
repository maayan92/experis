#include "socket.hpp"
#include "exceptions.hpp"
#include <cerrno>
#include <cassert>
#include <sys/socket.h>
#include <unistd.h> // for close() socket
using namespace exceptions;

namespace tcp {

Socket::Socket(unsigned int a_port) {
    m_socketNum = socket(AF_INET, SOCK_STREAM, 0);
    if(m_socketNum < 0) {
        assert(EINVAL != errno);
        assert(EAFNOSUPPORT != errno);
        assert(EPROTONOSUPPORT != errno);

        if(EACCES == errno) {
            throw ExcPermissionDenied();
        }
        if(EMFILE == errno) {
            throw ExcDescriptorTableFull();
        }
        if(ENOBUFS == errno || ENOMEM == errno) {
            throw ExcNotEnoughSpace();
        }
        assert(!"undocumented error for socket!");
    }
}

Socket::~Socket() {
    int status = close(m_socketNum);
    assert(0 == status);
}

} // tcp