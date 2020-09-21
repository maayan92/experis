#include "mu_test.h"
#include "testsFunctions.hpp"
#include <iostream>

#include "observersNotifierMT.hpp"
#include "subscribersFinder.hpp"
#include "subscriptionHandler.hpp"
#include "controllerTest.hpp"
#include "payloadSmoke.hpp"
using namespace std;
using namespace smart_house;

static clock_t g_time;

BEGIN_TEST(test_notifier_one_thread_one_notify)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    ControllerTest controllers[] = { ControllerTest(&subHandler, typeLoc) };

    set<IObserver*> observers;
    SubscribersFinder(subs).FindControllers(typeLoc[0], observers);
    {
        ObserversNotifierMT(1).NotifyAll(CreateEvent(typeLoc[0]), observers);
    }

    ASSERT_THAT(CheckResult<1>(typeLoc[0], controllers));
END_TEST

BEGIN_TEST(test_notifier_one_thread_one_event_M_observers)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    ControllerTest controllers[] = { ControllerTest(&subHandler, typeLoc), ControllerTest(&subHandler, typeLoc)
                                    , ControllerTest(&subHandler, typeLoc), ControllerTest(&subHandler, typeLoc)
                                    , ControllerTest(&subHandler, typeLoc), ControllerTest(&subHandler, typeLoc)
                                    , ControllerTest(&subHandler, typeLoc), ControllerTest(&subHandler, typeLoc) };

    set<IObserver*> observers;
    SubscribersFinder(subs).FindControllers(typeLoc[0], observers);
    {
        ObserversNotifierMT(1).NotifyAll(CreateEvent(typeLoc[0]), observers);
    }

    ASSERT_THAT(CheckResult<8>(typeLoc[0], controllers));
END_TEST

BEGIN_TEST(test_notifier_N_thread_one_event_M_observers)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    ControllerTest controllers[] = { ControllerTest(&subHandler, typeLoc), ControllerTest(&subHandler, typeLoc)
                                    , ControllerTest(&subHandler, typeLoc), ControllerTest(&subHandler, typeLoc)
                                    , ControllerTest(&subHandler, typeLoc), ControllerTest(&subHandler, typeLoc)
                                    , ControllerTest(&subHandler, typeLoc), ControllerTest(&subHandler, typeLoc) };

    set<IObserver*> observers;
    SubscribersFinder(subs).FindControllers(typeLoc[0], observers);
    {
        ObserversNotifierMT(5).NotifyAll(CreateEvent(typeLoc[0]), observers);
    }

    ASSERT_THAT(CheckResult<8>(typeLoc[0], controllers));
END_TEST

BEGIN_TEST(test_notifier_one_thread_one_event_M_observers_test_time)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    
    size_t SIZE = 1000000;
    vector<ControllerTest*> controllers;
    controllers.reserve(SIZE);
    for(size_t i = 0; i < SIZE; ++i) {
        controllers.push_back(new ControllerTest(&subHandler, typeLoc));
    }

    set<IObserver*> observers;
    SubscribersFinder(subs).FindControllers(typeLoc[0], observers);
    ASSERT_EQUAL(SIZE, observers.size());
    
    clock_t begin, end;
    begin = clock();
    {
        ObserversNotifierMT(1).NotifyAll(CreateEvent(typeLoc[0]), observers);
    }
    end = clock();
    g_time = end - begin;
END_TEST

BEGIN_TEST(test_notifier_N_thread_one_event_M_observers_test_time)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    
    size_t SIZE = 1000000;
    vector<ControllerTest*> controllers;
    controllers.reserve(SIZE);
    for(size_t i = 0; i < SIZE; ++i) {
        controllers.push_back(new ControllerTest(&subHandler, typeLoc));
    }

    set<IObserver*> observers;
    SubscribersFinder(subs).FindControllers(typeLoc[0], observers);
    ASSERT_EQUAL(SIZE, observers.size());

    clock_t begin, end;
    begin = clock();
    {
        ObserversNotifierMT(8).NotifyAll(CreateEvent(typeLoc[0]), observers);
    }
    end = clock();
    clock_t runTime = end - begin;
    //cout << "now " <<  runTime << '\n';
    //cout << "before" << g_time << '\n';
    
    ASSERT_THAT(runTime < g_time);
END_TEST

BEGIN_SUITE(test_notifier_with_thread_pool)
    TEST(test_notifier_one_thread_one_notify)

    TEST(test_notifier_one_thread_one_event_M_observers)
    TEST(test_notifier_N_thread_one_event_M_observers)

    //TEST(test_notifier_one_thread_one_event_M_observers_test_time)
    //TEST(test_notifier_N_thread_one_event_M_observers_test_time)
END_SUITE