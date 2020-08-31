#include "atomic.hpp"

namespace experis {

AtomicFlag::AtomicFlag(bool a_value)
: m_value(a_value)
{
}

bool AtomicFlag::CheckAndSet()
{
    return __sync_bool_compare_and_swap(&m_value, 0, 1);
}

bool AtomicFlag::GetValue() const
{
    return __sync_fetch_and_add(&m_value, 0);
}

} // experis