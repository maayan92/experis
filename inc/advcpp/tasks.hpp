#ifndef TASKS_HPP
#define TASKS_HPP

#include "runnable.hpp"
#include "shared_ptr.hpp"
#include "waitableQueue.hpp"

namespace advcpp {

class Tasks {
public:
    //Tasks() = default;
    //Tasks(const Tasks& a_tasks) = default;
    //~Tasks() = default;
    //Tasks& operator=(const Tasks& a_tasks) = default;

    void operator()();

    void Submit(shared_ptr<experis::IRunnable> a_newTask);
    void ShutDown();

private:
    WaitableQueue<shared_ptr<experis::IRunnable> > m_tasks;
    experis::AtomicFlag m_wasShutDown;
};

} // advcpp

#endif