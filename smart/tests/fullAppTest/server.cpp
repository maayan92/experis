#include "parser.hpp"
#include "configuration.hpp"
#include "agentsCreator.hpp"
#include "sensorAgentBucket.hpp"
#include "subscriptionHandler.hpp"
#include "networkListener.hpp"
#include "eventCreatorMT.hpp"
#include "messageHandler.hpp"
#include "observersNotifierMT.hpp"
#include "subscribersFinder.hpp"
#include "eventsExecutor.hpp"

#include <iostream>
#include <sstream>      // std::stringstream

using namespace std;
using namespace advcpp;
using namespace experis;
using namespace smart_house;

struct RunEventsExecutor : IRunnable {

    RunEventsExecutor(WaitableQueue<Event>& a_events, Subscriptions& a_subs)
    : m_notifier()
    , m_finder(a_subs)
    , m_executor(a_events, m_notifier, m_finder)
    {}

    void operator()() {
        m_executor.SendAllEvents();
    }

    ObserversNotifierMT m_notifier;
    SubscribersFinder m_finder;
    EventsExecutor m_executor;
};

struct RunServer : IRunnable {

    RunServer(const string& a_ip, size_t a_port, WaitableQueue<Event>& a_events, SensorAgentBucket& a_sensors)
    : m_creator(a_events)
    , m_handler(a_sensors, m_creator)
    , m_server(a_ip, a_port, m_handler)
    {}

    void operator()() {
        m_server.ListenEvents();
    }

    EventCreatorMT m_creator;
    messageHandler m_handler;
    NetworkListener m_server;
};

int main(int argc, char* argv[]) {

    if(argc != 3) {
        cout << "please enter IP and PORT numbers when running the server! \n";
        return 0;
    }

    WaitableQueue<Event> events;

    Subscriptions subs;
    SensorAgentBucket sensors;
    SubscriptionHandler subHandler(subs, sensors);

    Parser parser;
    smart_house::Configuration config(parser);
    AgentsCreator agentsCreator(subHandler, config);

    ifstream configFile("configuration.txt");
    vector<pair<shared_ptr<SharedLibrarySo>, shared_ptr<IObserver> > > agents;
    
    stringstream strPort(argv[2]);
    size_t port;
    strPort >> port;

    try {
        ThreadPool runProgram(2);

        shared_ptr<RunEventsExecutor> executor(new RunEventsExecutor(events, subs));
        shared_ptr<RunServer> server(new RunServer(argv[1], port, events, sensors));
        agentsCreator.CreateAgents(configFile, agents);
        
        runProgram.Submit(executor);
        runProgram.Submit(server);

    } catch(exception& exc) {
        cout << exc.what() << '\n';
    }

    return 0;
}