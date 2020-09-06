#include "locker.hpp"
#include "additionalStructures.hpp"
#include <iostream>

namespace advcpp {
/*
template<typename Obj, bool(Obj::*Func)() const, bool(Obj::*FuncSecond)() const>
struct WasShutDown {
    WasShutDown(const Obj& a_object)
    : m_ofExecutor(a_object)
    , m_object(a_object)
    {}

    bool operator()() {
        return m_ofExecutor() && (m_object.*FuncSecond)();
    }

private:
    experis::ObjectFuncExecutor<Obj, Func> m_ofExecutor;
    const Obj& m_object;
};
*/
template<typename T>
WaitableQueue<T>::WaitableQueue(size_t maxCapacity)
: m_mtSafe()
, m_cvEnque()
, m_waitableQueue()
, m_cvDeque()
, m_numOfElements(0)
, m_capacity(maxCapacity)
, m_shutDown(false)
{
}

template<typename T>
void WaitableQueue<T>::Enque(const T& a_element)
{
    experis::MutexLocker locker(m_mtSafe);
    m_cvEnque.Wait(locker, experis::ObjectFuncExecutor<WaitableQueue<T>, &WaitableQueue<T>::isFull>(*this));
    //m_cvEnque.Wait(locker, WasShutDown<WaitableQueue<T>, &WaitableQueue<T>::isFull, &WaitableQueue<T>::wasNotShutDown>(*this));
    size_t currentSize = m_numOfElements;
    
    assert(!isFull());
    m_waitableQueue.push(a_element);
    ++m_numOfElements;
    m_cvDeque.NotifyOne();

    assert(m_waitableQueue.size() == m_numOfElements);
    assert((currentSize + 1) == m_numOfElements);
}

template<typename T>
void WaitableQueue<T>::Deque(T& a_element)
{
    experis::MutexLocker locker(m_mtSafe);
    m_cvDeque.Wait(locker, experis::ObjectFuncExecutor<WaitableQueue<T>, &WaitableQueue<T>::Empty>(*this));
    size_t currentSize = m_numOfElements;
    
    assert(!Empty());
    a_element = m_waitableQueue.front();
    m_waitableQueue.pop();
    --m_numOfElements;
    m_cvEnque.NotifyOne();

    assert(m_waitableQueue.size() == m_numOfElements);
    assert((currentSize - 1) == m_numOfElements);
}

template<typename T>
bool WaitableQueue<T>::Empty() const
{
    return (0 == Size());
}

template<typename T>
size_t WaitableQueue<T>::Size() const
{
    return m_numOfElements;
}
template<typename T>
void WaitableQueue<T>::ShutDown()
{
    m_shutDown.CheckAndSet();
    m_cvEnque.NotifyAll();
    m_cvDeque.NotifyAll();
}

// private functions:

template<typename T>
bool WaitableQueue<T>::isFull() const
{
    return (m_numOfElements == m_capacity);
}

template<typename T>
bool WaitableQueue<T>::wasNotShutDown() const
{
    return !m_shutDown.GetValue();
}

} // advcpp