#include "mu_test.h"
#include "testsFunctions.hpp"
#include <iostream>
#include <unistd.h>

#include "eventsExecutor.hpp"
#include "observersNotifierMT.hpp"
#include "subscriptionHandler.hpp"
#include "controllerTest.hpp"
#include "waitableQueue.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;
using namespace smart_house;

struct ShutDownTask : public IRunnable {
    ShutDownTask(EventsExecutor& a_executor, size_t a_time)
    : m_executor(a_executor)
    , m_time(a_time)
    {}

    void operator()() {
        sleep(m_time);
        m_executor.ShutDown();
    }

private:
    EventsExecutor& m_executor;
    size_t m_time;
};

struct EventEnque : public IRunnable {
    EventEnque(WaitableQueue<Event>& a_events, vector<EventTypeLoc>& a_typeLoc)
    : m_events(a_events)
    , m_typeLoc(a_typeLoc)
    {}

    void operator()() {
        sleep(1);
        for(size_t i = 0; i < m_typeLoc.size(); ++i) {
            m_events.Enque(CreateEvent(m_typeLoc[i]));
        }
    }

private:
    WaitableQueue<Event>& m_events;
    vector<EventTypeLoc>& m_typeLoc;
};

// **** tests: **** //

BEGIN_TEST(test_events_executor_one_event_N_observers_M_threads)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
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
    EventsExecutor executor(events, &notifier);
    Thread<ShutDownTask> shutDown(shared_ptr<ShutDownTask>(new ShutDownTask(executor, 2)));

    executor.SendAllEvents(subs);
    shutDown.Join();

    ASSERT_THAT(CheckResult<SIZE>(typeLoc[0], controllers));
END_TEST

BEGIN_TEST(test_events_executor_M_event_M_types_N_observers_K_threads)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
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
    EventsExecutor executor(events, &notifier);
    Thread<ShutDownTask> shutDown(shared_ptr<ShutDownTask>(new ShutDownTask(executor, 5)));

    executor.SendAllEvents(subs);
    shutDown.Join();

    ASSERT_THAT(CheckResult<SIZE>(typeLoc[4], controllers));
END_TEST

BEGIN_TEST(test_events_executor_M_events_with_all_N_observers_K_threads)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
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
    EventsExecutor executor(events, &notifier);
    Thread<ShutDownTask> shutDown(shared_ptr<ShutDownTask>(new ShutDownTask(executor, 5)));
    executor.SendAllEvents(subs);
    shutDown.Join();

    ASSERT_THAT(CheckResult<SIZE * 2>(typeLoc[4], controllers));
END_TEST

BEGIN_TEST(test_events_executor_M_event_enque_thread_N_observers_K_threads)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
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
    EventsExecutor executor(events, &notifier);
    Thread<ShutDownTask> shutDown(shared_ptr<ShutDownTask>(new ShutDownTask(executor, 5)));

    executor.SendAllEvents(subs);
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