#include "absSensor.hpp"

namespace smart_house {

Sensor::~Sensor()
{}

void Sensor::Notify(const Event& a_newEvent)
{
    (void)a_newEvent;
}

} // smart_house