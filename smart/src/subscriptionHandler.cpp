#include "subscriptionHandler.hpp"

namespace smart_house {

SubscriptionHandler::SubscriptionHandler(Subscriptions& a_subscriptions, SensorAgentBucket& a_sensors)
: m_subscriptions(a_subscriptions)
, m_sensors(a_sensors)
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

void SubscriptionHandler::SubscribeSensor(const experis::DeviceId& a_deviceId, IObserver* a_observer)
{
    m_sensors.AddSensor(a_deviceId, a_observer);
}

void SubscriptionHandler::UnSubscribeSensor(const experis::DeviceId& a_deviceId)
{
    m_sensors.RemoveSensor(a_deviceId);
}

} // smart_house