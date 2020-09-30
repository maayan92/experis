#ifndef TEMPERATURE_PAYLOAD_HPP
#define TEMPERATURE_PAYLOAD_HPP

#include <string>
#include "iPayload.hpp"

namespace smart_house {

struct TemperaturePayload : public IPayload {

    double m_currentTemp;
    bool m_tempRising;

};

} // smart_house

#endif