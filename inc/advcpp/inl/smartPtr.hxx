#include <assert.h>
#include <iostream>
namespace advcpp {

template<typename T>
SmartPtr<T>::SmartPtr(T* a_ptr)
: m_ptr(a_ptr)
{
}

template<typename T>
SmartPtr<T>::~SmartPtr()
{
    delete m_ptr;
}

template<typename T>
const T* SmartPtr<T>::operator->() const
{
    return m_ptr;
}

template<typename T>
T* SmartPtr<T>::operator->()
{
    return m_ptr;
}

template<typename T>
const T& SmartPtr<T>::operator*() const
{
    return *m_ptr;
}

template<typename T>
T& SmartPtr<T>::operator*()
{
    return *m_ptr;
}

template<typename T>
const T** SmartPtr<T>::operator&() const
{
    return &m_ptr;
}

template<typename T>
T** SmartPtr<T>::operator&()
{
    return &m_ptr;
}

template<typename T>
SmartPtr<T>::operator BoolResult() const
{
    return (0 != m_ptr) ? &SmartPtr::BoolFunc : 0;
}

// static functions

template<typename T>
static bool operator==(const SmartPtr<T>& a_left, const SmartPtr<T>& a_right)
{
    if(0 == a_left.m_ptr && 0 == a_right.m_ptr) {
        return true;
    }
    assert(a_left.m_ptr != a_right.m_ptr);
    return (a_left.m_ptr == a_right.m_ptr);
}

template<typename T>
static bool operator!=(const SmartPtr<T>& a_left, const SmartPtr<T>& a_right)
{
    return !(a_left == a_right);
}

} // advcpp