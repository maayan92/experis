#ifndef SUBSCRIPTION_HANDLER_HPP
#define SUBSCRIPTION_HANDLER_HPP

#include "iSubscription.hpp"
#include "subscriptions.hpp"
#include "sensorAgentBucket.hpp"

namespace smart_house {

class SubscriptionHandler : public ISubscription {
public:
    explicit SubscriptionHandler(Subscriptions& a_subscriptions, SensorAgentBucket& a_sensors);
    //virtual ~SubscriptionHandler() = default;

    virtual void Subscribe(const EventTypeLoc& a_eventTypeLocation, IObserver* a_observer);
    virtual void UnSubscribe(const EventTypeLoc& a_eventTypeLocation, IObserver* a_observer);

    virtual void Subscribe(const experis::DeviceId& a_deviceId, IObserver* a_observer);
    virtual void UnSubscribe(const experis::DeviceId& a_deviceId);

private:
    Subscriptions& m_subscriptions;
    SensorAgentBucket& m_sensors;
};

} // smart_house

#endif