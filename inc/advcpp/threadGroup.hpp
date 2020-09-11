#ifndef THREAD_GROUP_HPP
#define THREAD_GROUP_HPP

#include <vector>
#include "thread.hpp"

namespace advcpp {

template<typename Action>
class ThreadGroup {
public:
    ThreadGroup(shared_ptr<Action> a_action, size_t a_numOfThread = 1);
    ~ThreadGroup();

    void AddThreads(shared_ptr<Action> a_action, size_t a_numOfThread = 1);
    void RemoveThread(pthread_t a_threadId);
    void JoinAll();
    
    size_t NumOfThread() const;

private:
    void threadsInitialization(shared_ptr<Action> a_action, size_t a_numOfThread);

private:
    mutable experis::Mutex m_mutex;
    std::vector<shared_ptr<Thread<Action> > > m_threads;
};

} // advcpp

#include "inl/threadGroup.hxx"

#endif