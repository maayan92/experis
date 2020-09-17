#ifndef CONTROLLER_SMOKER_HPP
#define CONTROLLER_SMOKER_HPP

#include "iObserver.hpp"
#include "iSubscription.hpp"

namespace smart_house {

class ControllerSmoke : public IObserver {
public:
    explicit ControllerSmoke(ISubscription* a_subscription);
    //virtual ~ControllerSmoke() = default;
    
    virtual void Notify(const Event& a_newEvent);
    EventTypeLoc GetEventTypeLocation() const;

private:
    ISubscription* m_subscription;
    EventTypeLoc m_eventTypeLocation;
};

} // smart_house

#endif