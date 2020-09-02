#include "locker.hpp"
#include "additionalStructures.hpp"
#include <iostream>

namespace advcpp {

template<typename T>
WaitableQueueMT<T>::WaitableQueueMT(size_t maxCapacity)
: m_waitableQueue()
, m_cvEnque()
, m_cvDeque()
, m_mtSafe()
, m_numOfElements(0)
, m_capacity(maxCapacity)
{
}

template<typename T>
void WaitableQueueMT<T>::Enque(const T& a_element)
{
    experis::MutexLocker locker(m_mtSafe);
    m_cvEnque.Wait(locker, experis::ObjectFuncExecutor<WaitableQueueMT<T>, &WaitableQueueMT<T>::isFull>(*this));
    size_t currentSize = m_numOfElements;
    
    m_waitableQueue.push(a_element);
    ++m_numOfElements;
    m_cvDeque.NotifyOne();

    assert(m_waitableQueue.size() == m_numOfElements);
    assert((currentSize + 1) == m_numOfElements);
}

template<typename T>
T WaitableQueueMT<T>::Deque()
{
    experis::MutexLocker locker(m_mtSafe);
    m_cvDeque.Wait(locker, experis::ObjectFuncExecutor<WaitableQueueMT<T>, &WaitableQueueMT<T>::Empty>(*this));
    size_t currentSize = m_numOfElements;
    assert(!Empty());

    T element = m_waitableQueue.front();
    m_waitableQueue.pop();
    --m_numOfElements;
    m_cvEnque.NotifyOne();

    assert(m_waitableQueue.size() == m_numOfElements);
    assert((currentSize - 1) == m_numOfElements);
    return element;
}

template<typename T>
bool WaitableQueueMT<T>::Empty() const
{
    return (0 == Size());
}

template<typename T>
size_t WaitableQueueMT<T>::Size() const
{
    return m_numOfElements;
}

template<typename T>
bool WaitableQueueMT<T>::isFull() const
{
    return (m_numOfElements == m_capacity);
}

} // advcpp