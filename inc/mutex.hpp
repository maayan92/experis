#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>
#include <exception>
#include "uncopyable.hpp"

namespace experis {

class ExcNotEnoughPermission : public std::exception {
public:
    virtual const char* what() const throw() { 
        return "initialization error - not enough permission!";
    }
};

class ExcNotEnoughSyncResources : public std::exception {
public:
    virtual const char* what() const throw() {
        return "initialization error - not enough synchronize resources";
    }
};

class ExcMutexIsAlreadyLocked : public std::exception {
public:
    virtual const char* what() const throw() {
        return "lock error - mutex is already locked!";
    }
};

class ExcDoesNotOwnCurrentMutex : public std::exception {
public:
    virtual const char* what() const throw() {
        return "unlock error - doesn't own current mutex!";
    }
};

class Mutex : private Uncopyable{
public:
    Mutex();
    ~Mutex();

    void Lock();
    void Unlock();
    pthread_mutex_t& GetMutex();

private:
    pthread_mutex_t m_locker;
};

} // experis

#endif