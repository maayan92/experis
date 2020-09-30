#include "mu_test.h"
#include "testsFunctions.hpp"
#include <iostream>
#include <fstream>
#include <vector>

#include "sharedLibrarySo.hpp"
#include "subscriptionHandler.hpp"
#include "subscriptions.hpp"
#include "HvacPayload.hpp"
#include "sprinklerPayload.hpp"
#include "eventsExecutor.hpp"
#include "subscribersFinder.hpp"
#include "observersNotifierMT.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;
using namespace smart_house;

static string GetValue(string& a_buffer, size_t& a_position)
{
    size_t pos = a_buffer.find(":", a_position + 1) + 2;
    size_t posLast = a_buffer.find("\t", pos);
    a_position = posLast;
    string result = a_buffer.substr(pos, posLast - pos);

    return result;
}

static bool CheckPayloadHvac(shared_ptr<HvacPayload>& a_data, string& a_buffer, size_t& a_position)
{
    if(GetValue(a_buffer, a_position) != a_data->m_iot) {
        return false;
    }
    if(GetValue(a_buffer, a_position) != a_data->m_tmp) {
        return false;
    }
    if(GetValue(a_buffer, a_position) != a_data->m_shutdown) {
        return false;
    }
    return true;
}

static bool CheckPayloadSprinkler(shared_ptr<SprinklerPayload>& a_data, string& a_buffer, size_t& a_position)
{
    if(GetValue(a_buffer, a_position) != a_data->m_on) {
        return false;
    }
    if(GetValue(a_buffer, a_position) != a_data->m_iot) {
        return false;
    }
    return true;
}

static bool CheckNotifyResultHvac(ifstream& a_logFile, const Event& a_event, size_t a_numOfEvents)
{
    string buffer;
    size_t pos = 0;

    while(a_numOfEvents > 0 && getline(a_logFile, buffer)) {
        if(GetValue(buffer, pos) != a_event.m_typeAndLocation.m_type) {
            return false;
        }
        if(GetValue(buffer, pos) != a_event.m_typeAndLocation.m_location.m_room) {
            return false;
        }
        if(GetValue(buffer, pos) != a_event.m_typeAndLocation.m_location.m_floor) {
            return false;
        }
        GetValue(buffer, pos);
        
        shared_ptr<HvacPayload> data;
        shared_ptr<IPayload> dataCopy(a_event.m_data);
        dataCopy.Swap<HvacPayload>(data);

        if(data) {
            CheckPayloadHvac(data, buffer, pos);
        }
        else {
            shared_ptr<SprinklerPayload> data;
            dataCopy = a_event.m_data;
            dataCopy.Swap<SprinklerPayload>(data);
            if(data) {
                CheckPayloadSprinkler(data, buffer, pos);
            }
        }
        
        --a_numOfEvents;
    }
    return (a_numOfEvents ==0) ? true : false;
}

struct EnqueByEvents : public experis::IRunnable {
    EnqueByEvents(WaitableQueue<Event>& a_eventsQueue, vector<Event>& a_events)
    : m_eventsQueue(a_eventsQueue)
    , m_events(a_events)
    {}

    virtual void operator()() {
        usleep(10000);
        for(size_t i = 0; i < m_events.size(); ++i) {
            m_eventsQueue.Enque(m_events[i]);
        }
    }

private:
    advcpp::WaitableQueue<smart_house::Event>& m_eventsQueue;
    vector<Event>& m_events;
};

struct TestExecutor : public EventsExecutor {
    TestExecutor(WaitableQueue<Event>& a_eventQueue, IObserversNotifier& a_notifier, ISubscribersFinder& a_finder)
    : EventsExecutor(a_eventQueue, a_notifier, a_finder)
    {}

    void SendEvents(size_t a_numOfEvents)
    {
        EventsExecutor::SendEvents(a_numOfEvents);
    }

    void SendUntil(Event const& a_event) 
    {
        EventsExecutor::SendEventsUntil(a_event);
    }

};

// **** tests: **** //

BEGIN_TEST(test_shared_library_so_one_event_one_observer)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    SharedLibrarySo observers("./controllerSO/libControllerHVAC.so");

    typedef IObserver* (*ObserverFactory)(ISubscription*, vector<EventTypeLoc>&);
    ObserverFactory factory = observers.SymbolAddr<ObserverFactory>("CreateObserver");

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("TestHVAC", Location("1", "room_1_a")));
    IObserver* o = factory(&subHandler, typeLoc);

    time_t t;
    time(&t);
    shared_ptr<HvacPayload> data(new HvacPayload("10.10.1.64", "77", "Fire_Detected|ROOM_EMPTY"));

    Event event = { localtime(&t), data, typeLoc[0] };
    o->Notify(event);

    ifstream logFile("hvac_log.txt");

    ASSERT_THAT(CheckNotifyResultHvac(logFile, event, 1));
