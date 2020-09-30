#include "subscriptions.hpp"
#include "mutexLocker.hpp"
#include <cassert>
#include <stdexcept>
using namespace std;
using namespace experis;

namespace smart_house {

void Subscriptions::Upsert(const EventTypeLoc& a_key, IObserver* a_value)
{
    assert(0 != a_value);
    
    MutexLocker locker(m_mtx);    
    m_subscribers[a_key].insert(a_value);
}

void Subscriptions::Find(const EventTypeLoc& a_key, set<IObserver*>& a_result) const
{
    MutexLocker locker(m_mtx);
    
    Map::const_iterator itr = m_subscribers.find(a_key);
    if(itr != m_subscribers.end()) {
        a_result = itr->second;
    }
}

void Subscriptions::Remove(const EventTypeLoc& a_key, IObserver* a_value)
{
    MutexLocker locker(m_mtx);
    
    Map::iterator itr = m_subscribers.find(a_key);
    if(itr != m_subscribers.end()) {
        itr->second.erase(a_value);
    }
}

size_t Subscriptions::Size() const
{
    MutexLocker locker(m_mtx);
    
    size_t size = 0;
    for(Map::const_iterator itr = m_subscribers.begin(); itr != m_subscribers.end(); ++itr) {
        size += itr->second.size();
    }
    
    return size;
}

} // smart_house
