#ifndef SMART_POINTER_HPP
#define SMART_POINTER_HPP

#include "uncopyable.hpp"
#include <iosfwd>

namespace experis {

template<typename T>
class SmartPtr : private Uncopyable {
    template<typename U>
    friend bool operator==(const SmartPtr<U>& a_smartPtr, size_t a_zero);
public:
    explicit SmartPtr(T* a_ptr = 0);
    ~SmartPtr();

    T* operator->();
    T& operator*();
    //operator (void (Testable::*)() const)() const;

private:
    class Testable;

private:
    T* m_ptr;
};

class Testable {
    typedef void (Testable::*bool_type)() const;
    void this_type_does_not_support_comparisons() const {}
public:
    explicit Testable(bool a_result = true) : m_result(a_result) {}

    operator bool_type() const {
        return m_result==true ? 
            &Testable::this_type_does_not_support_comparisons : 0;
    }

private:
    bool m_result;
};

} // experis

#include "smartPtr.hxx"

#endif