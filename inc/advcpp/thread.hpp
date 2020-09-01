#ifndef THREAD_HPP
#define THREAD_HPP

#include "uncopyable.hpp"
#include "shared_ptr.hpp"
#include <pthread.h>
#include <exception>

#define NOEXCEPT throw()

namespace advcpp {

struct ExcReachedToMaximum : public std::exception {
    virtual const char* what() const throw() {
        return "create thread - reached to the maximum number of PIDs!";
    }
};

struct ExcNotYetTerminated : public std::exception {
    virtual const char* what() const throw() {
        return "try join thread - the thread has not yet terminated!";
    }
};

template<typename T>
class Thread : private experis::Uncopyable{
public:
    explicit Thread(shared_ptr<T> a_sharedPtr);
    ~Thread() NOEXCEPT;

    void* Join() NOEXCEPT;
    void Detach() NOEXCEPT;

    void* TryJoin();

    static void Exit(void* a_value) NOEXCEPT;
    static void Sleep(size_t a_nanoseconds) NOEXCEPT; // TODO, nothing in the function
    static void Yeild() NOEXCEPT;

private:
    static void* threadAction(void* a_element);

private:
    pthread_t m_id;
    experis::AtomicFlag m_joinedOrDetached;
    shared_ptr<std::exception> m_exception;
};

} // advcpp

#include "inl/thread.hxx"

#endif