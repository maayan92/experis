#include "tasks.hpp"
#include "mutexLocker.hpp"
using namespace experis;

namespace advcpp {

Tasks::Tasks(WaitQueue& a_tasks, experis::AtomicFlag& a_shutDownImmediately)
: m_tasks(a_tasks)
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
        //TODO: fix the thread pool it must not crash the app
        catch(...) {
            throw;
        }
    }
}

} // advcpp
