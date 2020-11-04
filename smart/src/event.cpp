#include "event.hpp"
using namespace std;

namespace smart_house {

const EventTypeLoc Event::emptyTypeLoc;
static const size_t TIME_BUFFER_SIZE = 20;

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

ostream& operator<<(ostream& a_os, const Event& a_event)
{
    char buffer[TIME_BUFFER_SIZE];
 	strftime(buffer, sizeof(buffer), "%H:%M:%S %d-%m-%Y", a_event.m_timestamp);

    a_os << "event: ";
    a_os << " time - " << buffer;
    a_os << " | type - " << a_event.m_typeAndLocation.m_type;
    a_os << " | location - floor - " << a_event.m_typeAndLocation.m_location.m_floor;
    a_os << " , room - " << a_event.m_typeAndLocation.m_location.m_room;
    a_os << " | data - ";
    a_event.m_data->Print(a_os);

    return a_os;
}

} // smart_house