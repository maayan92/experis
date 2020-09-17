#include "subscriptions.hpp"
#include <cassert>
#include <stdexcept>
	
namespace smart_house {

void Subscriptions::Upsert(const EventTypeLoc& a_key, IObserver* a_value)
{
    assert(0 != a_value);
    m_subscribers[a_key].insert(a_value);
}

void Subscriptions::Find(const EventTypeLoc& a_key, std::set<IObserver*>& a_result) const
{
    Map::const_iterator itr = m_subscribers.find(a_key);
    if(itr == m_subscribers.end()) {
        throw std::runtime_error("failed to find the observers of this event type and location!");
    }

    a_result = itr->second;
}

} // smart_house