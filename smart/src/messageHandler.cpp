#include "messageHandler.hpp"
#include "protocol.hpp"
#include "event.hpp"
using namespace std;

namespace smart_house {

messageHandler::messageHandler(SensorAgentBucket& a_sensorAgents, IEventCreator& a_creator)
: m_sensorAgents(a_sensorAgents)
, m_creator(a_creator)
, m_msg()
{}

void messageHandler::HandleMsg(const char* a_msg)
{
    m_msg.AddToMsg(a_msg);

    while(m_msg.IsThereCompleteData()) {
        string data;
        m_msg.GetData(data);

        SensorInfo info;
        Protocol::UnPack(data, info);

        IObserver* sensor = 0;
        m_sensorAgents.FindSensor(info.m_deviceId, sensor);
        
        if(sensor) {
            m_creator.CreateEvent(info, sensor);
        }
    }
}

} // smart_house