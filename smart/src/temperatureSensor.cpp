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

void TemperatureSensor::CreateEvent(const string& a_data, struct Event& a_event)
{
    size_t midPos = a_data.find("|");    
    shared_ptr<TemperaturePayload> data(new TemperaturePayload());

    data->m_currentTemp = atof(string(a_data.begin(), a_data.begin() + midPos).c_str());
    data->m_tempRising = (0 == string(a_data.begin() + midPos + 1, a_data.end()).compare("rising"));

    a_event.m_data = data;
    a_event.m_typeAndLocation = m_deviceDetails.m_typeLocation;
    
    time_t currentTime;
    time(&currentTime);
    a_event.m_timestamp = localtime(&currentTime); /// ??
}

} // smart_house