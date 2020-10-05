#include "protocol.hpp"
#include <cstring>
using namespace std;

namespace smart_house {

static const size_t TIME_BUFFER_SIZE = 20;

void Protocol::Pack(std::string& a_msg, const SensorInfo& a_info)
{
    a_msg += 1;
    a_msg += 's';

    a_msg += a_info.m_deviceId.size();
    a_msg += a_info.m_deviceId;

    char buffer[TIME_BUFFER_SIZE];
 	strftime(buffer, sizeof(buffer), "%H:%M:%S %d-%m-%Y", a_info.m_time);

    a_msg += strlen(buffer);
    a_msg += buffer;

    a_msg += a_info.m_data.size();
    a_msg += a_info.m_data;

    a_msg[0] = a_msg.size() - 2;
}

void Protocol::UnPack(const string& a_msg, SensorInfo& a_result)
{
    size_t pos = 2;
    a_result.m_deviceId = string(a_msg, pos + 1, a_msg[pos]);

    pos += a_msg[pos] + 1;
 	strptime(string(a_msg, pos + 1, a_msg[pos]).c_str(), "%H:%M:%S %d-%m-%Y", a_result.m_time);

    pos += a_msg[pos] + 1;
    a_result.m_data = string(a_msg, pos + 1, a_msg[pos]);
}

} // smart_house