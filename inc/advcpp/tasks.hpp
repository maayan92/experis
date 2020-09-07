#ifndef TASKS_HPP
#define TASKS_HPP

#include "runnable.hpp"
#include "shared_ptr.hpp"
#include "waitableQueue.hpp"

namespace advcpp {

class Tasks : private experis::Uncopyable {
    typedef WaitableQueue<shared_ptr<experis::IRunnable> > WaitQueue;
public:
    Tasks(WaitQueue& a_tasks, experis::WaitersConditionVar& a_cvWaitForTasks, experis::AtomicFlag& a_shutDownImmediately);
    //~Tasks() = default;

    void operator()();

private:
    WaitQueue& m_tasks;
    experis::WaitersConditionVar& m_cvWaitForTasks;
    experis::AtomicFlag& m_shutDownImmediately;
};

} // advcpp

#endif