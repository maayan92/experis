#include "event.hpp"

namespace smart_house {

const EventTypeLoc Event::emptyTypeLoc;

bool Event::IsNotValid() const
{
    return m_typeAndLocation == emptyTypeLoc;
}

bool Event::operator==(Event const& a_event)
{
    return (m_data == a_event.m_data) &&
            (m_timestamp == a_event.m_timestamp) &&
            (m_typeAndLocation == a_event.m_typeAndLocation);
}

} // smart_house