#include "agentsCreator.hpp"
using namespace std;
using namespace advcpp;

namespace smart_house {

AgentsCreator::AgentsCreator(ISubscription& a_subscription, IConfiguration& a_configuration)
: m_subscription(a_subscription)
, m_configuration(a_configuration)
{}

void AgentsCreator::CreateAgents(ifstream& a_configFile, vector<pair<shared_ptr<SharedLibrarySo>, shared_ptr<IObserver> > >& a_agents)
{
    m_configuration.ReadFile(a_configFile);

    vector<Device> devices;
    m_configuration.GetDevices(devices);
    a_agents.reserve(a_agents.size() + devices.size());

    typedef IObserver* (*ObserverFactory)(ISubscription*, Device&);
    
    for(size_t i = 0; i < devices.size(); ++i) {
        string libFileName("./lib");
        libFileName += devices[i].m_deviceId + ".so";
        shared_ptr<SharedLibrarySo> shared(new SharedLibrarySo(libFileName.c_str()));

        ObserverFactory factory = shared->SymbolAddr<ObserverFactory>("CreateObserver");

        shared_ptr<IObserver> agent(factory(&m_subscription, devices[i]));
        a_agents.push_back(make_pair(shared, agent));
    }
}

} // smart_house