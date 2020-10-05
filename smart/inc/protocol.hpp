#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <string>
#include "typedefs.hpp"

namespace smart_house {

struct SensorInfo {

    SensorInfo(const experis::DeviceId& a_deviceId, const std::string& a_data)
    : m_deviceId(a_deviceId)
    , m_data(a_data)
    {}

    SensorInfo()
    : m_deviceId()
    , m_data()
    {}

    experis::DeviceId m_deviceId;
    std::string m_data;

};

class Protocol {
public:
    //Protocol() = default;

    static void Pack(std::string& a_msg, const SensorInfo& a_info);
    static void UnPack(const std::string& a_msg, SensorInfo& a_info);

};

} // smart_house

#endif