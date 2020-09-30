#include "event.hpp"

namespace smart_house {

const EventTypeLoc Event::emptyTypeLoc;

bool Event::IsNotValid() const
{
    return m_typeAndLocation == emptyTypeLoc;
}

} // smart_house