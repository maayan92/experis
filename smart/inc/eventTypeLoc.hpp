#ifndef EVENT_TYPE_LOCATION_HPP
#define EVENT_TYPE_LOCATION_HPP

#include "location.hpp"

namespace smart_house {

struct EventTypeLoc {
    EventTypeLoc(experis::EventType& a_type, Location& a_location);
    EventTypeLoc();
    
    bool operator==(const EventTypeLoc& a_eventTypeLoc) const;
    bool operator<(const EventTypeLoc& a_eventTypeLoc) const;
    
    experis::EventType m_type;
    Location m_location;
};

} // smart_house

#endif