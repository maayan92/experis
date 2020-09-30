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

};

} // smart_house

#endif