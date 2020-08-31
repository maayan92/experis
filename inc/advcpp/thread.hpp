#ifndef THREAD_HPP
#define THREAD_HPP

#include "uncopyable.hpp"
#include "shared_ptr.hpp"
#include "conditionVariable.hpp"
#include <pthread.h>
#include <exception>

#define NOEXCEPT throw()

namespace advcpp {

struct ExcReachedToMaximum : public std::exception {
    const char* what() const throw() {
        return "create thread - reached to the maximum number of PIDs!";
    }
};

struct ExcThreadNotJoinable : public std::exception {
    const char* what() const throw() {
        return "join thread - not joinable!";
    }
};

struct ExcNotYetTerminated : public std::exception {
    const char* what() const throw() {
        return "try join thread - the thread has not yet terminated!";
    }
};

template<typename T>
class Thread : private experis::Uncopyable{
public:
    explicit Thread(shared_ptr<T> a_sharedPtr);
    ~Thread() NOEXCEPT;

    void Join() NOEXCEPT;
    void Detach() NOEXCEPT;

    void TryJoin();

    static void Exit(int& a_code) NOEXCEPT;
    static void Sleep(size_t a_nanoseconds) NOEXCEPT; // TODO, nothing in the function
    static void Yeild();

private:
    static void* threadAction(void* a_element);

private:
    pthread_t m_id;
    experis::AtomicFlag m_joinedOrDetached;
    experis::ConditionVariable m_waitFlag;
};

} // advcpp

#include "inl/thread.hxx"

#endif