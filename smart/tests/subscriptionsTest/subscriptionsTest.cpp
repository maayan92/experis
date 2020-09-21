#include "mu_test.h"
#include <iostream>
#include <algorithm>

#include "subscriptionHandler.hpp"
#include "subscribersFinder.hpp"
#include "controllerTest.hpp"
#include "payloadSmoke.hpp"
#include "event.hpp"
using namespace std;
using namespace smart_house;

static bool equal(set<IObserver*>& a_observers, ControllerTest* a_controllers)
{
    for(size_t i = 0; i < a_observers.size(); ++i) {
        set<IObserver*>::iterator itr = find(a_observers.begin(), a_observers.end(), &a_controllers[i]);
        if(itr == a_observers.end()) {
            return false;
        }
    }

    return true;
}

// **** tests: **** //

BEGIN_TEST(test_subscribe_one_event_N_times)
    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    
    ControllerTest controllers[1] = { ControllerTest(&sub, typeLoc) };
    subscriptions.Upsert(typeLoc[0], &controllers[0]);
    subscriptions.Upsert(typeLoc[0], &controllers[0]);
    subscriptions.Upsert(typeLoc[0], &controllers[0]);
    subscriptions.Upsert(typeLoc[0], &controllers[0]);
    
    set<IObserver*> observers;
    subscriptions.Find(typeLoc[0], observers);
    ASSERT_EQUAL(1, observers.size());
    ASSERT_THAT(equal(observers, controllers));
END_TEST

BEGIN_TEST(test_subscribe_two_events_one_observer)
    time_t currentTime;
    time(&currentTime);

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));

    EventTypeLoc typeLocNoise("NOISE_LEVEL", Location("1", "room_2_a"));

    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);
    ControllerTest controllers[1] = { ControllerTest(&sub, typeLoc) };

    set<IObserver*> observers;
    subscriptions.Find(typeLoc[0], observers);
    ASSERT_EQUAL(1, observers.size());
    ASSERT_THAT(equal(observers, controllers));

    observers.clear();
    try {
        subscriptions.Find(typeLocNoise, observers);
    } catch(const exception& exc) {
        ASSERT_EQUAL(0, observers.size());
    }
END_TEST

BEGIN_TEST(test_subscribe_N_events_two_observer)
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("ENTRANCE_REQUEST", Location("2", "room_1_a")));

    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);

    ControllerTest controllers[2] = { ControllerTest(&sub, typeLoc), ControllerTest(&sub, typeLoc) };

    set<IObserver*> observers;
    subscriptions.Find(typeLoc[0], observers);
    ASSERT_EQUAL(2, observers.size());
    ASSERT_THAT(equal(observers, controllers));

    observers.clear();
    subscriptions.Find(typeLoc[1], observers);
    ASSERT_EQUAL(2, observers.size());
    ASSERT_THAT(equal(observers, controllers));
END_TEST

BEGIN_TEST(test_find_all_subscribers_one_event)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    vector<EventTypeLoc> typeLocSmoke;
    typeLocSmoke.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    ControllerTest controllers[] = { ControllerTest(&subHandler, typeLocSmoke)};

    set<IObserver*> observers;
    SubscribersFinder finder(subs);
    finder.FindControllers(typeLocSmoke[0], observers);

    ASSERT_EQUAL(1, observers.size());
    ASSERT_THAT(equal(observers, controllers));
END_TEST

BEGIN_SUITE(test_subscriptions)
    TEST(test_subscribe_one_event_N_times)
    TEST(test_subscribe_two_events_one_observer)
    TEST(test_subscribe_N_events_two_observer)

    TEST(test_find_all_subscribers_one_event)
END_SUITE