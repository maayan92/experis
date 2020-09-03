#include "conditionVariable.hpp"
#include <pthread.h>
#include <iostream>

namespace experis {

ConditionVariable::ConditionVariable()
: m_condVar() 
{
    int status = pthread_cond_init(&m_condVar, NULL);
    if(0 != status) {
        assert(EBUSY != status);
        assert(EINVAL != status);

        if(EAGAIN == status) {
            throw ExcSystemLackedOfResources();
        }
        if(ENOMEM == status) {
            throw ExcInsufficientMemory();
        }
        assert(!"undocumented error for pthread_cond_init");
    }
}

ConditionVariable::~ConditionVariable() throw() {
    int status = pthread_cond_destroy(&m_condVar);
    if(0 != status) {
        assert(EINVAL != status);
        assert(EBUSY != status);
        assert(!"undocumented error for pthread_cond_destroy");
    }
}

void ConditionVariable::NotifyOne() {
    int status = pthread_cond_signal(&m_condVar);
    if(0 != status) {
        assert(EINVAL != status);
        assert(!"undocumented error for pthread_cond_signal");
    }
}

void ConditionVariable::NotifyAll() {
    int status = pthread_cond_broadcast(&m_condVar);
    if(0 != status) {
        assert(EINVAL != status);
        assert(!"undocumented error for pthread_cond_broadcast");
    }
}

} // experis