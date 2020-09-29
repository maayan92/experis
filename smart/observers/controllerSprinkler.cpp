#include "controllerSprinkler.hpp"
#include "controllersApi.hpp"
#include "sprinklerPayload.hpp"
using namespace std;

namespace smart_house {

ControllerSprinkler::ControllerSprinkler(ISubscription* a_subscription, vector<EventTypeLoc>& a_typeLoc)
: m_subscription(a_subscription)
, m_logFile("sprinkler_log.txt")
, m_typeLoc(a_typeLoc)
{
    for(size_t i = 0; i < a_typeLoc.size(); ++i) {
        m_subscription->Subscribe(a_typeLoc[i], this);
    }
}

ControllerSprinkler::~ControllerSprinkler()
{
    m_logFile.close();
}

void ControllerSprinkler::Notify(const Event& a_newEvent)
{
    SprinklerPayload* data = dynamic_cast<SprinklerPayload*>(a_newEvent.m_data);
    if(!data){
        return;
    }
    m_logFile << "event type: " << a_newEvent.m_typeAndLocation.m_type;
    m_logFile << "\troom: " << a_newEvent.m_typeAndLocation.m_location.m_room;
    m_logFile << "\tfloor: " << a_newEvent.m_typeAndLocation.m_location.m_floor;
    m_logFile << "\tevent time: " << a_newEvent.m_timestamp;

    m_logFile << "\ton: " << data->m_on;
    m_logFile << "\tiot: " << data->m_iot;

    m_logFile.flush();
}

extern "C"
IObserver* CreateObserver(ISubscription* a_subscription, vector<EventTypeLoc>& a_typeLoc)
{
    return new ControllerSprinkler(a_subscription, a_typeLoc);
}

} // smart_house