END_TEST

BEGIN_TEST(test_shared_library_so_one_observer_all_floor_event)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    SharedLibrarySo observers("./controllerSO/libControllerHVAC.so");

    typedef IObserver* (*ObserverFactory)(ISubscription*, vector<EventTypeLoc>&);
    ObserverFactory factory = observers.SymbolAddr<ObserverFactory>("CreateObserver");

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("All", Location("1", "room_1_a")));
    IObserver* o = factory(&subHandler, typeLoc);

    time_t t;
    time(&t);
    shared_ptr<HvacPayload> data(new HvacPayload("10.10.1.64", "77", "Fire_Detected|ROOM_EMPTY"));

    Event event = { localtime(&t), data, EventTypeLoc("TestHVAC", Location("1", "room_1_a")) };
    o->Notify(event);

    ifstream logFile("hvac_log.txt");

    ASSERT_THAT(CheckNotifyResultHvac(logFile, event, 1));
END_TEST

BEGIN_TEST(test_shared_library_so_multi_events_one_observer)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    SharedLibrarySo observers("./controllerSO/libControllerHVAC.so");

    typedef IObserver* (*ObserverFactory)(ISubscription*, vector<EventTypeLoc>&);
    ObserverFactory factory = observers.SymbolAddr<ObserverFactory>("CreateObserver");

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("All", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("TestHVAC", Location("2", "room_1_b")));
    typeLoc.push_back(EventTypeLoc("HVAC", Location("3", "All")));
    IObserver* o = factory(&subHandler, typeLoc);

    time_t t;
    time(&t);
    shared_ptr<HvacPayload> data(new HvacPayload("10.10.1.64", "77", "Fire_Detected|ROOM_EMPTY"));

    Event event = { localtime(&t), data, EventTypeLoc("TestHVAC", Location("2", "room_1_a")) };
    Event event2 = { localtime(&t), data, EventTypeLoc("HVAC", Location("1", "room_1_a")) };
    o->Notify(event);
    o->Notify(event2);

    ifstream logFile("hvac_log.txt");

    ASSERT_THAT(CheckNotifyResultHvac(logFile, event, 1));
    ASSERT_THAT(CheckNotifyResultHvac(logFile, event2, 1));
END_TEST

BEGIN_TEST(test_shared_library_so_multi_events_two_same_observers_multi_thread)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    SharedLibrarySo observers("./controllerSO/libControllerHVAC.so");

    typedef IObserver* (*ObserverFactory)(ISubscription*, vector<EventTypeLoc>&);
    ObserverFactory factory = observers.SymbolAddr<ObserverFactory>("CreateObserver");

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("All", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("TestHVAC", Location("2", "room_1_b")));
    typeLoc.push_back(EventTypeLoc("HVAC", Location("3", "All")));
    IObserver* o1 = factory(&subHandler, typeLoc);
    IObserver* o2 = factory(&subHandler, typeLoc);

    ASSERT_NOT_EQUAL(o1, o2);

    typeLoc.push_back(EventTypeLoc("TestFire", Location("2", "room_1_b")));
    typeLoc.push_back(EventTypeLoc("Fire", Location("3", "All")));

    vector<Event> allEvents;
    time_t t;
    time(&t);
    shared_ptr<HvacPayload> data(new HvacPayload("10.10.1.64", "77", "Fire_Detected|ROOM_EMPTY"));

    Event e = { localtime(&t), data, typeLoc[1] };
    allEvents.push_back(e);
    Event e2 = { localtime(&t), data, typeLoc[2] };
    allEvents.push_back(e2);
    Event e3 = { localtime(&t), data, EventTypeLoc("test", Location("1", "room_1_a")) };
    allEvents.push_back(e3);
    Event e4 = { localtime(&t), data, typeLoc[4] };
    allEvents.push_back(e4);

    WaitableQueue<Event> eventsQueue;
    Thread<EnqueByEvents> eventEnquer(shared_ptr<EnqueByEvents>(new EnqueByEvents(eventsQueue, allEvents)));
    
    ObserversNotifierMT notifier;
    SubscribersFinder finder(subs);
    TestExecutor executor(eventsQueue, notifier, finder); 

    executor.SendEvents(allEvents.size());
    eventEnquer.Join();

    ifstream logFile("hvac_log.txt");
    for(size_t i = 0; i < allEvents.size() - 1; ++i) {
        ASSERT_THAT(CheckNotifyResultHvac(logFile, allEvents[i], 1));
    }

    ASSERT_THAT(!CheckNotifyResultHvac(logFile, allEvents[4], 1));
