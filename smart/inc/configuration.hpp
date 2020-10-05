#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <fstream>
#include <vector>
#include "iParser.hpp"

namespace smart_house {

class Configuration {
public:
    Configuration(IParser& a_parser);
    //~Configuration();

    void ReadFile(std::ifstream& a_file);
    std::vector<Device> GetDevices() const;

private:
    std::vector<Device> m_devices;
    IParser& m_parser;
};

} // smart_house

#endif