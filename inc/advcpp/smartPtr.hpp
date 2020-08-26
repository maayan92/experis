#ifndef SMART_POINTER_HPP
#define SMART_POINTER_HPP

#include "uncopyable.hpp"
#include <iosfwd>

namespace advcpp {

template<typename T>
class SmartPtr : private experis::Uncopyable {
    void BoolFunc() {}
    typedef void (SmartPtr::*BoolResult)();
    template<typename U>
    friend bool operator==(const SmartPtr<U>& a_left, const SmartPtr<U>& a_right);
public:
    explicit SmartPtr(T* a_ptr = 0);
    ~SmartPtr();

    const T* operator->() const;
    const T& operator*() const;
    operator BoolResult() const;
    const T** operator&() const;
    
    T* operator->();
    T& operator*();
    T** operator&();

private:
    T* m_ptr;
};

} // advcpp

#include "smartPtr.hxx"

#endif