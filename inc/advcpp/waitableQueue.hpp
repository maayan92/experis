#ifndef WAITABLE_QUEUE_HPP
#define WAITABLE_QUEUE_HPP

#include "mutex.hpp"
#include "atomic.hpp"
#include "conditionVariable.hpp"
#include "uncopyable.hpp"
#include <queue>
#include <iosfwd>

namespace advcpp {

template<typename T>
class WaitableQueueMT : private experis::Uncopyable {
public:
    explicit WaitableQueueMT(size_t maxCapacity = DEFAULT_MAX_CAPACITY);
    //~WaitableQueueMT() = default;

    void Enque(const T& a_element);
    T Deque();
    bool Empty() const;
    size_t Size() const;

private:
    bool isFull() const;

private:
    static const size_t DEFAULT_MAX_CAPACITY = 10000000;

    std::queue<T> m_waitableQueue;
    experis::ConditionVariable m_cvEnque;
    experis::ConditionVariable m_cvDeque;
    experis::Mutex m_mtSafe;
    experis::Atomic<size_t> m_numOfElements;
    size_t m_capacity;
};

} // advcpp

#include "inl/waitableQueue.hxx"

#endif