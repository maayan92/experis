#ifndef __CONDITION_VARIABLE_H__
#define __CONDITION_VARIABLE_H__

#include "mutexLocker.hpp"
#include "atomic.hpp"
#include <assert.h>
#include <errno.h>

namespace experis {

class ConditionVariable : private Uncopyable {
public:
    ConditionVariable();
    ~ConditionVariable() throw();

    void NotifyOne();
    void NotifyAll();

    template<typename Predicate>
    void Wait(MutexLocker& a_mutexLocker, Predicate a_predicate);

    template<typename Predicate>
    void Wait(Mutex& a_mutex, Predicate a_predicate);

private:
    pthread_cond_t m_condVar;
    Atomic<size_t> m_countWaiting;
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

template<typename Predicate>
void ConditionVariable::Wait(MutexLocker &a_mutexLocker, Predicate a_predicate) {
    while(a_predicate()) {
        ++m_countWaiting;
        int status = pthread_cond_wait(&m_condVar, &(a_mutexLocker.m_mutexLocker.m_locker));
        if(0 != status) {
            assert(EINVAL != status);
            assert(EPERM != status);
            assert(!"undocumented error for pthread_cond_wait");
        }
        --m_countWaiting;
    }
}

template<typename Predicate>
void ConditionVariable::Wait(Mutex &a_mutex, Predicate a_predicate) {
    while(a_predicate()) {
        ++m_countWaiting;
        int status = pthread_cond_wait(&m_condVar, &(a_mutex.m_locker));
        if(0 != status) {
            assert(EINVAL != status);
            assert(EPERM != status);
            assert(!"undocumented error for pthread_cond_wait");
        }
        --m_countWaiting;
    }
}

} // experis

#endif