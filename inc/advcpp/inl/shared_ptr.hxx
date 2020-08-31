#include "locker.hpp"
#include <iostream>

namespace advcpp {

template<typename T>
shared_ptr<T>::~shared_ptr()
{
    if(0 == --(*m_counter)) {
        delete m_ptr;
        delete m_counter;
    }
}

template<typename T>
shared_ptr<T>::shared_ptr(T* a_ptr)
: m_ptr(a_ptr)
, m_counter(0)
{
    try {
        m_counter = new experis::Atomic<size_t>(1);
    }catch(...) {
        delete m_ptr;
        throw;
    }
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& a_sharedPtr)
{
    copyObject(a_sharedPtr);
}

template<typename T>
template<typename U>
shared_ptr<T>::shared_ptr(const shared_ptr<U>& a_sharedPtr)
{
    copyObject(a_sharedPtr);
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& a_sharedPtr)
{
    shared_ptr<T> temp(a_sharedPtr);
    this->Swap(temp);
    return *this;
}

template<typename T>
template<typename U>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<U>& a_sharedPtr)
{
    shared_ptr<U> temp(a_sharedPtr);
    this->Swap(temp);
    return *this;
}

template<typename T>
const T* shared_ptr<T>::operator->() const
{
    return m_ptr;
}

template<typename T>
const T& shared_ptr<T>::operator*() const
{
    return *m_ptr;
}

template<typename T>
shared_ptr<T>::operator BoolResult() const
{
    return (0 != m_ptr) ? &shared_ptr::BoolFunc : 0;
}

template<typename T>
T* shared_ptr<T>::operator->()
{
    return m_ptr;
}

template<typename T>
T& shared_ptr<T>::operator*()
{
    if(!m_ptr) {
        throw ExcPtrIsNULL();
    }
    return *m_ptr;
}

template<typename T>
void shared_ptr<T>::Reset()
{
    m_ptr = 0;
}

template<typename T>
size_t shared_ptr<T>::UseCount() const
{
    return *m_counter;
}

template<typename T>
template<typename U>
void shared_ptr<T>::Swap(shared_ptr<U>& a_sharedPtr)
{
    U* ptr = static_cast<U*>(m_ptr);
    m_ptr = a_sharedPtr.m_ptr;
    a_sharedPtr.m_ptr = ptr;

    experis::Atomic<size_t>* counter = m_counter;
    m_counter = a_sharedPtr.m_counter;
    a_sharedPtr.m_counter = counter;
}

// private functions:

template<typename T>
template<typename U>
void shared_ptr<T>::copyObject(const shared_ptr<U>& a_sharedPtr)
{
    ++(*a_sharedPtr.m_counter);
    m_counter = a_sharedPtr.m_counter;
    m_ptr = a_sharedPtr.m_ptr;
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