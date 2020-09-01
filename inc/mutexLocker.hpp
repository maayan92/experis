#ifndef __MUTEX_LOCKER_H__
#define __MUTEX_LOCKER_H__

#include "mutex.hpp"

namespace experis {

class MutexLocker : private Uncopyable {
    friend class ConditionVariable;
public:
    explicit MutexLocker(Mutex &a_mutex);
    ~MutexLocker();
    void Lock();
    void Unlock();
    Mutex& GetMutex();

private:
    Mutex& m_mutexLocker;
};

} // experis

#include "inl/mutexLocker.hxx"

#endif