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
    for(;;){
        shared_ptr<IRunnable> task;
        m_tasks.Deque(task);
        if(!task) {
            break;
        }
        (*task)();
        MutexLocker locker(m_mutex);
        if(m_tasks.Empty()) {
            m_cvWaitForTasks.NotifyOne();
        }
    }
}

void Tasks::Submit(shared_ptr<IRunnable> a_newTask)
{
    if(!m_wasShutDown.GetValue()) {
        m_tasks.Enque(a_newTask);
    }
}

void Tasks::ShutDown()
{
    if(!m_wasShutDown.CheckAndSet()) {
        return;
    }

    MutexLocker locker(m_mutex);
    m_cvWaitForTasks.Wait(locker, ObjectFuncExecutor<Tasks, &Tasks::isNotEmpty>(*this));

    m_tasks.ShutDown();
}

bool Tasks::isNotEmpty() const
{
    return !m_tasks.Empty();
}

} // advcpp