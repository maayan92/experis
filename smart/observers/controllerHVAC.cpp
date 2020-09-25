#include "controllerHVAC.hpp"
#include "controllersApi.hpp"
#include "HvacPayload.hpp"
#include <typeinfo>

namespace smart_house {

const EventTypeLoc ControllerHVAC::testHVAC("TestHVAC", Location("1", "room_1_a"));

ControllerHVAC::ControllerHVAC(ISubscription* a_subscription)
: m_subscription(a_subscription)
, m_logFile("hvac_log")
{
    m_subscription->Subscribe(testHVAC, this);
}

void ControllerHVAC::Notify(const Event& a_newEvent)
{
    if(typeid(a_newEvent.m_data) != typeid(HvacPayload)) {
        return;
    }
    m_logFile << "event type: " << a_newEvent.m_typeAndLocation.m_type;
    m_logFile << "\tevent location: room:" << a_newEvent.m_typeAndLocation.m_location.m_room;
    m_logFile << " floor: " << a_newEvent.m_typeAndLocation.m_location.m_room;
    m_logFile << "\tevent time: " << a_newEvent.m_timestamp;
    HvacPayload* data = reinterpret_cast<HvacPayload*>(a_newEvent.m_data);

    m_logFile << "\tevent data: iot: " << data->m_iot;
    m_logFile << " tmp: " << data->m_tmp;
    m_logFile << " shut down: " << data->m_shutdown << '\n';
}

extern "C"
IObserver* CreateObserver(ISubscription* a_subscription)
{
    return new ControllerHVAC(a_subscription);
}

} // smart_house