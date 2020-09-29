#ifndef SPRINKLER_PAYLOAD_HPP
#define SPRINKLER_PAYLOAD_HPP

#include <string>
#include "iPayload.hpp"

namespace smart_house {

struct SprinklerPayload : public IPayload {

    SprinklerPayload(const std::string& a_on, const std::string& a_iot)
    : m_on(a_on)
    , m_iot(a_iot)
    {}
    
    SprinklerPayload()
    : m_on()
    , m_iot()
    {}

    std::string m_on;
    std::string m_iot;

};

} // smart_house

#endif