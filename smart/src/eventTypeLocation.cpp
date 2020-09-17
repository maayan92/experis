#include "eventTypeLoc.hpp"

namespace smart_house {

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