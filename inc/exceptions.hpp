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

} // exceptions

#endif