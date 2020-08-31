#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include "atomic.hpp"
#include "mutex.hpp"
#include <iosfwd>
#include <exception>

namespace advcpp {

struct ExcPtrIsNULL : public std::exception {
    const char* what() const throw() {
        return "shared pointer is not allocated!";
    }
};

template<typename T>
class shared_ptr {
    void BoolFunc() {}
    typedef void (shared_ptr::*BoolResult)();
    template<typename U>
    friend bool operator==(const shared_ptr<U>& a_left, const shared_ptr<U>& a_right);

    template<typename>
    friend class shared_ptr;
public:
    explicit shared_ptr(T* a_ptr = 0);
    shared_ptr(const shared_ptr& a_sharedPtr);
    
    template<typename U>
    shared_ptr(const shared_ptr<U>& a_sharedPtr);
    
    ~shared_ptr();
    shared_ptr& operator=(const shared_ptr& a_sharedPtr);

    template<typename U>
    shared_ptr& operator=(const shared_ptr<U>& a_sharedPtr);

    const T* operator->() const;
    const T& operator*() const;
    operator BoolResult() const;
    
    T* operator->();
    T& operator*();

    void Reset();
    size_t UseCount() const;

    template<typename U>
    void Swap(shared_ptr<U>& a_sharedPtr);

private:
    template<typename U>
    void copyObject(const shared_ptr<U>& a_sharedPtr);

private:
    T* m_ptr;
    experis::Atomic<size_t>* m_counter;
};

} // advcpp

#include "inl/shared_ptr.hxx"

#endif