#include "controllerSmoke.hpp"
#include <iostream>
using namespace std;

namespace smart_house {

ControllerSmoke::ControllerSmoke(ISubscription* a_subscription)
: m_subscription(a_subscription)
, m_eventTypeLocation()
{
    EventTypeLoc eventTL;
    eventTL.m_type = "SMOKE_DETECTED";
    eventTL.m_location.m_floor = "1";
    eventTL.m_location.m_room = "room_1_a";

    m_subscription->Subscribe(eventTL, this);
}

void ControllerSmoke::Notify(const Event& a_newEvent)
{
    m_eventTypeLocation = a_newEvent.m_typeAndLocation;
}

EventTypeLoc ControllerSmoke::GetEventTypeLocation() const
{
    return m_eventTypeLocation;
}

} // smart_house