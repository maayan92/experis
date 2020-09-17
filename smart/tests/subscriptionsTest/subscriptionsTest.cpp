#include "subscriptionHandler.hpp"
#include "controllerTest.hpp"
#include "payloadSmoke.hpp"
#include "event.hpp"
#include "mu_test.h"
#include <iostream>
using namespace std;
using namespace smart_house;

BEGIN_TEST(test_subscribe_one_event)
    time_t currentTime;
    time(&currentTime);

    EventTypeLoc typeLoc("SMOKE_DETECTED", Location("1", "room_1_a"));

    Subscriptions subscriptions;
    SubscriptionHandler sub(subscriptions);
    ControllerTest cs(&sub);
    subscriptions.Upsert(typeLoc, &cs);

    set<IObserver*> ob;
    try {
        subscriptions.Find(typeLoc, ob);
    } catch(const exception& exc) {
        ASSERT_FAIL(exc.what());
    }

    time_t t;
    time(&t);
    PayloadSmoke ps;

    Event e = {localtime(&t), &ps, typeLoc};
    (*ob.begin())->Notify(e);

    ASSERT_THAT(typeLoc == cs.GetEventTypeLocation());
    ASSERT_EQUAL(1, ob.size());
END_TEST

BEGIN_SUITE(test_subscriptions)
    TEST(test_subscribe_one_event)
END_SUITE