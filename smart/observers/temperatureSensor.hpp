#ifndef TEMPERATURE_SENSOR_HPP
#define TEMPERATURE_SENSOR_HPP

#include "absSensor.hpp"
#include "device.hpp"

namespace smart_house {

class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(const Device& a_deviceDetails);
    TemperatureSensor();
    //virtual ~TemperatureSensor() = default;

    virtual void CreateEvent(const SensorInfo& a_info, struct Event& a_event);

public:
    Device m_deviceDetails;
};

} // smart_house

#endif