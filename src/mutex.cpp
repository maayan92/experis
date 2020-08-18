#include "mutex.hpp"
#include <assert.h>
#include <errno.h>
#include <new>

namespace experis {

Mutex::Mutex()
: Uncopyable()
, m_locker() {
    int status = pthread_mutex_init(&m_locker, NULL);
    if(0 != status) {
        assert(EINVAL != status);
        assert(EBUSY != status);

        if(EPERM == status) {
            throw ExcNotEnoughPermission();
        }
        if(ENOMEM == status) {
            throw std::bad_alloc();
        }
        if(EAGAIN) {
           throw ExcNotEnoughSyncResources(); 
        }
        assert(!"undocumented error for pthread_mutex_init");
    }
}

Mutex::~Mutex() {
    int status = pthread_mutex_destroy(&m_locker);
    assert(0 == status);
}

void Mutex::Lock() {
    int status = pthread_mutex_lock(&m_locker);
    if(0 != status) {
        assert(EINVAL != status);
        assert(EBUSY != status);
        assert(EAGAIN != status);
        
        if(EDEADLK == status) {
            throw ExcMutexIsAlreadyLocked();
        }
        assert(!"undocumented error for pthread_mutex_lock");
    }
}

void Mutex::Unlock() {
    int status = pthread_mutex_unlock(&m_locker);
    if(0 != status) {
        assert(EINVAL != status);
        assert(EBUSY != status);
        assert(EAGAIN != status);
        assert(EPERM != status);
        assert(!"undocumented error for pthread_mutex_unlock");
    }
}

pthread_mutex_t& Mutex::GetMutex() {
    return m_locker;
}

} // experis