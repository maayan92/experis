#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "typedefs.hpp"

namespace smart_house {

struct Location {
    Location(experis::Floor& a_floor, experis::Room& a_room);
    Location();
    
    bool operator==(const Location& a_location) const;
    bool operator<(const Location& a_location) const;
    
    experis::Floor m_floor;
    experis::Room m_room;
};

} // smart_house

#endif