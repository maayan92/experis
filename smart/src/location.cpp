#include "location.hpp"

namespace smart_house {

bool Location::operator==(const Location& a_location) const
{
    return (m_floor == a_location.m_floor && m_room == a_location.m_room);
}

bool Location::operator<(const Location& a_location) const
{
    if(m_floor != a_location.m_floor) {
        return m_floor < a_location.m_floor;
    }
    if(m_room != a_location.m_room) {
        return m_room < a_location.m_room;
    }

    return false;
}

} // smart_house