#include "protocol.hpp"
using namespace std;

namespace smart_house {

void Protocol::Pack(std::string& a_msg, const SensorInfo& a_info)
{
    a_msg += 1;
    a_msg += 's';

    a_msg += a_info.m_deviceId.size();
    a_msg += a_info.m_deviceId;

    a_msg += a_info.m_data.size();
    a_msg += a_info.m_data;

    a_msg[0] = a_msg.size() - 2;
}

void Protocol::UnPack(const string& a_msg, SensorInfo& a_result)
{
    size_t pos = 2;
    a_result.m_deviceId = string(a_msg, pos + 1, a_msg[pos]);

    pos += a_msg[pos] + 1;
    a_result.m_data = string(a_msg, pos + 1, a_msg[pos]);
}

} // smart_house