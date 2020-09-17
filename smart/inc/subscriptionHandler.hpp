#ifndef SUBSCRIPTION_HANDLER_HPP
#define SUBSCRIPTION_HANDLER_HPP

#include "iSubscription.hpp"
#include "subscriptions.hpp"

namespace smart_house {

class SubscriptionHandler : public ISubscription {
public:
    explicit SubscriptionHandler(Subscriptions& a_subscriptions);
    //virtual ~SubscriptionHandler() = default;

    virtual void Subscribe(const EventTypeLoc& a_eventTypeLocation, IObserver* a_observer);
    //virtual void UnSubscribe(const EventTypeLoc& a_eventTypeLocation, const IObserver* a_controller);

private:
    Subscriptions& m_subscriptions;
};

} // smart_house

#endif