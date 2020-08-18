#include "mutexBucket.hpp"

namespace experis {

MutexBucket::MutexBucket(size_t a_numOfThreads)
: m_bucket(calcCapacity(a_numOfThreads))
{
}

void MutexBucket::LockByPosition(size_t a_hashPosition) {
    size_t position = a_hashPosition % m_bucket.size();
    m_bucket[position]->Lock();
}

void MutexBucket::UnLockByPosition(size_t a_hashPosition) {
    m_bucket[a_hashPosition % m_bucket.size()]->Unlock();
}

// private functions:

size_t MutexBucket::calcCapacity(size_t a_numOfThreads)
{
    return (a_numOfThreads*1.3);
}

} // experis
