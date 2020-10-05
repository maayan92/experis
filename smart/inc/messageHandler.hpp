#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

#include "iMessageHandler.hpp"
#include "sensorAgentBucket.hpp"
#include "iEventCreator.hpp"
#include "messageSeparator.hpp"

namespace smart_house {

class messageHandler : public experis::IMessageHandler {
public:
    messageHandler(SensorAgentBucket& a_sensorAgents, IEventCreator& a_creator);
    //~messageHandler() = default;

    virtual void HandleMsg(const char* a_msg);

private:
    SensorAgentBucket& m_sensorAgents;
    IEventCreator& m_creator;
    MessageSeparator m_msg;
};

} // smart_house

#endif