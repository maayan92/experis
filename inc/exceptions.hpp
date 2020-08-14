#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

namespace exceptions {

class ExcPermissionDenied : std::exception {
public:
    virtual const char* what() const throw() {
        return "Permission to create a socket is denied!";
    }
};

class ExcDescriptorTableFull : std::exception {
public:
    virtual const char* what() const throw() {
        return "The socket descriptor table is full!";
    }
};

class ExcNotEnoughSpace : std::exception {
public:
    virtual const char* what() const throw() {
        return "The socket cannot be created until sufficient resources are freed!";
    }
};

class ExcConnectionReset : std::exception {
public:
    virtual const char* what() const throw() {
        return "Connection reset!";
    }
};

class ExcSignalOccurred : std::exception {
public:
    virtual const char* what() const throw() {
        return "A signal occurred before any data was transmitted!";
    }
};

class ExcNoMemory : std::exception {
public:
    virtual const char* what() const throw() {
        return "No memory available!";
    }
};

class ExcLocalHasBeenShutDown : std::exception {
public:
    virtual const char* what() const throw() {
        return "The local end has been shut down on a connection oriented socket!";
    }
};

} // exceptions

#endif