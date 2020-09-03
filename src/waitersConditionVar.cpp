#include "waitersConditionVar.hpp"

namespace experis {

void WaitersConditionVar::NotifyOne()
{
    if(0 < m_countWaiting) {
        ConditionVariable::NotifyOne();
    }
}

void WaitersConditionVar::NotifyAll()
{
    if(0 < m_countWaiting) {
        ConditionVariable::NotifyAll();
    }
}

} // experis