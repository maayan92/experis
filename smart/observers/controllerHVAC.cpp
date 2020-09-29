#include "controllerHVAC.hpp"
#include "controllersApi.hpp"
#include "HvacPayload.hpp"
using namespace std;

namespace smart_house {

ControllerHVAC::ControllerHVAC(ISubscription* a_subscription, vector<EventTypeLoc>& a_typeLoc)
: m_subscription(a_subscription)
, m_logFile("hvac_log.txt")
, m_typeLoc(a_typeLoc)
{
    for(size_t i = 0; i < a_typeLoc.size(); ++i) {
        m_subscription->Subscribe(a_typeLoc[i], this);
    }
}

ControllerHVAC::~ControllerHVAC()
{
    m_logFile.close();
}

void ControllerHVAC::Notify(const Event& a_newEvent)
{
    HvacPayload* data = dynamic_cast<HvacPayload*>(a_newEvent.m_data);
    if(!data){
        return;
    }
    m_logFile << "event type: " << a_newEvent.m_typeAndLocation.m_type;
    m_logFile << "\troom: " << a_newEvent.m_typeAndLocation.m_location.m_room;
    m_logFile << "\tfloor: " << a_newEvent.m_typeAndLocation.m_location.m_floor;
    m_logFile << "\tevent time: " << a_newEvent.m_timestamp;

    m_logFile << "\tiot: " << data->m_iot;
    m_logFile << "\ttmp: " << data->m_tmp;
    m_logFile << "\tshut down: " << data->m_shutdown << '\n';

    m_logFile.flush();
}

extern "C"
IObserver* CreateObserver(ISubscription* a_subscription, vector<EventTypeLoc>& a_typeLoc)
{
    return new ControllerHVAC(a_subscription, a_typeLoc);
}

} // smart_house