#ifndef CONTROLLER_HVAC_HPP
#define CONTROLLER_HVAC_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include "iSubscription.hpp"
#include "controller.hpp"

namespace smart_house {

class ControllerHVAC : public Controller {
public:
    ControllerHVAC(ISubscription* a_subscription, std::vector<EventTypeLoc>& a_typeLoc);
    virtual ~ControllerHVAC();

    virtual void Notify(const Event& a_newEvent);

private:
    ISubscription* m_subscription;
    std::ofstream m_logFile;
    std::vector<EventTypeLoc>& m_typeLoc;
};

} // smart_house

#endif