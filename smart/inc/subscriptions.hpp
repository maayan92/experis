#ifndef SUBSCRIPTIONS_HPP
#define SUBSCRIPTIONS_HPP

#include <map>
#include <set>
#include "eventTypeLoc.hpp"
#include "iObserver.hpp"
#include "uncopyable.hpp"
#include "mutex.hpp"

namespace smart_house {

class Subscriptions : private experis::Uncopyable {
    typedef std::map<EventTypeLoc, std::set<IObserver*> > Map;
public:
    //Subscriptions() = default;
    //~Subscriptions() = default;

    void Upsert(const EventTypeLoc& a_key, IObserver* a_value);
    void Find(const EventTypeLoc& a_key, std::set<IObserver*>& a_result) const;
    void Remove(const EventTypeLoc& a_key, IObserver* a_value);

    size_t Size() const;

private:
    mutable experis::Mutex m_mtx;
    Map m_subscribers;
};

} // smart_house

#endif