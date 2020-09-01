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
    explicit WaitableQueueMT(size_t maxCapacity = 10000000);
    //~WaitableQueueMT() = default;

    void Enque(const T& a_element);
    const T& Deque();
    bool Empty() const;
    size_t Size() const;

private:
    std::queue<T> m_waitableQueue;
    experis::ConditionVariable m_conditionVar;
    experis::Mutex m_mtSafe;
    experis::Atomic<size_t> m_numOfElements;
    size_t m_capacity;
};

} // advcpp

#include "inl/waitableQueue.hxx"

#endif