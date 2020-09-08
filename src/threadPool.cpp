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

ThreadPool::ThreadPool(size_t a_numOfThread)
: m_mutex()
, m_threads()
, m_tasksQueue()
, m_shutDown(false)
, m_turnOn(true)
, m_shutDownImmediately(false)
, m_tasks(new Tasks(m_tasksQueue, m_shutDownImmediately))
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
, m_tasks(new Tasks(m_tasksQueue, m_shutDownImmediately))
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

void ThreadPool::RemoveThread(size_t a_numOfThreads)
{
    if(!m_shutDown.GetValue()) {
        MutexLocker locker(m_mutex);
        WaitableQueue<pthread_t> removingQueue(a_numOfThreads);
        setRemovingTasks(a_numOfThreads, removingQueue);

        for(size_t i = 0 ; i < a_numOfThreads ; ++i) {
            pthread_t val;
            removingQueue.Deque(val);
            vector<shared_ptr<advcpp::Thread<Tasks> > >::iterator itr = find_if(m_threads.begin(), m_threads.end(), CheckThreadId(val));
            assert(itr != m_threads.end());
            (*itr)->Join();
            m_threads.erase(itr);
        }
    }
}

void ThreadPool::ShutDown()
{
    if(!m_shutDown.CheckAndSet()) {
        return;
    }

    for(size_t i = 0 ; i < m_threads.size() ; ++i) {
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
    joinAll();
    m_threads.clear();
    m_turnOn.CheckAndReset();
}

void ThreadPool::setRemovingTasks(size_t a_numOfThreads, WaitableQueue<pthread_t>& a_removingQueue)
{
    for(size_t i = 0 ; i < a_numOfThreads ; ++i) {
        shared_ptr<RemoveThreadExecutor> removeTasks(new RemoveThreadExecutor(a_removingQueue));
        m_tasksQueue.EnqueFront(removeTasks);
    }
}