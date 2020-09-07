#include "threadPool.hpp"
#include "additionalStructures.hpp"
#include <algorithm>
using namespace advcpp;
using namespace experis;

ThreadPool::ThreadPool(size_t a_numOfThread)
: m_mutex()
, m_threads()
, m_tasksQueue()
, m_wasShutDown(false)
, m_cvWaitForTasks()
, m_tasks(new Tasks(m_tasksQueue, m_cvWaitForTasks))
{
    threadsInitialization(a_numOfThread);
}

ThreadPool::ThreadPool(size_t a_numOfThread, size_t a_maxCapacityOfTasks)
: m_mutex()
, m_threads()
, m_tasksQueue(a_maxCapacityOfTasks)
, m_wasShutDown(false)
, m_cvWaitForTasks()
, m_tasks(new Tasks(m_tasksQueue, m_cvWaitForTasks))
{
    threadsInitialization(a_numOfThread);   
}

static void join(shared_ptr<Thread<Tasks> > a_thread)
{
    a_thread->Join();
}

ThreadPool::~ThreadPool()
{
    ShutDown();
    for_each(m_threads.begin(), m_threads.end(), join);
}

void ThreadPool::Submit(shared_ptr<IRunnable> a_newTask)
{
    if(!m_wasShutDown.GetValue()) {
        m_tasksQueue.Enque(a_newTask);
    }
}

void ThreadPool::AddNewThread()
{
    MutexLocker locker(m_mutex);
    shared_ptr<Thread<Tasks> > shrPtr(new Thread<Tasks>(m_tasks));
    m_threads.push_back(shrPtr);
}

void ThreadPool::ShutDown()
{
    if(!m_wasShutDown.CheckAndSet()) {
        return;
    }

    MutexLocker locker(m_mutex);
    m_cvWaitForTasks.Wait(locker, ObjectFuncExecutor<ThreadPool, &ThreadPool::isNotEmpty>(*this));

    m_tasksQueue.ShutDown();
}

// private functions:

void ThreadPool::threadsInitialization(size_t a_numOfThread)
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

bool ThreadPool::isNotEmpty() const
{
    return !m_tasksQueue.Empty();
}