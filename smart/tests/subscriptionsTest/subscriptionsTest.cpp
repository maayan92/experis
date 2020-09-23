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

template<size_t SIZE>
static bool equal(set<IObserver*>& a_observers, ControllerTest* a_controllers)
{
    for(size_t i = 0; i < SIZE; ++i) {
        set<IObserver*>::iterator itr = find(a_observers.begin(), a_observers.end(), &a_controllers[i]);
        if(itr == a_observers.end()) {
            return false;
        }
        a_observers.erase(itr);
    }

    return true;
}

// **** tests: **** //

BEGIN_TEST(test_subscribe_N_times_one_event_one_cntlr)
    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    
    ControllerTest controllers[1] = { ControllerTest(&sub, typeLoc) };
    sub.Subscribe(typeLoc[0], &controllers[0]);
    sub.Subscribe(typeLoc[0], &controllers[0]);
    sub.Subscribe(typeLoc[0], &controllers[0]);
    sub.Subscribe(typeLoc[0], &controllers[0]);
    sub.Subscribe(typeLoc[0], &controllers[0]);
    
    set<IObserver*> observers;
    subscriptions.Find(typeLoc[0], observers);
    ASSERT_EQUAL(1, observers.size());
    ASSERT_THAT(equal<1>(observers, controllers));
END_TEST

BEGIN_TEST(test_subscribe_two_events_one_observer)
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));

    EventTypeLoc typeLocNoise("NOISE_LEVEL", Location("1", "room_2_a"));

    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);
    ControllerTest controllers[1] = { ControllerTest(&sub, typeLoc) };
    ASSERT_EQUAL(1, subscriptions.Size());

    set<IObserver*> observers;
    subscriptions.Find(typeLoc[0], observers);
    ASSERT_EQUAL(1, observers.size());
    ASSERT_THAT(equal<1>(observers, controllers));

    observers.clear();
    subscriptions.Find(typeLocNoise, observers);
    ASSERT_EQUAL(0, observers.size());
END_TEST

BEGIN_TEST(test_subscribe_N_events_same_type_M_observer_with_all)
    vector<EventTypeLoc> typeLoc(1, EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));

    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);
    ControllerTest controllers[] = { ControllerTest(&sub, typeLoc) };

    vector<EventTypeLoc> typeLocAllFloors(1, EventTypeLoc("SMOKE_DETECTED", Location("All", "room_1_a")));
    ControllerTest controllersAllFloors[] = { ControllerTest(&sub, typeLocAllFloors) };
    
    vector<EventTypeLoc> typeLocAllRooms(1, EventTypeLoc("SMOKE_DETECTED", Location("1", "All")));
    ControllerTest controllersAllRooms[] = { ControllerTest(&sub, typeLocAllRooms) };
    ASSERT_EQUAL(3, subscriptions.Size());

    set<IObserver*> observers;
    SubscribersFinder(subscriptions).FindControllers(typeLoc[0], observers);
    ASSERT_EQUAL(3, observers.size());
    ASSERT_THAT(equal<1>(observers, controllers));
    ASSERT_THAT(equal<1>(observers, controllersAllFloors));
    ASSERT_THAT(equal<1>(observers, controllersAllRooms));
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
    ASSERT_THAT(equal<2>(observers, controllers));

    observers.clear();
    subscriptions.Find(typeLoc[1], observers);
    ASSERT_EQUAL(2, observers.size());
    ASSERT_THAT(equal<2>(observers, controllers));
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
    ASSERT_THAT(equal<1>(observers, controllers));
END_TEST

BEGIN_TEST(test_subscribe_size_N_events_two_observer)
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("ENTRANCE_REQUEST", Location("2", "room_1_a")));

    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);

    ControllerTest controllers[2] = { ControllerTest(&sub, typeLoc), ControllerTest(&sub, typeLoc) };

    ASSERT_EQUAL(4, subscriptions.Size());
END_TEST

BEGIN_SUITE(test_subscriptions)
    TEST(test_subscribe_N_times_one_event_one_cntlr)
    TEST(test_subscribe_two_events_one_observer)
    TEST(test_subscribe_N_events_same_type_M_observer_with_all)
    TEST(test_subscribe_N_events_two_observer)
    TEST(test_find_all_subscribers_one_event)

    TEST(test_subscribe_size_N_events_two_observer)
END_SUITE