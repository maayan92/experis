#include "controllerTest.hpp"
#include <iostream>
using namespace std;

namespace smart_house {

const EventTypeLoc ControllerTest::eventTLSmoke("SMOKE_DETECTED", Location("1", "room_1_a"));
const EventTypeLoc ControllerTest::eventTLEntrance("ENTRANCE_REQUEST", Location("2", "room_1_b"));

ControllerTest::ControllerTest(ISubscription* a_subscription)
: m_subscription(a_subscription)
, m_eventTypeLocation()
{
    m_subscription->Subscribe(eventTLSmoke, this);
    m_subscription->Subscribe(eventTLEntrance, this);
}

void ControllerTest::Notify(const Event& a_newEvent)
{
    if(a_newEvent.m_typeAndLocation == eventTLSmoke) {
        m_eventTypeLocation = a_newEvent.m_typeAndLocation;
    }
    else if(a_newEvent.m_typeAndLocation == eventTLEntrance) {
        m_eventTypeLocation = a_newEvent.m_typeAndLocation;
    }
}

EventTypeLoc ControllerTest::GetEventTypeLocation() const
{
    return m_eventTypeLocation;
}

} // smart_house