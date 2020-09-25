#include "mu_test.h"
#include <iostream>

#include "sharedLibrarySo.hpp"
#include "subscriptionHandler.hpp"
#include "subscriptions.hpp"
#include "HvacPayload.hpp"
using namespace std;
using namespace smart_house;


BEGIN_TEST(test_shared_library_so)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    SharedLibrarySo observers("libControllerHVAC.so");

    typedef IObserver* (*ObserverFactory)(ISubscription*);
    ObserverFactory factory = observers.SymbolAddr<ObserverFactory>("CreateObserver");

    IObserver* o = factory(&subHandler);

    time_t t;
    time(&t);
    HvacPayload data("10.10.1.64", "77", "Fire_Detected|ROOM_EMPTY");

    Event event = { localtime(&t), &data, EventTypeLoc("TestHVAC", Location("1", "room_1_a")) };
    o->Notify(event);

    ASSERT_PASS();
END_TEST

BEGIN_SUITE(test_shared_library)
    TEST(test_shared_library_so)
END_SUITE