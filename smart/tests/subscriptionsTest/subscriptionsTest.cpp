#include "subscriptionHandler.hpp"
#include "controllerTest.hpp"
#include "payloadSmoke.hpp"
#include "event.hpp"
#include "mu_test.h"
#include <iostream>
using namespace std;
using namespace smart_house;

template<size_t SIZE>
static bool FindAndCheck(Subscriptions& a_subscriptions, EventTypeLoc& a_typeLoc, ControllerTest* a_controllers)
{
    set<IObserver*> ob;
    try {
        a_subscriptions.Find(a_typeLoc, ob);
    } catch(const exception& exc) {
        return (0 == SIZE);
    }

    if(SIZE != ob.size()) {
        return false;
    }

    time_t t;
    time(&t);
    PayloadSmoke ps;
    Event event = {localtime(&t), &ps, a_typeLoc};

    bool result = true;
    size_t i = 0;
    for(set<IObserver*>::iterator itr = ob.begin(); itr != ob.end(); ++itr) {
        (*itr)->Notify(event);
        result &= (a_typeLoc == a_controllers[i++].GetEventTypeLocation());
    }
    return result;
}

// **** tests: **** //

BEGIN_TEST(test_subscribe_one_event)
    time_t currentTime;
    time(&currentTime);

    EventTypeLoc typeLoc("SMOKE_DETECTED", Location("1", "room_1_a"));

    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);
    ControllerTest controllers[1] = { ControllerTest(&sub) };
    subscriptions.Upsert(typeLoc, &controllers[0]);

    ASSERT_THAT(FindAndCheck<1>(subscriptions, typeLoc, controllers));
END_TEST

BEGIN_TEST(test_subscribe_two_events_one_observer)
    time_t currentTime;
    time(&currentTime);

    EventTypeLoc typeLocSmoke("SMOKE_DETECTED", Location("1", "room_1_a"));
    EventTypeLoc typeLocNoise("NOISE_LEVEL", Location("1", "room_2_a"));

    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);
    ControllerTest controllers[1] = { ControllerTest(&sub) };

    ASSERT_THAT(FindAndCheck<1>(subscriptions, typeLocSmoke, controllers));

    ControllerTest controllersNoise[0] = {};
    ASSERT_THAT(FindAndCheck<0>(subscriptions, typeLocNoise, controllersNoise));
END_TEST

BEGIN_TEST(test_subscribe_two_events_two_observer)
    time_t currentTime;
    time(&currentTime);

    EventTypeLoc typeLocSmoke("SMOKE_DETECTED", Location("1", "room_1_a"));
    EventTypeLoc typeLocEntrance("ENTRANCE_REQUEST", Location("2", "room_1_b"));

    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);
    ControllerTest controllers[2] = { ControllerTest(&sub), ControllerTest(&sub) };

    ASSERT_THAT(FindAndCheck<2>(subscriptions, typeLocSmoke, controllers));
    ASSERT_THAT(FindAndCheck<2>(subscriptions, typeLocEntrance, controllers));
END_TEST

BEGIN_SUITE(test_subscriptions)
    TEST(test_subscribe_one_event)
    TEST(test_subscribe_two_events_one_observer)
    TEST(test_subscribe_two_events_two_observer)
END_SUITE