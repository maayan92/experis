#ifndef IEVENT_CREATOR_HPP
#define IEVENT_CREATOR_HPP

#include "iSensorAgent.hpp"
#include <string>

namespace smart_house {

class IEventCreator {
public:
    virtual ~IEventCreator();

    virtual void CreateEvent(const std::string& a_data, ISensorAgent* a_sensor) = 0;

protected:
    IEventCreator();
};

} // smart_house

#endif