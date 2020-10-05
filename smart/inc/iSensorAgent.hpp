#ifndef ISENSOR_AGENT_HPP
#define ISENSOR_AGENT_HPP

#include <string>
#include "protocol.hpp"

namespace smart_house {

class ISensorAgent {
public:
    ~ISensorAgent();

    virtual void CreateEvent(const SensorInfo& a_info, struct Event& a_event) = 0;

protected:
    ISensorAgent();
};

} // smart_house

#endif