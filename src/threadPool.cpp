#include "threadPool.hpp"
#include "additionalStructures.hpp"
#include <algorithm>
#include <cassert>
using namespace std;
using namespace advcpp;
using namespace experis;

struct ShutDownExecutor : public IRunnable {
    void operator()() {
        throw EndOfWork();
    }
};

struct RemoveThreadExecutor : public IRunnable {
    RemoveThreadExecutor(WaitableQueue<pthread_t>& a_removingQueue)
    : m_removingQueue(a_removingQueue)
    {}

    void operator()() {
        m_removingQueue.Enque(pthread_self());
        throw EndOfWork();
    }

private:
    WaitableQueue<pthread_t>& m_removingQueue;
};

struct CheckThreadId {
    CheckThreadId(pthread_t a_val)
    : m_val(a_val)
    {}

    bool operator()(shared_ptr<advcpp::Thread<Tasks> > a_thread) {
        return (*a_thread) == m_val;
    }

private:
    pthread_t m_val;
};

// CTOR/DTOR

ThreadPool::ThreadPool(size_t a_numOfThread)
: m_mutex()
, m_tasks(new Tasks(m_tasksQueue, m_shutDownImmediately))
, m_tasksQueue()
, m_shutDown(false)
, m_turnOn(true)
, m_shutDownImmediately(false)
, m_threads(m_tasks, a_numOfThread)
{
}

ThreadPool::ThreadPool(size_t a_numOfThread, size_t a_maxCapacityOfTasks)
: m_mutex()
, m_tasks(new Tasks(m_tasksQueue, m_shutDownImmediately))
, m_tasksQueue(a_maxCapacityOfTasks)
, m_shutDown(false)
, m_turnOn(true)
, m_shutDownImmediately(false)
, m_threads(m_tasks, a_numOfThread)
{
}

ThreadPool::~ThreadPool()
{
    ShutDown();
}

// mem functions

void ThreadPool::Submit(shared_ptr<IRunnable> a_newTask)
{
    if(!m_shutDown.GetValue()) {
        m_tasksQueue.Enque(a_newTask);
    }
}

void ThreadPool::AddThread(size_t a_numOfThreads)
{
    if(!m_shutDown.GetValue()) {
        m_threads.AddThreads(m_tasks, a_numOfThreads);
    }
}

void ThreadPool::RemoveThread(size_t a_numOfThreads)
{
    if(a_numOfThreads > NumOfThread()) {
        throw ExcNumOfThreadTooBig();
    }

    MutexLocker locker(m_mutex);
    WaitableQueue<pthread_t> removingQueue(a_numOfThreads);
    setRemovingTasks(a_numOfThreads, removingQueue);

    removeTheThreads(a_numOfThreads, removingQueue);
}

void ThreadPool::ShutDown()
{
    if(!m_shutDown.CheckAndSet()) {
        return;
    }

    for(size_t i = 0 ; i < m_threads.NumOfThread() ; ++i) {
        shared_ptr<ShutDownExecutor> shutDownTask(new ShutDownExecutor());
        m_tasksQueue.Enque(shutDownTask);
    }
    
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

    m_threads.AddThreads(m_tasks, a_numOfThreads);
    m_shutDown.CheckAndReset();
    m_shutDownImmediately.CheckAndReset();
}

size_t ThreadPool::NumOfThread() const
{
    return m_threads.NumOfThread();
}

size_t ThreadPool::NumOfTasks() const
{
    return m_tasksQueue.Size();
}

// private functions:

bool ThreadPool::isNotEmpty() const
{
    return !m_tasksQueue.Empty();
}

void ThreadPool::shutAllDown()
{
    m_threads.JoinAll();
    m_threads.Clear();
    m_turnOn.CheckAndReset();
}

void ThreadPool::setRemovingTasks(size_t a_numOfThreads, WaitableQueue<pthread_t>& a_removingQueue)
{
    for(size_t i = 0 ; i < a_numOfThreads ; ++i) {
        shared_ptr<RemoveThreadExecutor> removeTasks(new RemoveThreadExecutor(a_removingQueue));
        m_tasksQueue.EnqueFront(removeTasks);
    }
}

void ThreadPool::removeTheThreads(size_t a_numOfThreads, WaitableQueue<pthread_t>& a_removingQueue)
{
    for(size_t i = 0 ; i < a_numOfThreads ; ++i) {
        pthread_t val;
        a_removingQueue.Deque(val);
        
        m_threads.RemoveThread(val);
    }
}