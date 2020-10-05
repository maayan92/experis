#ifndef IPARSER_HPP
#define IPARSER_HPP

#include <string>
#include "device.hpp"

namespace smart_house {

class IParser {
public:
    virtual ~IParser();

    virtual void Parse(std::string& a_values, Device& a_device) = 0;

protected:
    IParser();
};

} // smart_house

#endif