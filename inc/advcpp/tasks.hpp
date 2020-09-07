#ifndef TASKS_HPP
#define TASKS_HPP

#include "runnable.hpp"
#include "shared_ptr.hpp"
#include "waitableQueue.hpp"
#include "uncopyable.hpp"

namespace advcpp {

class Tasks : private experis::Uncopyable {
public:
    Tasks();
    explicit Tasks(size_t a_maxCapacityOfTasks);
    //~Tasks() = default;

    void operator()();

    void Submit(shared_ptr<experis::IRunnable> a_newTask);
    void ShutDown();

private:
    bool isNotEmpty() const;

private:
    experis::Mutex m_mutex;
    WaitableQueue<shared_ptr<experis::IRunnable> > m_tasks;
    experis::AtomicFlag m_wasShutDown;
    experis::ConditionVariable m_cvWaitForTasks;
};

} // advcpp

#endif