#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector>
#include "thread.hpp"
#include "tasks.hpp"

namespace advcpp {

class ThreadPool {
public:
    explicit ThreadPool(size_t a_numOfThread);
    ~ThreadPool();

    void Submit(shared_ptr<experis::IRunnable> a_newTask);
    void ShutDown();
    void AddNewThread();

private:
    std::vector<shared_ptr<advcpp::Thread<Tasks> > > m_threads;
    shared_ptr<Tasks> m_tasks;
};

} // advcpp

#endif