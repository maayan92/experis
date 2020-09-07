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
    void AddNewThread();

private:
    void threadsInitialization(size_t a_numOfThread);
    bool isNotEmpty() const;

private:
    experis::Mutex m_mutex;
    std::vector<shared_ptr<advcpp::Thread<Tasks> > > m_threads;
    WaitableQueue<shared_ptr<experis::IRunnable> > m_tasksQueue;
    experis::AtomicFlag m_wasShutDown;
    experis::WaitersConditionVar m_cvWaitForTasks;
    shared_ptr<Tasks> m_tasks;
};

} // advcpp

#endif