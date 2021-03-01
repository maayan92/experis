#include "parser.hpp"
using namespace std;

namespace smart_house {

static void GetNextValue(string& a_values, const string& a_type, string& a_result)
{
    size_t valuePos = 0;
    size_t start = 0;
    size_t size = a_type.size();

    while((start - valuePos - size) > 2) {
        valuePos = a_values.find(a_type, valuePos + 1);
        if(string::npos == valuePos) {
            return;
        }

        start = a_values.find("=", valuePos) + 1;
    }

    if(a_values[start] == ' ') {
        ++start;
    }

    size_t end = a_values.find("|", start);
    a_result = string(a_values, start, end - start);
}

void Parser::Parse(string& a_values, Device& a_device)
{
    size_t start = a_values.find("[");
    start += (' ' == a_values[start + 1]) ? 2 : 1;
    size_t end = a_values.find("]");
    if(' ' == a_values[end - 1]) {
        --end;
    }
    a_device.m_deviceId = string(a_values, start, end - start);

    GetNextValue(a_values, "type", a_device.m_typeLocation.m_type);
    GetNextValue(a_values, "room", a_device.m_typeLocation.m_location.m_room);
    GetNextValue(a_values, "floor", a_device.m_typeLocation.m_location.m_floor);
    GetNextValue(a_values, "log", a_device.m_log);
    a_device.m_log += "_log.txt";
    GetNextValue(a_values, "config", a_device.m_config);
}

} // smart_house