#ifndef PAYLAOD_SMOKE_HPP
#define PAYLAOD_SMOKE_HPP

#include "iPayload.hpp"

namespace smart_house {

struct PayloadSmoke : public IPayload {
    //PayloadSmoke() = default;
    //virtual ~PayloadSmoke() = default;

    virtual void Print(std::ostream& a_os) const
    {
        a_os << "smoke\n";
    }

};

} // smart_house

#endif