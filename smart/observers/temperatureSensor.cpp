#include <stdlib.h>     /* atof */
#include "temperatureSensor.hpp"
#include "temperaturePayload.hpp"
#include "shared_ptr.hpp"
using namespace std;
using namespace advcpp;

namespace smart_house {

TemperatureSensor::TemperatureSensor(const Device& a_deviceDetails)
: m_deviceDetails(a_deviceDetails)
{}

TemperatureSensor::TemperatureSensor()
: m_deviceDetails()
{}

void TemperatureSensor::CreateEvent(const SensorInfo& a_info, struct Event& a_event)
{
    size_t midPos = a_info.m_data.find("|");    
    shared_ptr<TemperaturePayload> data(new TemperaturePayload());

    data->m_currentTemp = atof(string(a_info.m_data.begin(), a_info.m_data.begin() + midPos).c_str());
    data->m_tempRising = (0 == string(a_info.m_data.begin() + midPos + 1, a_info.m_data.end()).compare("rising"));

    a_event.m_data = data;
    a_event.m_typeAndLocation = m_deviceDetails.m_typeLocation;
    
    a_event.m_timestamp = a_info.m_time;
}

} // smart_house