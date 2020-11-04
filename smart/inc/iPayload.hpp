#ifndef IPAYLOAD_HPP
#define IPAYLOAD_HPP

#include <iostream>
#include <fstream>

namespace smart_house {

class IPayload {
public:
    virtual ~IPayload() = 0;

    virtual void Print(std::ostream& a_os) const = 0;

protected:
    IPayload();
};

} // smart_house

#endif