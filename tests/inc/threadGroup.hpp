#ifndef THREAD_GROUP_HPP
#define THREAD_GROUP_HPP

#include <vector>
#include "thread.hpp"
#include "waitableQueue.hpp"

namespace experis {

template<typename T, typename Action>
class ThreadGroup {
public:
    ThreadGroup(advcpp::WaitableQueue<T>& a_waQueue);
    ~ThreadGroup();

    void CreateNewThread(std::vector<T>& a_vector);

    void JoinAll();

private:
    std::vector<advcpp::Thread<Action>* > m_threads;
    advcpp::WaitableQueue<T>& m_waQueue;
};

} // experis

namespace experis {

template<typename Action>
static void deleteThread(advcpp::Thread<Action>* a_thread)
{
    delete a_thread;
}

template<typename Action>
static void join(advcpp::Thread<Action>* a_thread)
{
    a_thread->Join();
}

template<typename T, typename Action>
ThreadGroup<T, Action>::ThreadGroup(advcpp::WaitableQueue<T>& a_waQueue)
: m_threads()
, m_waQueue(a_waQueue)
{
}

template<typename T, typename Action>
ThreadGroup<T, Action>::~ThreadGroup()
{
    for_each(m_threads.begin(), m_threads.end(), deleteThread<Action>);
}

template<typename T, typename Action>
void ThreadGroup<T, Action>::CreateNewThread(std::vector<T>& a_vector)
{
    advcpp::shared_ptr<Action> shrPtr(new Action(m_waQueue, a_vector));
    m_threads.push_back(new advcpp::Thread<Action>(shrPtr));
}

template<typename T, typename Action>
void ThreadGroup<T, Action>::JoinAll()
{
    for_each(m_threads.begin(), m_threads.end(), join<Action>);
}

} // experis

#endif