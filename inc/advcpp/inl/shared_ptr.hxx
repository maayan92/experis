#include "locker.hpp"
#include <iostream>

namespace advcpp {

template<typename T>
shared_ptr<T>::~shared_ptr()
{
    deletePointers();
}

template<typename T>
shared_ptr<T>::shared_ptr(T* a_ptr)
: m_ptr(a_ptr)
, m_counter(new experis::Atomic<size_t>(1))
, m_ptrSafe(new experis::Mutex())
{
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& a_sharedPtr) ///
{
    experis::multiThreading::Locker lockCopy(a_sharedPtr.m_ptrSafe);
    copyObject(a_sharedPtr);
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& a_sharedPtr) ///
{
    if(*this != a_sharedPtr) {
        if(*(a_sharedPtr.m_counter) > 0) {
            experis::multiThreading::Locker lockCopy(a_sharedPtr.m_ptrSafe);
            deletePointers();
            copyObject(a_sharedPtr);
        }
    }
    return *this;
}

template<typename T>
const T* shared_ptr<T>::operator->() const
{
    experis::multiThreading::Locker lock(m_ptrSafe);
    return m_ptr;
}

template<typename T>
const T& shared_ptr<T>::operator*() const
{
    experis::multiThreading::Locker lock(m_ptrSafe);
    return *m_ptr;
}

template<typename T>
shared_ptr<T>::operator BoolResult() const
{
    experis::multiThreading::Locker lock(m_ptrSafe);
    return (0 != m_ptr) ? &shared_ptr::BoolFunc : 0;
}

template<typename T>
T* shared_ptr<T>::operator->()
{
    experis::multiThreading::Locker lock(m_ptrSafe);
    return m_ptr;
}

template<typename T>
T& shared_ptr<T>::operator*()
{
    experis::multiThreading::Locker lock(m_ptrSafe);
    if(!m_ptr) {
        throw ExcPtrIsNotNULL();
    }
    return *m_ptr;
}

template<typename T>
void shared_ptr<T>::Reset()
{
    experis::multiThreading::Locker lock(m_ptrSafe);
    m_ptr = 0;
}

template<typename T>
size_t shared_ptr<T>::UseCount() const
{
    return *m_counter;
}

template<typename T>
void shared_ptr<T>::Swap(shared_ptr& a_sharedPtr)
{
    experis::multiThreading::Locker lock(m_ptrSafe);
    experis::multiThreading::Locker secondLock(a_sharedPtr.m_ptrSafe);
    if(*this != a_sharedPtr) {
        T* ptr = m_ptr;
        m_ptr = a_sharedPtr.m_ptr;
        a_sharedPtr.m_ptr = ptr;

        experis::Atomic<size_t>* counter = m_counter;
        m_counter = a_sharedPtr.m_counter;
        a_sharedPtr.m_counter = counter;

        experis::Mutex* ptrSafe = m_ptrSafe;
        m_ptrSafe = a_sharedPtr.m_ptrSafe;
        a_sharedPtr.m_ptrSafe = ptrSafe;
    }
}

// private functions:

template<typename T>
void shared_ptr<T>::deletePointers()
{
    {
        experis::multiThreading::Locker lock(m_ptrSafe);
        if(0 == --(*m_counter)) {
            delete m_ptr;
            delete m_counter;
            m_counter = 0;
        }
    }
    if(!m_counter) {
        delete m_ptrSafe;
    }
}

template<typename T>
void shared_ptr<T>::copyObject(const shared_ptr& a_sharedPtr)
{
    ++(*a_sharedPtr.m_counter);
    m_counter = a_sharedPtr.m_counter;
    m_ptr = a_sharedPtr.m_ptr;
    m_ptrSafe = a_sharedPtr.m_ptrSafe;
}

// additional functions:

template<typename T>
bool operator==(const shared_ptr<T>& a_left, const shared_ptr<T>& a_right)
{
    assert(!((a_left.m_ptr == a_right.m_ptr) && (a_left.m_counter != a_right.m_counter)));
    return (a_left.m_ptr == a_right.m_ptr);
}

template<typename T>
bool operator!=(const shared_ptr<T>& a_left, const shared_ptr<T>& a_right)
{
    return !(a_left == a_right);
}

} // advcpp