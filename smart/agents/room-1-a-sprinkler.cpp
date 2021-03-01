#include "room-1-a-sprinkler.hpp"
#include "room-1-a-smoke.hpp"
#include "agentsApi.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

Room1aSprinkler::Room1aSprinkler(ISubscription* a_subscription, Device& a_device)
: m_subscription(a_subscription)
, m_device(a_device)
, m_log(Singleton<FileLog>::Instance())
, m_logFile(a_device.m_log.c_str(), ios::app)
{
    m_subscription->Subscribe(m_device.m_typeLocation, this);
}

Room1aSprinkler::~Room1aSprinkler()
{
    m_logFile.close();
    m_subscription->UnSubscribe(m_device.m_typeLocation, this);
}

void Room1aSprinkler::Notify(const Event& a_newEvent)
{
    shared_ptr<Room1aSmokePayload> data(new Room1aSmokePayload());
    shared_ptr<IPayload> dataBase(a_newEvent.m_data);
    dataBase.Swap<Room1aSmokePayload>(data);

    if(data->m_hasSmokeInTheRoom) {
        data->m_activateSprinklers = true;
    }
    else {
        data->m_activateSprinklers = false;
    }
    
    stringstream msg;
    msg << a_newEvent;
    LOGINFO(m_log, m_logFile, msg.str());
    
    cout << "\nsprinkler:\n";
    a_newEvent.m_data->Print(cout);
}

extern "C"
IObserver* CreateObserver(ISubscription* a_subscription, Device& a_device)
{
    return new Room1aSprinkler(a_subscription, a_device);
}

} // smart_house