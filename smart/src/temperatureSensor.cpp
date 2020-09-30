#include "temperatureSensor.hpp"

namespace smart_house {

TemperatureSensor::TemperatureSensor(const Device& a_deviceDetails)
: m_deviceDetails(a_deviceDetails)
{}

TemperatureSensor::TemperatureSensor()
: m_deviceDetails()
{}

void TemperatureSensor::CreateEvent(const char* a_data, struct Event& a_event)
{
    (void)a_data;
    (void)a_event;
}

} // smart_house