#ifndef SECURITY_4_G_HPP
#define SECURITY_4_G_HPP

#include <sstream>
#include "iSubscription.hpp"
#include "iObserver.hpp"
#include "device.hpp"
#include "fileLog.hpp"
#include "clientTcp.hpp"

namespace smart_house {

struct Security4gPayload : public IPayload {

    std::string m_lockId;
    bool m_validBadge;

    virtual void Print(std::ostream& a_os) const {
        a_os << "badge reader 4_g: " << (!m_validBadge ? "not valid secure signature!" : "door is openning!") << '\n';
    }
};

struct Security4gConfigData {

    std::string m_token;
    std::string m_event;
};

//sensor + controller
class Security4g : public IObserver {
public:
    Security4g(ISubscription* a_subscription, Device& a_device);
    virtual ~Security4g();

    virtual void Notify(const Event& a_newEvent);
    virtual void CreateEvent(const SensorInfo& a_info, struct Event& a_event);

private:
    std::string getNextValue(const std::string& a_valName, size_t& a_end);
    void parseConfig();

private:
    ISubscription* m_subscription;
    Device m_device;
    experis::FileLog& m_log;
    std::ofstream m_logFile;
    Security4gConfigData m_data;
    experis::ClientTcp m_sensor;
};

} // smart_house

#endif