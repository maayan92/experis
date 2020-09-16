#ifndef EVENT_HPP
#define EVENT_HPP

#include <ctime>
#include "iPayload.hpp"
#include "eventTypeLoc.hpp"

namespace smart_house {

struct Event {

    tm* m_timestamp;
    IPayload* m_data;
    EventTypeLoc m_typeAndLocation;

};

} // smart_house

#endif