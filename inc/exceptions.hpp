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

} // exceptions

#endif