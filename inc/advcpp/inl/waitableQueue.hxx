#include "locker.hpp"
#include <iostream>

namespace advcpp {

struct CompareSize {
    experis::Atomic<size_t>& m_size;
    size_t m_compareSize;
    bool operator()() {
        return (m_size == m_compareSize);
    }
};

template<typename T>
WaitableQueueMT<T>::WaitableQueueMT(size_t maxCapacity)
: m_waitableQueue()
, m_conditionVar()
, m_mtSafe()
, m_numOfElements(0)
, m_capacity(maxCapacity)
{
}

template<typename T>
void WaitableQueueMT<T>::Enque(const T& a_element)
{
    experis::MutexLocker locker(m_mtSafe);
    CompareSize isFull = { m_numOfElements, m_capacity };
    m_conditionVar.Wait(locker, isFull);
    size_t currentSize = m_numOfElements;
    
    m_waitableQueue.push(a_element);
    ++m_numOfElements;
    m_conditionVar.NotifyOne();

    assert(m_waitableQueue.size() == m_numOfElements);
    assert((currentSize + 1) == m_numOfElements);
}

template<typename T>
T WaitableQueueMT<T>::Deque()
{
    experis::MutexLocker locker(m_mtSafe);
    CompareSize isEmpty = { m_numOfElements, 0 };
    m_conditionVar.Wait(locker, isEmpty);
    size_t currentSize = m_numOfElements;
    assert(!Empty());

    T element = m_waitableQueue.front();
    m_waitableQueue.pop();
    --m_numOfElements;
    m_conditionVar.NotifyOne();

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

} // advcpp