#ifndef WAITABLE_QUEUE_HPP
#define WAITABLE_QUEUE_HPP

#include "mutex.hpp"
#include "atomic.hpp"
#include "waitersConditionVar.hpp"
#include "uncopyable.hpp"
#include <deque>
#include <iosfwd>

namespace advcpp {

template<typename T>
class WaitableQueue : private experis::Uncopyable {
public:
    explicit WaitableQueue(size_t maxCapacity = DEFAULT_MAX_CAPACITY);
    //~WaitableQueue() = default;

    void Enque(const T& a_element);
    void EnqueFront(const T& a_element);
    void Deque(T& a_element);
    bool Empty() const;
    size_t Size() const;

    // after calling this function no Enqueue or Dequeue is possible.
    void ShutDown();

private:
    bool isFull() const;
    bool wasNotShutDown() const;
    void enque(const T& a_element, bool a_pushBack);

private:
    static const size_t DEFAULT_MAX_CAPACITY = 10000000;
    typedef std::deque<T> Queue;

    experis::Mutex m_mtSafe;
    experis::WaitersConditionVar m_cvEnque;
    Queue m_waitableQueue;
    experis::WaitersConditionVar m_cvDeque;
    experis::Atomic<size_t> m_numOfElements;
    size_t m_capacity;
    experis::AtomicFlag m_shutDown;
};

} // advcpp

#include "inl/waitableQueue.hxx"

#endif