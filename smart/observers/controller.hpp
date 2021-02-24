#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "iObserver.hpp"

namespace smart_house {

class Controller : public IObserver {
public:
    virtual ~Controller() = 0;
    
    virtual void Notify(const Event& a_newEvent) = 0;
    virtual void CreateEvent(const SensorInfo& a_info, struct Event& a_event);

};

} // smart_house

#endif