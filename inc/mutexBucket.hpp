#ifndef MUTEX_BUCKET_H
#define MUTEX_BUCKET_H

#include "mutex.hpp"
#include "uncopyable.hpp"
#include <vector>

namespace experis {

class MutexBucket : private Uncopyable{
public:
    MutexBucket(size_t a_numOfThreads);
    ~MutexBucket();

    void LockByPosition(size_t a_hashPosition) const;
    void UnLockByPosition(size_t a_hashPosition) const;

private:
    size_t calcCapacity(size_t a_numOfThreads);
    void createMutexs();
    void deleteMutexs();

private:
    std::vector<Mutex*> m_bucket;
};

} // experis

#endif