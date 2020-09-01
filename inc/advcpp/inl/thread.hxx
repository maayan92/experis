#include "conditionVariable.hpp"
#include <cassert>
#include <errno.h>
#include <unistd.h>

namespace advcpp {

template<typename T>
struct ThreadElement {
    shared_ptr<T> m_sharePtr;
    experis::ConditionVariable& m_waitFlag;
    experis::AtomicFlag& m_wasNotify;
    bool operator()() {
        return m_wasNotify.GetValue();
    }
};

static void joinErrors(int a_status)
{
    assert(ESRCH != a_status);
    assert(EDEADLK != a_status);
    assert(EINVAL != a_status);
}

template<typename T>
void* Thread<T>::threadAction(void* a_element)
{
    ThreadElement<T>* element = reinterpret_cast<ThreadElement<T>* >(a_element);
    assert(element->m_sharePtr);
    shared_ptr<T> actionPtr(element->m_sharePtr);
    assert(actionPtr);
    element->m_wasNotify.CheckAndSet();
    element->m_waitFlag.NotifyOne();

    try {
        actionPtr->operator()();
    } catch(const std::exception& exc) {
        ///
    }

    return 0;
}

template<typename T>
Thread<T>::Thread(shared_ptr<T> a_sharedPtr)
: m_id()
, m_joinedOrDetached(false)
{
    assert(a_sharedPtr);
    experis::ConditionVariable waitFlag;
    experis::AtomicFlag wasNotify(false);
    ThreadElement<T> element = { a_sharedPtr, waitFlag, wasNotify };
    int status = pthread_create(&m_id, 0, threadAction, (void*)&element);
    if(0 != status) {
        assert(EINVAL != status);
        assert(EPERM != status);

        if(EAGAIN == status) {
            throw ExcReachedToMaximum();
        }
        assert(!"undocumented error for pthread_create");
    }
    
    experis::Mutex mutex;
    experis::MutexLocker locker(mutex);
    waitFlag.Wait(locker, element);
}

template<typename T>
Thread<T>::~Thread() NOEXCEPT
{
    assert(m_joinedOrDetached.GetValue());
}

template<typename T>
void Thread<T>::Join() NOEXCEPT
{
    if(m_joinedOrDetached.CheckAndSet()) {
        int status = pthread_join(m_id, 0);
        if(0 != status) {
            joinErrors(status);
            assert(!"undocumented error for pthread_join");
        }
    }
}

template<typename T>
void Thread<T>::Detach() NOEXCEPT
{
    if(m_joinedOrDetached.CheckAndSet()) {
        int status = pthread_detach(m_id);
        if(0 != status) {
            assert(ESRCH != status);
            assert(EINVAL != status);
            assert(!"undocumented error for pthread_detach");
        }
    }
}

template<typename T>
void Thread<T>::TryJoin()
{
    if(m_joinedOrDetached.CheckAndSet()) {
        int status = pthread_tryjoin_np(m_id, 0);
        if(0 != status) {
            joinErrors(status);
            if(EBUSY == status) {
                m_joinedOrDetached.CheckAndReset();
                throw ExcNotYetTerminated();
            }
            assert(!"undocumented error for pthread_tryjoin_np");
        }
    }
}

template<typename T>
void Thread<T>::Exit(void* a_value) NOEXCEPT
{
    pthread_exit(a_value);
}

template<typename T>
void Thread<T>::Sleep(size_t a_nanoseconds) NOEXCEPT
{
    //const size_t fromNanoToMicro = 1000;
    //useconds_t timeToSleep =  a_nanoseconds / fromNanoToMicro;
}

template<typename T>
void Thread<T>::Yeild() NOEXCEPT
{
    pthread_yield();
}

} // advcpp