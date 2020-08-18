#ifndef MUTEX_BUCKET_H
#define MUTEX_BUCKET_H

#include "mutex.hpp"
#include "uncopyable.hpp"
#include <vector>

namespace experis {

class MutexBucket : private Uncopyable{
public:
    MutexBucket(size_t a_numOfThreads);
    //~MutexBucket() = default;

    void LockByPosition(size_t a_hashPosition);
    void UnLockByPosition(size_t a_hashPosition);

private:
    size_t calcCapacity(size_t a_numOfThreads);

private:
    std::vector<Mutex*> m_bucket;
};

} // experis

#endif