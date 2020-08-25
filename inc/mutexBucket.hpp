#ifndef MUTEX_BUCKET_H
#define MUTEX_BUCKET_H

#include "mutex.hpp"
#include "uncopyable.hpp"
#include <vector>

namespace experis {

class MutexBucket : private Uncopyable {
public:
    explicit MutexBucket(size_t a_numOfThreads);
    ~MutexBucket();

    void LockByHashPosition(size_t a_hashPosition) const;
    void UnLockByHashPosition(size_t a_hashPosition) const;
    Mutex* GetMutexByHashPosition(size_t a_hashPosition) const;

private:
    size_t calcCapacity(size_t a_numOfThreads);
    void createMutexs(size_t a_size);

private:
    std::vector<Mutex*> m_bucket;
};

} // experis

#endif