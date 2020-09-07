#include "tasks.hpp"
#include "mutexLocker.hpp"
#include "additionalStructures.hpp"
using namespace experis;

namespace advcpp {

Tasks::Tasks(size_t a_maxCapacityOfTasks)
: m_mutex()
, m_tasks(a_maxCapacityOfTasks)
, m_wasShutDown(false)
, m_cvWaitForTasks()
{
}

Tasks::Tasks()
: m_mutex()
, m_tasks()
, m_wasShutDown(false)
, m_cvWaitForTasks()
{
}

void Tasks::operator()()
{
    while(!m_wasShutDown.GetValue()){
        shared_ptr<IRunnable> task;
        m_tasks.Deque(task);
        if(m_wasShutDown.GetValue()) {
            break;
        }
        (*task)();
        if(m_tasks.Empty()) {
            m_cvWaitForTasks.NotifyOne();
        }
    }
}

void Tasks::Submit(shared_ptr<IRunnable> a_newTask)
{
    MutexLocker locker(m_mutex);
    if(!m_wasShutDown.GetValue()) {
        m_tasks.Enque(a_newTask);
    }
}

void Tasks::ShutDown()
{
    MutexLocker locker(m_mutex);
    m_cvWaitForTasks.Wait(locker, ObjectFuncExecutor<Tasks, &Tasks::isNotEmpty>(*this));

    m_wasShutDown.CheckAndSet();
    m_tasks.ShutDown();
}

bool Tasks::isNotEmpty() const
{
    return !m_tasks.Empty();
}

} // advcpp