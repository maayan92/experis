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

    virtual void Print(std::ostream& a_os) const
    {
        a_os << "on: " << m_on;
        a_os << "| iot: " << m_iot;
        a_os << '\n';
    }

    std::string m_on;
    std::string m_iot;

};

} // smart_house

#endif