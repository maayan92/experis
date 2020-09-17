#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "typedefs.hpp"

namespace smart_house {

struct Location {
    Location(const experis::Floor& a_floor, const experis::Room& a_room);
    Location();
    
    bool operator==(const Location& a_location) const;
    bool operator<(const Location& a_location) const;
    
    experis::Floor m_floor;
    experis::Room m_room;
};

} // smart_house

#endif