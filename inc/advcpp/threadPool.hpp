#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector>
#include "thread.hpp"
#include "tasks.hpp"

namespace advcpp {

class ThreadPool : private experis::Uncopyable {
public:
    explicit ThreadPool(size_t a_numOfThread);
    ThreadPool(size_t a_numOfThread, size_t a_maxCapacityOfTasks);
    ~ThreadPool();

    void Submit(shared_ptr<experis::IRunnable> a_newTask);
    void ShutDown();
    void ShutDownImmediately();
    void AddThread(size_t a_numOfThreads = 1);
    void RemoveThread(size_t a_numOfThreads = 1);
    void TurnOn(size_t a_numOfThreads = 1);

    size_t NumOfThread() const;
    size_t NumOfTasks() const;

private:
    void threadsInitialization(size_t a_numOfThread);
    bool isNotEmpty() const;
    void joinAll();
    void shutAllDown();
    void setRemovingTasks(size_t a_numOfThreads, WaitableQueue<pthread_t>& a_removingQueue);

private:
    mutable experis::Mutex m_mutex;
    std::vector<shared_ptr<advcpp::Thread<Tasks> > > m_threads;
    WaitableQueue<shared_ptr<experis::IRunnable> > m_tasksQueue;
    experis::AtomicFlag m_shutDown;
    experis::AtomicFlag m_turnOn;
    experis::AtomicFlag m_shutDownImmediately;
    experis::WaitersConditionVar m_cvWaitForTasks;
    shared_ptr<Tasks> m_tasks;
};

} // advcpp

#endif