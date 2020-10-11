#include "configuration.hpp"
using namespace std;

namespace smart_house {

Configuration::Configuration(IParser& a_parser)
: m_devices()
, m_parser(a_parser)
{}

void Configuration::ReadFile(ifstream& a_file)
{
    while(!a_file.eof()) {
        string buffer;
        getline(a_file, buffer);
        string values;

        while(!buffer.empty() && !a_file.eof()) {
            values += buffer + "|";
            buffer.clear();
            getline(a_file, buffer);
        }
        values += buffer;
        
        Device device;
        m_parser.Parse(values, device);
        m_devices.push_back(device);
    }
}

void Configuration::GetDevices(std::vector<Device>& a_devices) const
{
    a_devices = m_devices;
}

} // smart_house