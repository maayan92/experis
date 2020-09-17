#include "location.hpp"
using namespace experis;

namespace smart_house {

Location::Location(Floor& a_floor, Room& a_room)
: m_floor(a_floor)
, m_room(a_room)
{
}

Location::Location()
: m_floor()
, m_room()
{
}

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