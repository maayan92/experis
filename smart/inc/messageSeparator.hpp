#ifndef MESSAGE_SEPARATOR_HPP
#define MESSAGE_SEPARATOR_HPP

#include <string>

namespace smart_house {

class MessageSeparator {
public:
    //MessageSeparator() = default;
    //~MessageSeparator() = default;

    void AddToMsg(const char* a_buffer);
    bool IsThereCompleteData() const;
    void GetData(std::string& a_data);

private:
    std::string m_msg;
};

} // smart_house

#endif