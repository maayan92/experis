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

static void Delete(ControllerTest* a_ctrl)
{
    delete a_ctrl;
}

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

BEGIN_TEST(test_notifier_K_thread_N_event_M_observers)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    vector<EventTypeLoc> typeLoc;
    
    const size_t SIZE = 8;
    vector<ControllerTest*> controllers;
    controllers.reserve(SIZE * 3);

    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    for(size_t i = 0; i < SIZE; ++i) {
        controllers.push_back(new ControllerTest(&subHandler, typeLoc));
    }

    typeLoc.push_back(EventTypeLoc("NOISE_LEVEL", Location("1", "room_1_a")));
    for(size_t i = 0; i < SIZE; ++i) {
        controllers.push_back(new ControllerTest(&subHandler, typeLoc));
    }
    
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("2", "room_1_a")));
    for(size_t i = 0; i < SIZE; ++i) {
        controllers.push_back(new ControllerTest(&subHandler, typeLoc));
    }
    
    typeLoc.push_back(EventTypeLoc("All", Location("1", "room_1_a")));

    set<IObserver*> observers;
    SubscribersFinder finder(subs);
    ObserversNotifierMT notifier(5);
    for(size_t i = 4; i > 0; --i) {
        observers.clear();
        finder.FindControllers(typeLoc[i - 1], observers);
        ASSERT_EQUAL(24 - ((i - 1) * 8), observers.size());
        {
            notifier.NotifyAll(CreateEvent(typeLoc[i - 1]), observers);
        }
    }

    ASSERT_THAT(CheckResult<SIZE>(typeLoc[0], controllers));

    vector<ControllerTest*>::iterator itr = controllers.begin();
    ASSERT_THAT(CheckResult<SIZE>(typeLoc[0], vector<ControllerTest*>(itr + SIZE, itr + (SIZE * 2))));
    ASSERT_THAT(CheckResult<SIZE>(typeLoc[0], vector<ControllerTest*>(itr + (SIZE * 2), controllers.end())));

    for_each(controllers.begin(), controllers.end(), Delete);
END_TEST

BEGIN_TEST(test_notifier_N_thread_M_event_lots_of_observers)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    
    const size_t SIZE = 1000;
    vector<ControllerTest*> controllers;
    controllers.reserve(SIZE * 2);

    for(size_t i = 0; i < SIZE; ++i) {
        controllers.push_back(new ControllerTest(&subHandler, typeLoc));
    }
    
    typeLoc.push_back(EventTypeLoc("All", Location("1", "room_1_a")));
    for(size_t i = 0; i < SIZE; ++i) {
        controllers.push_back(new ControllerTest(&subHandler, typeLoc));
    }

    typeLoc.push_back(EventTypeLoc("ENTRANCE_REQUEST", Location("1", "room_1_a")));

    set<IObserver*> observers;
    SubscribersFinder finder(subs);
    ObserversNotifierMT notifier;
    for(size_t i = 3; i > 0; --i) {
        observers.clear();
        finder.FindControllers(typeLoc[i - 1], observers);
        {
            notifier.NotifyAll(CreateEvent(typeLoc[i - 1]), observers);
        }
    }
    
    ASSERT_THAT(CheckResult<SIZE>(typeLoc[0], controllers));
    ASSERT_THAT(CheckResult<SIZE>(typeLoc[0], vector<ControllerTest*>(controllers.begin() + SIZE, controllers.end())));

    for_each(controllers.begin(), controllers.end(), Delete);
END_TEST

BEGIN_SUITE(test_notifier_with_thread_pool)
    TEST(test_notifier_one_thread_one_notify)

    TEST(test_notifier_one_thread_one_event_M_observers)
    TEST(test_notifier_N_thread_one_event_M_observers)

    TEST(test_notifier_K_thread_N_event_M_observers)
    TEST(test_notifier_N_thread_M_event_lots_of_observers)
END_SUITE