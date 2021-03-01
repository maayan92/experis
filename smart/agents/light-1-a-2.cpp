#include "light-1-a-2.hpp"
#include "agentsApi.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

Light1a2::Light1a2(ISubscription* a_subscription, Device& a_device)
: m_subscription(a_subscription)
, m_device(a_device)
, m_log(Singleton<FileLog>::Instance())
, m_logFile(a_device.m_log.c_str(), ios::app)
, m_data()
{
    parseConfig();
    m_subscription->Subscribe(m_device.m_typeLocation, this);
    m_subscription->SubscribeSensor(m_device.m_deviceId, this);
}

Light1a2::~Light1a2()
{
    m_logFile.close();
    m_subscription->UnSubscribe(m_device.m_typeLocation, this);
    m_subscription->UnSubscribeSensor(m_device.m_deviceId);
}

void Light1a2::Notify(const Event& a_newEvent)
{
    stringstream msg;
    msg << a_newEvent;
    LOGINFO(m_log, m_logFile, msg.str());
    
    a_newEvent.m_data->Print(cout);
}

void Light1a2::CreateEvent(const SensorInfo& a_info, struct Event& a_event)
{
    a_event.m_typeAndLocation = m_device.m_typeLocation;
    a_event.m_timestamp = a_info.m_time;

    shared_ptr<Light1a2Payload> data(new Light1a2Payload());
    data->m_lightOn = (0 == a_info.m_data.compare("on"));
    a_event.m_data = data;

    stringstream msg;
    msg << a_event;
    LOGINFO(m_log, m_logFile, msg.str());
}

extern "C"
IObserver* CreateObserver(ISubscription* a_subscription, Device& a_device)
{
    return new Light1a2(a_subscription, a_device);
}

// private functions:

void Light1a2::parseConfig()
{
    size_t start = 0;
    m_data.m_iot = getNextValue("iot:", start);
    m_data.m_sat = getNextValue("sat:", start);
    m_data.m_bright = getNextValue("bright:", start);
    m_data.m_hue = getNextValue("hue:", start);
}

string Light1a2::getNextValue(const string& a_valName, size_t& a_begin)
{
    a_begin = m_device.m_config.find(a_valName, a_begin) + 1;
    size_t end = m_device.m_config.find(",", a_begin);

    return string(m_device.m_config, a_begin, end - a_begin);
}

} // smart_house