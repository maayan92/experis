#ifndef THREAD_GROUP_HPP
#define THREAD_GROUP_HPP

#include <vector>
#include "thread.hpp"

namespace advcpp {

struct ExcThreadIsNotInThreadGroup : public std::exception {
    const char* what() const throw() {
        return "thread remove, pthread_t id does not match any thread id in the thread group!";
    }
};

template<typename Action>
class ThreadGroup {
public:
    ThreadGroup();
    ThreadGroup(shared_ptr<Action> a_action, size_t a_numOfThread = 1);
    ~ThreadGroup();

    void AddThreads(shared_ptr<Action> a_action, size_t a_numOfThread = 1);
    void RemoveThread(pthread_t a_threadId);
    void JoinAll();
    
    size_t NumOfThread() const;
    void Clear();

private:
    void threadsInitialization(shared_ptr<Action> a_action, size_t a_numOfThread);

private:
    mutable experis::Mutex m_mutex;
    std::vector<shared_ptr<Thread<Action> > > m_threads;
};

} // advcpp

#include "inl/threadGroup.hxx"

#endif