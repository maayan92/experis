#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

namespace exceptions {

class ExcPermissionDenied : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Permission to create a socket is denied!";
    }
};

class ExcDescriptorTableFull : public std::exception {
public:
    virtual const char* what() const throw() {
        return "The socket descriptor table is full!";
    }
};

class ExcNotEnoughSpace : public std::exception {
public:
    virtual const char* what() const throw() {
        return "The socket cannot be created until sufficient resources are freed!";
    }
};

class ExcConnectionReset : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Connection reset!";
    }
};

class ExcSignalOccurred : public std::exception {
public:
    virtual const char* what() const throw() {
        return "A signal occurred before any data was transmitted!";
    }
};

class ExcNoMemory : public std::exception {
public:
    virtual const char* what() const throw() {
        return "No memory available!";
    }
};

class ExcLocalHasBeenShutDown : public std::exception {
public:
    virtual const char* what() const throw() {
        return "The local end has been shut down on a connection oriented socket!";
    }
};

class ExcBufferSizeTooSmall : public std::exception {
public:
    virtual const char* what() const throw() {
        return "The buffer size is too small!";
    }
};

class ExcCantSendNotConnected : public std::exception {
public:
    virtual const char* what() const throw() {
        return "send data failed! client is not connection to server!";
    }
};

class ExcConnetionFailed : public std::exception {
public:
    virtual const char* what() const throw() {
        return "client connection request failed!";
    }
};

class ExcSocketIsClosed : public std::exception {
public:
    virtual const char* what() const throw() {
        return "client socket is closed!";
    }
};

class ExcRecieveFailed : public std::exception {
public:
    virtual const char* what() const throw() {
        return "recieve data failed!";
    }
};

class ExcFileFailedToOpen : public std::exception {
public:
    virtual const char* what() const throw() {
        return "The file failed to open!";
    }
};

class ExcSetSocketFailed : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Set server socket failed!";
    }
};

class ExcServerBindFailed : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Server bind failed!";
    }
};

class ExcServerListenFailed : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Server listen failed!";
    }
};

class ExcAcceptFailed : public std::exception {
public:
    virtual const char* what() const throw() {
        return "accept client connection failed!";
    }
};

} // exceptions

#endif