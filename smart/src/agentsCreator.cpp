#include "agentsCreator.hpp"
#include "sharedLibrarySo.hpp"
using namespace std;

namespace smart_house {

AgentsCreator::AgentsCreator(ISubscription& a_subscription, IConfiguration& a_configuration)
: m_subscription(a_subscription)
, m_configuration(a_configuration)
{}

void AgentsCreator::CreateAgents(std::ifstream& a_configFile)
{
    m_configuration.ReadFile(a_configFile);

    vector<Device> devices;
    m_configuration.GetDevices(devices);

    typedef IObserver* (*ObserverFactory)(ISubscription*, Device&);
    string libFileName("./lib");
    for(size_t i = 0; i < devices.size(); ++i) {
        libFileName += devices[i].m_deviceId + ".so";
        SharedLibrarySo shared(libFileName.c_str());

        ObserverFactory factory = shared.SymbolAddr<ObserverFactory>("CreateObserver");

        IObserver* agent = factory(&m_subscription, devices[i]);
    }
}

} // smart_house