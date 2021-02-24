#include "controllerTest.hpp"
#include <iostream>
#include <algorithm>
#include <unistd.h>
using namespace std;

namespace smart_house {

ControllerTest::ControllerTest(ISubscription* a_subscription, const vector<EventTypeLoc>& a_typeLocArr)
: m_subscription(a_subscription)
, m_eventTypeLocation()
, m_typeLocArr(a_typeLocArr)
{
    for(size_t i = 0; i < a_typeLocArr.size(); ++i) {
        m_subscription->Subscribe(a_typeLocArr[i], this);
    }
}

void ControllerTest::Notify(const Event& a_newEvent)
{
    m_eventTypeLocation = a_newEvent.m_typeAndLocation;
    usleep(10000);
}

EventTypeLoc ControllerTest::GetEventTypeLocation() const
{
    return m_eventTypeLocation;
}

void ControllerTest::CreateEvent(const SensorInfo& a_info, struct Event& a_event)
{
    (void)a_info;
    (void)a_event;
}

} // smart_house