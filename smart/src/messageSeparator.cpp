#include "messageSeparator.hpp"
using namespace std;

namespace smart_house {

void MessageSeparator::AddToMsg(const char* a_buffer)
{
    m_msg += a_buffer;
}

bool MessageSeparator::IsThereCompleteData() const
{
    return (m_msg.size() > 0) ? (size_t)m_msg[0] <= (m_msg.size() - 2) : false;
}

void MessageSeparator::GetData(std::string& a_data)
{
    a_data = string(m_msg, 0, m_msg[0] + 2);
    m_msg.erase(0, m_msg[0] + 2);
}

} // smart_house