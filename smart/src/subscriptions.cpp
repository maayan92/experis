#include "subscriptions.hpp"
#include <cassert>
#include <stdexcept>
using namespace std;

namespace smart_house {

void Subscriptions::Upsert(const EventTypeLoc& a_key, IObserver* a_value)
{
    assert(0 != a_value);
    m_subscribers[a_key].insert(a_value);
}

void Subscriptions::Find(const EventTypeLoc& a_key, set<IObserver*>& a_result) const
{
    Map::const_iterator itr = m_subscribers.find(a_key);
    if(itr != m_subscribers.end()) {
        a_result = itr->second;
    }
}

void Subscriptions::Remove(const EventTypeLoc& a_key, IObserver* a_value)
{
    Map::iterator itr = m_subscribers.find(a_key);
    if(itr != m_subscribers.end()) {
        itr->second.erase(a_value);
    }
}

size_t Subscriptions::Size() const
{
    size_t size = 0;
    for(Map::const_iterator itr = m_subscribers.begin(); itr != m_subscribers.end(); ++itr) {
        size += itr->second.size();
    }
    
    return size;
}

} // smart_house