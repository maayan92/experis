#ifndef CONTROLLER_HVAC_HPP
#define CONTROLLER_HVAC_HPP

#include <iostream>
#include <fstream>
#include "iSubscription.hpp"
#include "iObserver.hpp"

namespace smart_house {

class ControllerHVAC : public IObserver {
public:
    ControllerHVAC(ISubscription* a_subscription);
    //virtual ~ControllerHVAC() = default;

    virtual void Notify(const Event& a_newEvent);

private:
    static const EventTypeLoc testHVAC;

    ISubscription* m_subscription;
    std::ofstream m_logFile;
};

} // smart_house

#endif