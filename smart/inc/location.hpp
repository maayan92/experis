#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "typedefs.hpp"

namespace smart_house {

struct Location {

    experis::Floor m_floor;
    experis::Room m_room;

    bool operator==(const Location& a_location) const;
    bool operator<(const Location& a_location) const;
};

} // smart_house

#endif