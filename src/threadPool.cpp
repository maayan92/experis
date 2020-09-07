#include "threadPool.hpp"
#include "additionalStructures.hpp"
#include <algorithm>
using namespace advcpp;
using namespace experis;

ThreadPool::ThreadPool(size_t a_numOfThread)
: m_mutex()
, m_threads()
, m_tasksQueue()
, m_shutDown(false)
, m_turnOn(true)
, m_shutDownImmediately(false)
, m_cvWaitForTasks()
, m_tasks(new Tasks(m_tasksQueue, m_cvWaitForTasks, m_shutDownImmediately))
{
    threadsInitialization(a_numOfThread);
}

ThreadPool::ThreadPool(size_t a_numOfThread, size_t a_maxCapacityOfTasks)
: m_mutex()
, m_threads()
, m_tasksQueue(a_maxCapacityOfTasks)
, m_shutDown(false)
, m_turnOn(true)
, m_shutDownImmediately(false)
, m_cvWaitForTasks()
, m_tasks(new Tasks(m_tasksQueue, m_cvWaitForTasks, m_shutDownImmediately))
{
    threadsInitialization(a_numOfThread);   
}

ThreadPool::~ThreadPool()
{
    ShutDown();
}

void ThreadPool::Submit(shared_ptr<IRunnable> a_newTask)
{
    if(!m_shutDown.GetValue()) {
        m_tasksQueue.Enque(a_newTask);
    }
}

void ThreadPool::AddThread(size_t a_numOfThreads)
{
    if(!m_shutDown.GetValue()) {
        MutexLocker locker(m_mutex);

        m_threads.reserve(m_threads.size() + a_numOfThreads);
        for(size_t i = 0 ; i < a_numOfThreads ; ++i) {
            shared_ptr<Thread<Tasks> > shrPtr(new Thread<Tasks>(m_tasks));
            m_threads.push_back(shrPtr);
        }
    }
}

void ThreadPool::ShutDown()
{
    if(!m_shutDown.CheckAndSet()) {
        return;
    }

    MutexLocker locker(m_mutex);
    m_cvWaitForTasks.Wait(locker, ObjectFuncExecutor<ThreadPool, &ThreadPool::isNotEmpty>(*this));
    
    m_shutDownImmediately.CheckAndSet();
    shutAllDown();
}

void ThreadPool::ShutDownImmediately()
{
    if(!m_shutDownImmediately.CheckAndSet() || !m_shutDown.CheckAndSet()) {
        return;
    }

    shutAllDown();
}

void ThreadPool::TurnOn(size_t a_numOfThreads)
{
    MutexLocker locker(m_mutex);
    if(!m_turnOn.CheckAndSet()) {
        return;
    }

    threadsInitialization(a_numOfThreads);
    m_shutDown.CheckAndReset();
    m_shutDownImmediately.CheckAndReset();
}

size_t ThreadPool::NumOfThread() const
{
    MutexLocker locker(m_mutex);
    return m_threads.size();
}

size_t ThreadPool::NumOfTasks() const
{
    return m_tasksQueue.Size();
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

static void join(shared_ptr<Thread<Tasks> > a_thread)
{
    a_thread->Join();
}

void ThreadPool::joinAll()
{
    for_each(m_threads.begin(), m_threads.end(), join);
}

void ThreadPool::shutAllDown()
{
    m_tasksQueue.ShutDown();
    joinAll();
    m_threads.clear();
    m_turnOn.CheckAndReset();
}