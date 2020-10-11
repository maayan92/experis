#include "mu_test.h"

#include "parser.hpp"
#include "configuration.hpp"
#include "agentsCreator.hpp"
#include "sensorAgentBucket.hpp"
#include "subscriptionHandler.hpp"
using namespace std;
using namespace smart_house;

BEGIN_TEST(test_agents_creator_controller)
    Subscriptions subs;
    SensorAgentBucket sensors;
    SubscriptionHandler subHandler(subs, sensors);

    Parser parser;
    Configuration config(parser);
    AgentsCreator agentsCreator(subHandler, config);

    ifstream configFile("configuration.txt");
    agentsCreator.CreateAgents(configFile);

END_TEST

BEGIN_SUITE(test_agents_creator)

END_SUITE