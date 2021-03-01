#include "door-4-a.hpp"
#include "security-4-g.hpp"
#include "agentsApi.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

Door4a::Door4a(ISubscription* a_subscription, Device& a_device)
: m_subscription(a_subscription)
, m_device(a_device)
, m_log(Singleton<FileLog>::Instance())
, m_logFile(a_device.m_log.c_str(), ios::app)
, m_data()
{
    parseConfig();
    m_subscription->Subscribe(m_device.m_typeLocation, this);
    m_subscription->Subscribe(EventTypeLoc(m_data.m_event, Location(m_device.m_typeLocation.m_location.m_floor, m_data.m_from)), this);
}

Door4a::~Door4a()
{
    m_logFile.close();
    m_subscription->UnSubscribe(m_device.m_typeLocation, this);
}

void Door4a::Notify(const Event& a_newEvent)
{
    shared_ptr<Security4gPayload> data(new Security4gPayload());
    shared_ptr<IPayload> dataBase(a_newEvent.m_data);
    dataBase.Swap<Security4gPayload>(data);

    if(data->m_validBadge) {
        // ---- open door ---- //
    }
    
    stringstream msg;
    msg << a_newEvent;
    LOGINFO(m_log, m_logFile, msg.str());
    
    a_newEvent.m_data->Print(cout);
}

// private functions:

void Door4a::parseConfig()
{
    size_t begin = 0;
    m_data.m_token = getNextValue("Token:", begin);
    m_data.m_event = getNextValue("Event:", begin);
    m_data.m_from = getNextValue("From:", begin);
}

string Door4a::getNextValue(const string& a_valName, size_t& a_end)
{
    size_t begin = m_device.m_config.find(a_valName, a_end);
    begin = m_device.m_config.find('"', begin) + 1;
    a_end = m_device.m_config.find('"', begin);

    return string(m_device.m_config, begin, a_end - begin);
}

//

extern "C"
IObserver* CreateObserver(ISubscription* a_subscription, Device& a_device)
{
    return new Door4a(a_subscription, a_device);
}

} // smart_house