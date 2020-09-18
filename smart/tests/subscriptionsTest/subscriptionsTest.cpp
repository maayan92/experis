#include "mu_test.h"
#include <iostream>

#include "subscriptionHandler.hpp"
#include "controllerTest.hpp"
#include "payloadSmoke.hpp"
#include "event.hpp"
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
    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    
    ControllerTest controllers[1] = { ControllerTest(&sub, typeLoc) };
    subscriptions.Upsert(typeLoc[0], &controllers[0]);

    ASSERT_THAT(FindAndCheck<1>(subscriptions, typeLoc[0], controllers));
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

    ASSERT_THAT(FindAndCheck<1>(subscriptions, typeLoc[0], controllers));

    ControllerTest controllersNoise[0] = {};
    ASSERT_THAT(FindAndCheck<0>(subscriptions, typeLocNoise, controllersNoise));
END_TEST

BEGIN_TEST(test_subscribe_two_events_two_observer)
    time_t currentTime;
    time(&currentTime);

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("ENTRANCE_REQUEST", Location("2", "room_1_a")));

    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);

    ControllerTest controllers[2] = { ControllerTest(&sub, typeLoc), ControllerTest(&sub, typeLoc) };

    ASSERT_THAT(FindAndCheck<2>(subscriptions, typeLoc[0], controllers));
    ASSERT_THAT(FindAndCheck<2>(subscriptions, typeLoc[1], controllers));
END_TEST

BEGIN_SUITE(test_subscriptions)
    TEST(test_subscribe_one_event)
    TEST(test_subscribe_two_events_one_observer)
    TEST(test_subscribe_two_events_two_observer)
END_SUITE