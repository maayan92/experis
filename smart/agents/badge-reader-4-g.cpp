#include "badge-reader-4-g.hpp"
#include "agentsApi.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

// static functions:

static string getNext(const string& a_data, size_t& a_start)
{
    size_t start = a_start;
    size_t end = a_data.find("|", start);
    a_start = end + 1;

    return string(a_data, start, end - start);
}

// member functions:

BadgeReader4g::BadgeReader4g(ISubscription* a_subscription, Device& a_device)
: m_subscription(a_subscription)
, m_device(a_device)
, m_log(Singleton<FileLog>::Instance())
, m_logFile(a_device.m_log.c_str(), ios::app)
{
    m_subscription->SubscribeSensor(m_device.m_deviceId, this);
}

BadgeReader4g::~BadgeReader4g()
{
    m_logFile.close();
    m_subscription->UnSubscribeSensor(m_device.m_deviceId);
}

void BadgeReader4g::CreateEvent(const SensorInfo& a_info, struct Event& a_event)
{
    a_event.m_typeAndLocation = m_device.m_typeLocation;
    a_event.m_timestamp = a_info.m_time;

    shared_ptr<BadgeReader4gPayload> data(new BadgeReader4gPayload());

    size_t start = 0;
    data->m_employeeId = getNext(a_info.m_data, start);
    data->m_lockId = getNext(a_info.m_data, start);
    data->m_token = string(a_info.m_data, start);

    a_event.m_data = data;
    data->Print(cout);

    stringstream msg;
    msg << a_event;
    LOGINFO(m_log, m_logFile, msg.str());
}

extern "C"
IObserver* CreateObserver(ISubscription* a_subscription, Device& a_device)
{
    return new BadgeReader4g(a_subscription, a_device);
}

} // smart_house