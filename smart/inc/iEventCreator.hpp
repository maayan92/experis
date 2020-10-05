#ifndef IEVENT_CREATOR_HPP
#define IEVENT_CREATOR_HPP

#include "iSensorAgent.hpp"
#include <string>

namespace smart_house {

class IEventCreator {
public:
    virtual ~IEventCreator();

    virtual void CreateEvent(const SensorInfo& a_info, ISensorAgent* a_sensor) = 0;

protected:
    IEventCreator();
};

} // smart_house

#endif