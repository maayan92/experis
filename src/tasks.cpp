#include "tasks.hpp"
#include "mutexLocker.hpp"
using namespace experis;

namespace advcpp {

Tasks::Tasks(WaitableQueue<shared_ptr<experis::IRunnable> >& a_tasks, experis::WaitersConditionVar& a_cvWaitForTasks)
: m_mutex()
, m_tasks(a_tasks)
, m_cvWaitForTasks(a_cvWaitForTasks)
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

} // advcpp