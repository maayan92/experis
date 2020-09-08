#include "tasks.hpp"
#include "mutexLocker.hpp"
using namespace experis;

namespace advcpp {

Tasks::Tasks(WaitQueue& a_tasks, WaitersConditionVar& a_cvWaitForTasks, experis::AtomicFlag& a_shutDownImmediately)
: m_tasks(a_tasks)
, m_cvWaitForTasks(a_cvWaitForTasks)
, m_shutDownImmediately(a_shutDownImmediately)
{
}

void Tasks::operator()()
{
    while(!m_shutDownImmediately.GetValue()){
        shared_ptr<IRunnable> task;
        m_tasks.Deque(task);
        if(m_shutDownImmediately.GetValue()) {
            break;
        }

        try {
            (*task)();
        } catch(const EndOfWork& exc) {
            break;
        }
        catch(...) {
            throw;
        }
        
        if(m_tasks.Empty()) {
            m_cvWaitForTasks.NotifyOne();
        }
    }
}

} // advcpp