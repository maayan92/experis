#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "typedefs.hpp"
#include "eventTypeLoc.hpp"

namespace smart_house {

struct Device {

    experis::DeviceId m_deviceId;
    EventTypeLoc m_typeLocation;
    experis::LogFile m_log;
    experis::Configuration m_config;

    bool operator==(const Device& a_device) const {
        return (m_deviceId == a_device.m_deviceId) &&
                (m_typeLocation == a_device.m_typeLocation) &&
                (m_log == a_device.m_log) &&
                (m_config == a_device.m_config);
    }

};

} // smart_house

#endif