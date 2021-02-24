#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "iObserver.hpp"

namespace smart_house {

class Sensor : public IObserver {
public:
    virtual ~Sensor() = 0;
    
    virtual void Notify(const Event& a_newEvent);
    virtual void CreateEvent(const SensorInfo& a_info, struct Event& a_event) = 0;

};

} // smart_house

#endif