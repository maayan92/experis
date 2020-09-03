#ifndef WAITERS_CONDITION_VARIABLE_HPP
#define WAITERS_CONDITION_VARIABLE_HPP

#include "atomic.hpp"
#include "conditionVariable.hpp"

namespace experis {

class WaitersConditionVar : private ConditionVariable {
public:
    //WaitersConditionVar() = default;
    //~WaitersConditionVar() = default;

    void NotifyOne();
    void NotifyAll();

    template<typename Predicate>
    void Wait(MutexLocker& a_mutexLocker, Predicate a_predicate);

    template<typename Predicate>
    void Wait(Mutex& a_mutex, Predicate a_predicate);

private:
    Atomic<size_t> m_countWaiting;
};

} // experis

#include "inl/waitersConditionVar.hxx"

#endif