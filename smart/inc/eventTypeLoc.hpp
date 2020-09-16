#ifndef EVENT_TYPE_LOCATION_HPP
#define EVENT_TYPE_LOCATION_HPP

#include "location.hpp"

namespace smart_house {

struct EventTypeLoc {

    experis::EventType m_type;
    Location m_location;
        
};

} // smart_house

#endif