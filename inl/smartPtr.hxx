#include <assert.h>

namespace experis {

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
T* SmartPtr<T>::operator->()
{
    return m_ptr;
}

template<typename T>
T& SmartPtr<T>::operator*()
{
    return *m_ptr;
}

template<typename T>
bool operator==(const SmartPtr<T>& a_smartPtr, size_t a_zero)
{
    assert(0 == a_zero);
    return (reinterpret_cast<size_t>(a_smartPtr.m_ptr) == a_zero);
}

} // experis