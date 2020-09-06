#include "threadPool.hpp"
#include <algorithm>
using namespace advcpp;
using namespace experis;

class ShutDownTask : public IRunnable {
public:
    virtual void operator()() {
    }
};

ThreadPool::ThreadPool(size_t a_numOfThread)
: m_threads()
, m_tasks(new Tasks())
{
    m_threads.reserve(a_numOfThread);
    try {
        for(size_t i = 0 ; i < a_numOfThread ; ++i) {
            shared_ptr<Thread<Tasks> > shrPtr(new Thread<Tasks>(m_tasks));
            m_threads.push_back(shrPtr);
        }

    } catch(...) {
        m_threads.clear();
        throw;
    }
}

static void detach(shared_ptr<Thread<Tasks> > a_thread)
{
    a_thread->Detach();
}

ThreadPool::~ThreadPool()
{
    for_each(m_threads.begin(), m_threads.end(), detach);
    ShutDown();
}

void ThreadPool::Submit(shared_ptr<IRunnable> a_newTask)
{
    m_tasks->Submit(a_newTask);
}

void ThreadPool::AddNewThread()
{
    shared_ptr<Thread<Tasks> > shrPtr(new Thread<Tasks>(m_tasks));
    m_threads.push_back(shrPtr);
}

void ThreadPool::ShutDown()
{
    shared_ptr<IRunnable> newTask(new ShutDownTask());
    for(size_t i = 0 ; i < m_threads.size() ; ++i) {
        m_tasks->Submit(newTask);
    }
    m_tasks->ShutDown();
}