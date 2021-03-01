#ifndef LIGHT_1_A_1_HPP
#define LIGHT_1_A_1_HPP

#include <sstream>
#include "iSubscription.hpp"
#include "iObserver.hpp"
#include "device.hpp"
#include "fileLog.hpp"

namespace smart_house {

struct Light1a1Payload : public IPayload {
    bool m_lightOn;

    virtual void Print(std::ostream& a_os) const {
        a_os << "light 1_a_1: " << (m_lightOn ? "on" : "off") << '\n';
    }
};

//sensor + controller
class Light1a1 : public IObserver {
public:
    Light1a1(ISubscription* a_subscription, Device& a_device);
    virtual ~Light1a1();

    virtual void Notify(const Event& a_newEvent);
    virtual void CreateEvent(const SensorInfo& a_info, struct Event& a_event);

private:
    ISubscription* m_subscription;
    Device m_device;
    experis::FileLog& m_log;
    std::ofstream m_logFile;
};

} // smart_house

#endif