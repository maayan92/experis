#include "mu_test.h"
#include "testsFunctions.hpp"
#include <iostream>
#include <unistd.h>

#include "eventsExecutor.hpp"
#include "observersNotifierMT.hpp"
#include "subscriptionHandler.hpp"
#include "subscribersFinder.hpp"
#include "controllerTest.hpp"
#include "waitableQueue.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;
using namespace smart_house;

// **** tests: **** //

BEGIN_TEST(test_events_executor_one_event_N_observers_M_threads)
    Subscriptions subs;
    SensorAgentBucket sensors;
    SubscriptionHandler subHandler(subs, sensors);
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    
    vector<ControllerTest*> controllers;
    const size_t SIZE = 100;
    controllers.reserve(SIZE);
    for(size_t i = 0; i < SIZE; ++i) {
        controllers.push_back(new ControllerTest(&subHandler, typeLoc));
    }
    
    WaitableQueue<Event> events;
    events.Enque(CreateEvent(typeLoc[0]));

    ObserversNotifierMT notifier;
    SubscribersFinder finder(subs);
    EventsExecutor executor(events, notifier, finder);
    Thread<ShutDownTask> shutDown(shared_ptr<ShutDownTask>(new ShutDownTask(executor, 2)));

    executor.SendAllEvents();
    shutDown.Join();

    ASSERT_THAT(CheckResult<SIZE>(typeLoc[0], controllers));
END_TEST

BEGIN_TEST(test_events_executor_M_event_M_types_N_observers_K_threads)
    Subscriptions subs;
    SensorAgentBucket sensors;
    SubscriptionHandler subHandler(subs, sensors);
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("NOISE_DETECTED", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("A_DETECTED", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("B_DETECTED", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("C_DETECTED", Location("1", "room_1_a")));
    
    vector<ControllerTest*> controllers;
    const size_t SIZE = 100;
    controllers.reserve(SIZE);
    for(size_t i = 0; i < SIZE; ++i) {
        controllers.push_back(new ControllerTest(&subHandler, typeLoc));
    }
    
    WaitableQueue<Event> events;
    for(size_t i = 0; i < 5; ++i) {
        events.Enque(CreateEvent(typeLoc[i]));
    }
    
    ObserversNotifierMT notifier;
    SubscribersFinder finder(subs);
    EventsExecutor executor(events, notifier, finder);
    Thread<ShutDownTask> shutDown(shared_ptr<ShutDownTask>(new ShutDownTask(executor, 5)));

    executor.SendAllEvents();
    shutDown.Join();

    ASSERT_THAT(CheckResult<SIZE>(typeLoc[4], controllers));
END_TEST

BEGIN_TEST(test_events_executor_M_events_with_all_N_observers_K_threads)
    Subscriptions subs;
    SensorAgentBucket sensors;
    SubscriptionHandler subHandler(subs, sensors);
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("2", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("NOISE_DETECTED", Location("1", "room")));
    typeLoc.push_back(EventTypeLoc("A_DETECTED", Location("4", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("C_DETECTED", Location("All", "room_3_a")));
    
    vector<ControllerTest*> controllers;
    const size_t SIZE = 100;
    controllers.reserve(SIZE * 2);
    for(size_t i = 0; i < SIZE; ++i) {
        controllers.push_back(new ControllerTest(&subHandler, typeLoc));
    }
    
    typeLoc.push_back(EventTypeLoc("C_DETECTED", Location("3", "room_3_a")));
    for(size_t i = 0; i < SIZE; ++i) {
        controllers.push_back(new ControllerTest(&subHandler, typeLoc));
    }
    ASSERT_EQUAL(900, subs.Size());
    
    WaitableQueue<Event> events;
    for(size_t i = 0; i < 5; ++i) {
        events.Enque(CreateEvent(typeLoc[i]));
    }
    
    ObserversNotifierMT notifier;
    SubscribersFinder finder(subs);
    EventsExecutor executor(events, notifier, finder);
    Thread<ShutDownTask> shutDown(shared_ptr<ShutDownTask>(new ShutDownTask(executor, 5)));

    executor.SendAllEvents();
    shutDown.Join();

    ASSERT_THAT(CheckResult<SIZE * 2>(typeLoc[4], controllers));
END_TEST

BEGIN_TEST(test_events_executor_M_event_enque_thread_N_observers_K_threads)
    Subscriptions subs;
    SensorAgentBucket sensors;
    SubscriptionHandler subHandler(subs, sensors);
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("NOISE_DETECTED", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("A_DETECTED", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("B_DETECTED", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("C_DETECTED", Location("1", "room_1_a")));
    
    vector<ControllerTest*> controllers;
    const size_t SIZE = 100;
    controllers.reserve(SIZE);
    for(size_t i = 0; i < SIZE; ++i) {
        controllers.push_back(new ControllerTest(&subHandler, typeLoc));
    }
    ASSERT_EQUAL(500, subs.Size());

    WaitableQueue<Event> events;
    Thread<EventEnque> eventEnque(shared_ptr<EventEnque>(new EventEnque(events, typeLoc)));
    
    ObserversNotifierMT notifier;
    SubscribersFinder finder(subs);
    EventsExecutor executor(events, notifier, finder);
    Thread<ShutDownTask> shutDown(shared_ptr<ShutDownTask>(new ShutDownTask(executor, 5)));

    executor.SendAllEvents();
    eventEnque.Join();
    shutDown.Join();

    ASSERT_THAT(CheckResult<SIZE>(typeLoc[4], controllers));
END_TEST

BEGIN_SUITE(test_events_executor)
    TEST(test_events_executor_one_event_N_observers_M_threads)
    TEST(test_events_executor_M_event_M_types_N_observers_K_threads)
    TEST(test_events_executor_M_events_with_all_N_observers_K_threads)
    TEST(test_events_executor_M_event_enque_thread_N_observers_K_threads)
END_SUITE