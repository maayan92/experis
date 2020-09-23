#ifndef IPAYLOAD_HPP
#define IPAYLOAD_HPP

namespace smart_house {

class IPayload {
public:
    virtual ~IPayload() = 0;

protected:
    IPayload();
};

} // smart_house

#endif