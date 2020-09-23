#include "subscriptionHandler.hpp"

namespace smart_house {

SubscriptionHandler::SubscriptionHandler(Subscriptions& a_subscriptions)
: m_subscriptions(a_subscriptions)
{
}

void SubscriptionHandler::Subscribe(const EventTypeLoc& a_eventTypeLocation, IObserver* a_observer)
{
    m_subscriptions.Upsert(a_eventTypeLocation, a_observer);
}

void SubscriptionHandler::UnSubscribe(const EventTypeLoc& a_eventTypeLocation, IObserver* a_observer)
{
    m_subscriptions.Remove(a_eventTypeLocation, a_observer);
}

} // smart_house