END_TEST

BEGIN_TEST(test_shared_library_so_multi_events_two_different_observers_multi_thread)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    SharedLibrarySo observersHvac("./controllerSO/libControllerHVAC.so");
    SharedLibrarySo observersSprinkler("./controllerSO/libControllerSprinkler.so");

    typedef IObserver* (*ObserverFactory)(ISubscription*, vector<EventTypeLoc>&);
    ObserverFactory factoryHvac = observersHvac.SymbolAddr<ObserverFactory>("CreateObserver");
    ObserverFactory factorySprinkler = observersSprinkler.SymbolAddr<ObserverFactory>("CreateObserver");

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("All", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("TestHVAC", Location("2", "room_1_b")));
    typeLoc.push_back(EventTypeLoc("HVAC", Location("3", "All")));
    IObserver* hvac = factoryHvac(&subHandler, typeLoc);

    typeLoc.pop_back();
    typeLoc.pop_back();

    typeLoc.push_back(EventTypeLoc("TestSprinkler", Location("2", "room_1_b")));
    typeLoc.push_back(EventTypeLoc("TestFire", Location("3", "All")));
    IObserver* sprinkler = factorySprinkler(&subHandler, typeLoc);

    ASSERT_NOT_EQUAL(hvac, sprinkler);

    vector<Event> allEvents;
    time_t t;
    time(&t);
    shared_ptr<HvacPayload> dataHavc(new HvacPayload("10.10.1.64", "77", "Fire_Detected|ROOM_EMPTY"));
    shared_ptr<SprinklerPayload> dataSprinkler(new SprinklerPayload("Fire_Detected|ROOM_EMPTY", "10.10.1.64"));

    Event e = { localtime(&t), dataHavc, EventTypeLoc("TestHVAC", Location("2", "room_1_b")) };
    allEvents.push_back(e);
    Event e2 = { localtime(&t), dataSprinkler, EventTypeLoc("TestSprinkler", Location("2", "room_1_b")) };
    allEvents.push_back(e2);
    Event e3 = { localtime(&t), dataHavc, EventTypeLoc("HVAC", Location("3", "All")) };
    allEvents.push_back(e3);
    Event e4 = { localtime(&t), dataSprinkler, EventTypeLoc("TestFire", Location("3", "All")) };
    allEvents.push_back(e4);
    Event end = { localtime(&t), dataSprinkler, EventTypeLoc("end", Location("3", "All")) };
    allEvents.push_back(end);
    Event e6 = { localtime(&t), dataSprinkler, EventTypeLoc("All", Location("1", "room_1_a")) };
    allEvents.push_back(e6);

    WaitableQueue<Event> eventsQueue;
    Thread<EnqueByEvents> eventEnque(shared_ptr<EnqueByEvents>(new EnqueByEvents(eventsQueue, allEvents)));
    
    ObserversNotifierMT notifier;
    SubscribersFinder finder(subs);
    TestExecutor executor(eventsQueue, notifier, finder);

    executor.SendUntil(end);
    eventEnque.Join();

    ifstream logFileHvac("hvac_log.txt");
    ifstream logFileSprinkler("sprinkler_log.txt");
    for(size_t i = 0; i < allEvents.size() - 2; i += 2) {
        ASSERT_THAT(CheckNotifyResultHvac(logFileHvac, allEvents[i], 1));
        ASSERT_THAT(CheckNotifyResultHvac(logFileSprinkler, allEvents[i + 1], 1));
    }
    ASSERT_THAT(!CheckNotifyResultHvac(logFileSprinkler, allEvents[5], 1));

    logFileHvac.close();
    logFileSprinkler.close();
END_TEST

BEGIN_SUITE(test_shared_library)
    TEST(test_shared_library_so_one_event_one_observer)
    TEST(test_shared_library_so_one_observer_all_floor_event)
    TEST(test_shared_library_so_multi_events_one_observer)
    TEST(test_shared_library_so_multi_events_two_same_observers_multi_thread)
    TEST(test_shared_library_so_multi_events_two_different_observers_multi_thread)
END_SUITE
