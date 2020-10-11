#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <fstream>
#include <vector>
#include "iParser.hpp"
#include "iConfiguration.hpp"

namespace smart_house {

class Configuration : public IConfiguration {
public:
    Configuration(IParser& a_parser);
    //~Configuration();

    virtual void ReadFile(std::ifstream& a_file);
    virtual void GetDevices(std::vector<Device>& a_devices) const;

private:
    std::vector<Device> m_devices;
    IParser& m_parser;
};

} // smart_house

#endif