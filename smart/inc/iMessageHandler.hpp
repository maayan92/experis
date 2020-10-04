#ifndef IMESSAGE_HANDLER_HPP
#define IMESSAGE_HANDLER_HPP

#include "uncopyable.hpp"

namespace experis {

class IMessageHandler : private Uncopyable {
public:
    ~IMessageHandler();

    virtual void HandleMsg(const char* a_msg) = 0;

protected:
    IMessageHandler();

};

} // experis

#endif