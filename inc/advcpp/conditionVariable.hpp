#ifndef __CONDITION_VARIABLE_H__
#define __CONDITION_VARIABLE_H__

#include "mutex.hpp"

namespace experis {

class ConditionVariable : private Uncopyable {
public:
    ConditionVariable();
    ~ConditionVariable() throw();

    void NotifyOne();
    void NotifyAll();
    void Wait(Mutex& a_mutex);

private:
    pthread_cond_t m_condVar;
};

class ExcSystemLackedOfResources : public std::exception {
public:
    const char* what() const throw() {
        return "create error - system lacked the necessary resources";
    }
};

class ExcInsufficientMemory : public std::exception {
public:
    const char* what() const throw() {
        return "create error - Insufficient memory exists to initialize";
    }
};

} // experis

#endif