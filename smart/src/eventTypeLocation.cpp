#include "eventTypeLoc.hpp"
using namespace experis;

namespace smart_house {

EventTypeLoc::EventTypeLoc(EventType& a_type, Location& a_location)
: m_type(a_type)
, m_location(a_location)
{
}

EventTypeLoc::EventTypeLoc()
: m_type()
, m_location()
{
}

bool EventTypeLoc::operator==(const EventTypeLoc& a_eventTypeLoc) const
{
    return (m_type == a_eventTypeLoc.m_type) &&
            (m_location == a_eventTypeLoc.m_location);
}

bool EventTypeLoc::operator<(const EventTypeLoc& a_eventTypeLoc) const
{
    if(m_type != a_eventTypeLoc.m_type) {
        return m_type < a_eventTypeLoc.m_type;
    }

    return m_location < a_eventTypeLoc.m_location;
}

} // smart_house