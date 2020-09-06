#include "tasks.hpp"

namespace advcpp {

void Tasks::operator()()
{
    while(!m_wasShutDown.GetValue()){
        shared_ptr<experis::IRunnable> task;
        m_tasks.Deque(task);
        (*task)();
    }
}

void Tasks::Submit(shared_ptr<experis::IRunnable> a_newTask)
{
    if(!m_wasShutDown.GetValue()) {
        m_tasks.Enque(a_newTask);
    }
}

void Tasks::ShutDown()
{
    m_wasShutDown.CheckAndSet();
}

} // advcpp