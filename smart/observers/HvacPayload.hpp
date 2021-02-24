#ifndef HVAC_PAYLOAD_HPP
#define HVAC_PAYLOAD_HPP

#include <string>
#include "iPayload.hpp"

namespace smart_house {

struct HvacPayload : public IPayload {

    HvacPayload(const std::string& a_iot, const std::string& a_tmp, const std::string& a_shutdown)
    : m_iot(a_iot)
    , m_tmp(a_tmp)
    , m_shutdown(a_shutdown)
    {}
    
    HvacPayload()
    : m_iot()
    , m_tmp()
    , m_shutdown()    
    {}

    virtual void Print(std::ostream& a_os) const
    {
        a_os << "iot: " << m_iot;
        a_os << "| tmp: " << m_tmp;
        a_os << "| shut down: " << m_shutdown;
        a_os << '\n';
    }

    std::string m_iot;
    std::string m_tmp;
    std::string m_shutdown;

};

} // smart_house

#endif