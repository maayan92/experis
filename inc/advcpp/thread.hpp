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

struct ExcCaughtFromUser : public std::exception {
    ExcCaughtFromUser(std::string& a_excetion)
    : m_exception(a_excetion)
    {}
    virtual ~ExcCaughtFromUser() throw() {}
    virtual const char* what() const throw() {
        return m_exception.c_str();
    }

private:
    std::string m_exception;
};

template<typename T>
class Thread : private experis::Uncopyable{
public:
    explicit Thread(shared_ptr<T> a_sharedPtr);
    ~Thread() NOEXCEPT;

    void* Join();
    void Detach() NOEXCEPT;

    void* TryJoin();

    static void Exit(void* a_value) NOEXCEPT;
    static void Sleep(size_t a_nanoseconds) NOEXCEPT;
    static void Yeild() NOEXCEPT;

private:
    static void* threadAction(void* a_element);

private:
    pthread_t m_id;
    experis::AtomicFlag m_joinedOrDetached;
    std::string m_exception;
};

} // advcpp

#include "inl/thread.hxx"

#endif