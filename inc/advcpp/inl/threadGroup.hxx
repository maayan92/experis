#include <algorithm>
#include <cassert>
#include "mutexLocker.hpp"

namespace advcpp {

template<typename Action>
struct CheckThreadId {
    CheckThreadId(pthread_t a_id)
    : m_id(a_id)
    {}

    bool operator()(shared_ptr<advcpp::Thread<Action> > a_thread) {
        return (*a_thread) == m_id;
    }

private:
    pthread_t m_id;
};

template<typename Action>
ThreadGroup<Action>::ThreadGroup()
: m_mutex()
, m_threads()
{
}

template<typename Action>
ThreadGroup<Action>::ThreadGroup(shared_ptr<Action> a_action, size_t a_numOfThread)
: m_mutex()
, m_threads()
{
    threadsInitialization(a_action, a_numOfThread);
}

template<typename Action>
static void join(shared_ptr<Thread<Action> > a_thread)
{
    a_thread->Join();
}

template<typename Action>
void ThreadGroup<Action>::JoinAll()
{
    for_each(m_threads.begin(), m_threads.end(), join<Action>);
}

template<typename Action>
ThreadGroup<Action>::~ThreadGroup()
{
    JoinAll();
}

template<typename Action>
void ThreadGroup<Action>::AddThreads(shared_ptr<Action> a_action, size_t a_numOfThread)
{
    experis::MutexLocker locker(m_mutex);
    
    m_threads.reserve(m_threads.size() + a_numOfThread);
    for(size_t i = 0 ; i < a_numOfThread ; ++i) {
        shared_ptr<Thread<Action> > shrPtr(new Thread<Action>(a_action));
        m_threads.push_back(shrPtr);
    }
}

template<typename Action>
void ThreadGroup<Action>::RemoveThread(pthread_t a_threadId)
{
    experis::MutexLocker locker(m_mutex);
    
    typedef typename std::vector<shared_ptr<Thread<Action> > >::iterator Iterator;
    Iterator itr = std::find_if(m_threads.begin(), m_threads.end(), CheckThreadId<Action>(a_threadId));
    if(itr == m_threads.end()) {
        throw ExcThreadIsNotInThreadGroup();
    }
    (*itr)->Join();
    m_threads.erase(itr);
}

template<typename Action>
size_t ThreadGroup<Action>::NumOfThread() const
{
    experis::MutexLocker locker(m_mutex);
    return m_threads.size();
}

template<typename Action>
void ThreadGroup<Action>::Clear()
{
    experis::MutexLocker locker(m_mutex);
    m_threads.clear();
}

// private functions:

template<typename Action>
void ThreadGroup<Action>::threadsInitialization(shared_ptr<Action> a_action, size_t a_numOfThread)
{
    m_threads.reserve(a_numOfThread);
    try {
        for(size_t i = 0 ; i < a_numOfThread ; ++i) {
            shared_ptr<Thread<Action> > shrPtr(new Thread<Action>(a_action));
            m_threads.push_back(shrPtr);
        }

    } catch(...) {
        m_threads.clear();
        throw;
    }
}

} // advcpp