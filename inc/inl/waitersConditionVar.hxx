namespace experis {

template<typename Predicate>
void WaitersConditionVar::Wait(MutexLocker& a_mutexLocker, Predicate a_predicate)
{
    ++m_countWaiting;
    ConditionVariable::Wait<Predicate>(a_mutexLocker, a_predicate);
    --m_countWaiting;
}

template<typename Predicate>
void WaitersConditionVar::Wait(Mutex& a_mutex, Predicate a_predicate)
{
    ++m_countWaiting;
    ConditionVariable::Wait<Predicate>(a_mutex, a_predicate);
    --m_countWaiting;
}

} // experis