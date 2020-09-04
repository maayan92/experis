#include "locker.hpp"
#include "additionalStructures.hpp"
#include <iostream>

namespace advcpp {

template<typename T>
WaitableQueue<T>::WaitableQueue(size_t maxCapacity)
: m_mtSafe()
, m_cvEnque()
, m_waitableQueue()
, m_cvDeque()
, m_numOfElements(0)
, m_capacity(maxCapacity)
{
}

template<typename T>
void WaitableQueue<T>::Enque(const T& a_element)
{
    experis::MutexLocker locker(m_mtSafe);
    m_cvEnque.Wait(locker, experis::ObjectFuncExecutor<WaitableQueue<T>, &WaitableQueue<T>::isFull>(*this));
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
bool WaitableQueue<T>::isFull() const
{
    return (m_numOfElements == m_capacity);
}

} // advcpp