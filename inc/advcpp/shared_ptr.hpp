#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include "atomic.hpp"
#include "mutex.hpp"
#include <iosfwd>
#include <exception>

namespace advcpp {

struct ExcPtrIsNotNULL : public std::exception {
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
public:
    explicit shared_ptr(T* a_ptr = 0);
    shared_ptr(const shared_ptr& a_sharedPtr);
    ~shared_ptr();
    shared_ptr& operator=(const shared_ptr& a_sharedPtr);

    const T* operator->() const;
    const T& operator*() const;
    operator BoolResult() const;
    
    T* operator->();
    T& operator*();

    void Reset();
    size_t UseCount() const;
    void Swap(shared_ptr& a_sharedPtr);

private:
    void deletePointers();
    void copyObject(const shared_ptr& a_sharedPtr);

private:
    T* m_ptr;
    experis::Atomic<size_t>* m_counter;
    experis::Mutex* m_ptrSafe;
};

} // advcpp

#include "shared_ptr.hxx"

#endif