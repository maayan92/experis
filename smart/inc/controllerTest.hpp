#ifndef CONTROLLER_SMOKER_HPP
#define CONTROLLER_SMOKER_HPP

#include "iObserver.hpp"
#include "iSubscription.hpp"

namespace smart_house {

class ControllerTest : public IObserver {
public:
    explicit ControllerTest(ISubscription* a_subscription);
    //virtual ~ControllerTest() = default;
    
    virtual void Notify(const Event& a_newEvent);
    EventTypeLoc GetEventTypeLocation() const;

private:
    static const EventTypeLoc eventTLSmoke;
    static const EventTypeLoc eventTLEntrance;
    
    ISubscription* m_subscription;
    EventTypeLoc m_eventTypeLocation;
};

} // smart_house

#endif