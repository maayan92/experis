#ifndef SUBSCRIBERS_FINDER_HPP
#define  SUBSCRIBERS_FINDER_HPP

#include "ISubscribersFinder.hpp"
#include "subscriptions.hpp"

namespace smart_house {

class SubscribersFinder {
public:
    SubscribersFinder(Subscriptions& a_subscriptions);
    //~SubscribersFinder() = default;

    virtual void FindControllers(const EventTypeLoc& a_typeLocation, std::set<IObserver*>& a_observers);

private:
    void findByTypeLocation(const experis::EventType& a_type, const Location& a_location, std::set<IObserver*>& a_observers);

private:
    Subscriptions& m_subscriptions;
};

} // smart_house

#endif