#ifndef AGENTS_CREATOR_HPP
#define AGENTS_CREATOR_HPP

#include <fstream>
#include "iSubscription.hpp"
#include "iConfiguration.hpp"
#include "sharedLibrarySo.hpp"
#include "shared_ptr.hpp"

namespace smart_house {

class AgentsCreator {
public:
    AgentsCreator(ISubscription& a_subscription, IConfiguration& a_configuration);

    void CreateAgents(std::ifstream& a_configFile, std::vector<std::pair<advcpp::shared_ptr<SharedLibrarySo>, advcpp::shared_ptr<IObserver> > >& a_agents);

private:
    ISubscription& m_subscription;
    IConfiguration& m_configuration;
};

} // smart_house

#endif