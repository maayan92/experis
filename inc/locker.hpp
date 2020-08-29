#ifndef LOCKER_H
#define LOCKER_H

#include "mutex.hpp"

namespace experis {

namespace multiThreading {

class Locker : private Uncopyable{
public:
    Locker(Mutex* a_mutex);
    ~Locker();

private:
    Mutex* m_mutex;
};

inline Locker::Locker(Mutex* a_mutex)
: m_mutex(a_mutex)
{
    m_mutex->Lock();
}

inline Locker::~Locker()
{
    m_mutex->Unlock();
}

} // multiThreading

} // experis

#endif