#ifndef ISENSOR_AGENT_HPP
#define ISENSOR_AGENT_HPP

#include <string>

namespace smart_house {

class ISensorAgent {
public:
    ~ISensorAgent();

    virtual void CreateEvent(const std::string& a_data, struct Event& a_event) = 0;

protected:
    ISensorAgent();
};

} // smart_house

#endif