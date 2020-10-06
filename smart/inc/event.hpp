#ifndef EVENT_HPP
#define EVENT_HPP

#include <ostream>
#include <ctime>
#include "iPayload.hpp"
#include "eventTypeLoc.hpp"
#include "shared_ptr.hpp"

namespace smart_house {

struct Event {
    
    bool IsNotValid() const;
    bool operator==(Event const& a_event);
    
    tm* m_timestamp;
    advcpp::shared_ptr<IPayload> m_data;
    EventTypeLoc m_typeAndLocation;

private:
    static const EventTypeLoc emptyTypeLoc;
};

std::ostream& operator<<(std::ostream& a_os, Event& a_event);

} // smart_house

#endif
