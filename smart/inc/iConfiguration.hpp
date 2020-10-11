#ifndef ICONFIGURATION_HPP
#define ICONFIGURATION_HPP

#include <fstream>
#include <vector>
#include "device.hpp"
#include "uncopyable.hpp"

namespace smart_house {

class IConfiguration : private experis::Uncopyable {
public:
    virtual ~IConfiguration();

    virtual void ReadFile(std::ifstream& a_file) = 0;
    virtual void GetDevices(std::vector<Device>& a_devices) const = 0;

protected:    
    IConfiguration();
};

} // smart_house

#endif