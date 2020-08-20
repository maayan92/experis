#include "mutexBucket.hpp"
#include <algorithm>

namespace experis {

template<class T>
struct DeleteElement {
    void operator()(T* a_element){
        delete a_element;
    }
};

MutexBucket::MutexBucket(size_t a_numOfThreads)
: m_bucket()
{
    createMutexs(calcCapacity(a_numOfThreads));
}

MutexBucket::~MutexBucket() 
{
    std::for_each(m_bucket.begin(), m_bucket.end(), DeleteElement<Mutex>());
}

void MutexBucket::LockByHashPosition(size_t a_hashPosition) const
{
    m_bucket[a_hashPosition % m_bucket.size()]->Lock();
}

void MutexBucket::UnLockByHashPosition(size_t a_hashPosition) const 
{
    m_bucket[a_hashPosition % m_bucket.size()]->Unlock();
}

Mutex* MutexBucket::GetMutexByHashPosition(size_t a_hashPosition) const
{
    return m_bucket[a_hashPosition % m_bucket.size()];
}

// private functions:

size_t MutexBucket::calcCapacity(size_t a_numOfThreads)
{
    return (a_numOfThreads*1.3);
}

void MutexBucket::createMutexs(size_t a_size)
{
    m_bucket.reserve(a_size);
    for (size_t i = 0 ; i < a_size ; ++i) {
        m_bucket.push_back(new Mutex);
    }
}

} // experis
