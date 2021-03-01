#ifndef LIGHT_1_A_2_HPP
#define LIGHT_1_A_2_HPP

#include <sstream>
#include "iSubscription.hpp"
#include "iObserver.hpp"
#include "device.hpp"
#include "fileLog.hpp"

namespace smart_house {

struct Light1a2Payload : public IPayload {
    bool m_lightOn;

    virtual void Print(std::ostream& a_os) const {
        a_os << "light 1_a_2: " << (m_lightOn ? "on" : "off") << '\n';
    }
};

struct Light1a2ConfigData {

    std::string m_iot;
    std::string m_sat;
    std::string m_bright;
    std::string m_hue;

};

//sensor + controller
class Light1a2 : public IObserver {
public:
    Light1a2(ISubscription* a_subscription, Device& a_device);
    virtual ~Light1a2();

    virtual void Notify(const Event& a_newEvent);
    virtual void CreateEvent(const SensorInfo& a_info, struct Event& a_event);

private:    
    void parseConfig();
    std::string getNextValue(const std::string& a_valName, size_t& a_begin);

private:
    ISubscription* m_subscription;
    Device m_device;
    experis::FileLog& m_log;
    std::ofstream m_logFile;
    Light1a2ConfigData m_data;
};

} // smart_house

#endif