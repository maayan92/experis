#include "room-1-a-smoke.hpp"
#include "agentsApi.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

Room1aSmoke::Room1aSmoke(ISubscription* a_subscription, Device& a_device)
: m_subscription(a_subscription)
, m_device(a_device)
, m_log(Singleton<FileLog>::Instance())
, m_logFile(a_device.m_log.c_str(), ios::app)
{
    m_subscription->SubscribeSensor(m_device.m_deviceId, this);
}

Room1aSmoke::~Room1aSmoke()
{
    m_logFile.close();
    m_subscription->UnSubscribeSensor(m_device.m_deviceId);
}

void Room1aSmoke::CreateEvent(const SensorInfo& a_info, struct Event& a_event)
{
    shared_ptr<Room1aSmokePayload> data(new Room1aSmokePayload());
    data->m_hasSmokeInTheRoom = (0 == a_info.m_data.compare("on"));

    a_event.m_data = data;
    a_event.m_timestamp = a_info.m_time;
    a_event.m_typeAndLocation = EventTypeLoc("sprinx", m_device.m_typeLocation.m_location);
    stringstream msg;
    msg << a_event;
    LOGINFO(m_log, m_logFile, msg.str());
    
    cout << "\nsmoke detector:\n";
    a_event.m_data->Print(cout);
}

extern "C"
IObserver* CreateObserver(ISubscription* a_subscription, Device& a_device)
{
    return new Room1aSmoke(a_subscription, a_device);
}

} // smart_house