#ifndef SUBSCRIPTIONS_HPP
#define SUBSCRIPTIONS_HPP

#include <map>
#include <set>
#include "eventTypeLoc.hpp"
#include "iObserver.hpp"
#include "uncopyable.hpp"

namespace smart_house {

class Subscriptions : private experis::Uncopyable {
    typedef std::map<EventTypeLoc, std::set<IObserver*> > Map;
public:
    //Subscriptions() = default;
    //~Subscriptions() = default;

    void Upsert(const EventTypeLoc& a_key, IObserver* a_value);
    void Find(const EventTypeLoc& a_key, std::set<IObserver*>& a_result) const;

private:
    Map m_subscribers;
};

} // smart_house

#endif