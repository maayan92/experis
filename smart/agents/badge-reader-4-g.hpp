#ifndef BEDGE_READER_4_G_HPP
#define BEDGE_READER_4_G_HPP

#include <sstream>
#include "iSubscription.hpp"
#include "absSensor.hpp"
#include "device.hpp"
#include "fileLog.hpp"
#include "clientTcp.hpp"

namespace smart_house {

struct BadgeReader4gPayload : public IPayload {

    std::string m_employeeId;
    std::string m_lockId;
    std::string m_token;

    virtual void Print(std::ostream& a_os) const {
        a_os << "badge reader 4_g: badge info: employee id: " << m_employeeId
            << "lock id: " << m_lockId << "token: " << m_token << '\n';
    }
};

//sensor
class BadgeReader4g : public Sensor {
public:
    BadgeReader4g(ISubscription* a_subscription, Device& a_device);
    virtual ~BadgeReader4g();

    virtual void CreateEvent(const SensorInfo& a_info, struct Event& a_event);

private:
    std::string getNextValue(const std::string& a_valName, size_t& a_begin);
    void parseConfig();

private:
    ISubscription* m_subscription;
    Device m_device;
    experis::FileLog& m_log;
    std::ofstream m_logFile;
};

} // smart_house

#endif