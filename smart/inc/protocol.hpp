#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <string>
#include "typedefs.hpp"

namespace smart_house {

struct SensorInfo {

    SensorInfo(const experis::DeviceId& a_deviceId, const std::string& a_data, tm* a_time)
    : m_deviceId(a_deviceId)
    , m_data(a_data)
    , m_time(a_time)
    {}

    SensorInfo()
    : m_deviceId()
    , m_data()
    , m_time()
    {
        time_t currentTime = time(NULL);
        m_time = localtime(&currentTime);
    }

    experis::DeviceId m_deviceId;
    std::string m_data;
    tm* m_time;
};

class Protocol {
public:
    //Protocol() = default;

    static void Pack(std::string& a_msg, const SensorInfo& a_info);
    static void UnPack(const std::string& a_msg, SensorInfo& a_info);

private:
    ~Protocol();
};

} // smart_house

#endif