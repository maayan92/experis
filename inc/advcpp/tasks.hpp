#ifndef TASKS_HPP
#define TASKS_HPP

#include "runnable.hpp"
#include "shared_ptr.hpp"
#include "waitableQueue.hpp"

namespace advcpp {

class Tasks : private experis::Uncopyable {
public:
    Tasks(WaitableQueue<shared_ptr<experis::IRunnable> >& a_tasks, experis::WaitersConditionVar& a_cvWaitForTasks);
    //~Tasks() = default;

    void operator()();

private:
    experis::Mutex m_mutex;
    WaitableQueue<shared_ptr<experis::IRunnable> >& m_tasks;
    experis::WaitersConditionVar& m_cvWaitForTasks;
};

} // advcpp

#endif