#include "security-4-g.hpp"
#include "badge-reader-4-g.hpp"
#include "agentsApi.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

Security4g::Security4g(ISubscription* a_subscription, Device& a_device)
: m_subscription(a_subscription)
, m_device(a_device)
, m_log(Singleton<FileLog>::Instance())
, m_logFile(a_device.m_log.c_str(), ios::app)
, m_data()
, m_sensor("127.0.0.1", 1234)
{
    m_subscription->Subscribe(m_device.m_typeLocation, this);
    m_subscription->SubscribeSensor(m_device.m_deviceId, this);

    parseConfig();
    m_sensor.ConnectToServer();
}

Security4g::~Security4g()
{
    m_logFile.close();
    m_subscription->UnSubscribe(m_device.m_typeLocation, this);
    m_subscription->UnSubscribeSensor(m_device.m_deviceId);
}

void Security4g::Notify(const Event& a_newEvent)
{
    shared_ptr<BadgeReader4gPayload> data(new BadgeReader4gPayload());
    shared_ptr<IPayload> dataBase(a_newEvent.m_data);
    dataBase.Swap<BadgeReader4gPayload>(data);

    time_t t;
    time(&t);
    struct tm* eventTime = localtime(&t);
    string msg;
    if(0 == data->m_token.compare(m_data.m_token)) {
        msg = "valid signature|";
    }
    else {
        msg = "not valid signature|";
    }

    msg += data->m_lockId;
    
    SensorInfo info(m_device.m_deviceId, msg.c_str(), eventTime);
    msg.clear();
    Protocol::Pack(msg, info);
    m_sensor.SendMessage(msg);
    
    stringstream logMsg;
    logMsg << a_newEvent;
    LOGINFO(m_log, m_logFile, logMsg.str());
}

void Security4g::CreateEvent(const SensorInfo& a_info, struct Event& a_event)
{
    a_event.m_typeAndLocation = EventTypeLoc(m_data.m_event, m_device.m_typeLocation.m_location);
    a_event.m_timestamp = a_info.m_time;

    shared_ptr<Security4gPayload> data(new Security4gPayload());

    size_t end = a_info.m_data.find("|");
    data->m_validBadge = (0 == string(a_info.m_data, 0, end).compare("valid signature")) ? true : false;
    data->m_lockId = string(a_info.m_data, end + 1);
    a_event.m_data = data;

    stringstream logMsg;
    logMsg << a_event;
    LOGINFO(m_log, m_logFile, logMsg.str());
}

// private functions:

string Security4g::getNextValue(const string& a_valName, size_t& a_end)
{
    size_t begin = m_device.m_config.find(a_valName, a_end);
    begin = m_device.m_config.find("\"", begin) + 1;
    a_end = m_device.m_config.find("\"", begin);

    return string(m_device.m_config, begin, a_end - begin);
}

void Security4g::parseConfig()
{
    size_t begin = 0;
    m_data.m_token = getNextValue("Token:", begin);
    m_data.m_event = getNextValue("Event:", begin);
}

//

extern "C"
IObserver* CreateObserver(ISubscription* a_subscription, Device& a_device)
{
    return new Security4g(a_subscription, a_device);
}

} // smart_house