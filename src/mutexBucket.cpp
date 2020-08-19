#include "mutexBucket.hpp"
#include <algorithm>

#include <iostream>
namespace experis {

MutexBucket::MutexBucket(size_t a_numOfThreads)
: m_bucket(calcCapacity(a_numOfThreads))
{
    createMutexs();
}

MutexBucket::~MutexBucket() 
{
    deleteMutexs();
}

void MutexBucket::LockByPosition(size_t a_hashPosition) const
{
    m_bucket[a_hashPosition % m_bucket.size()]->Lock();
}

void MutexBucket::UnLockByPosition(size_t a_hashPosition) const 
{
    m_bucket[a_hashPosition % m_bucket.size()]->Unlock();
}

// private functions:

size_t MutexBucket::calcCapacity(size_t a_numOfThreads)
{
    return (a_numOfThreads*1.3);
}

void MutexBucket::createMutexs()
{
    for (size_t i = 0 ; i < m_bucket.size() ; ++i) {
        m_bucket[i] = new Mutex;
    }
}

void MutexBucket::deleteMutexs()
{
    for (size_t i = 0 ; i < m_bucket.size() ; ++i) {
        delete m_bucket[i];
    }
}

} // experis
