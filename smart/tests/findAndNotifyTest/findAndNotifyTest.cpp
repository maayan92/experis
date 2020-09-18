#include "mu_test.h"
#include <iostream>
#include <vector>

#include "subscribersFinder.hpp"
#include "observersNotifier.hpp"
#include "subscriptionHandler.hpp"
#include "controllerTest.hpp"
#include "payloadSmoke.hpp"
using namespace std;
using namespace smart_house;

template<size_t SIZE>
static bool FindAndCheckResult(set<IObserver*>& a_observers, EventTypeLoc& a_typeLocSmoke, ControllerTest* a_controllers)
{
    time_t t;
    time(&t);
    PayloadSmoke ps;
    Event event = {localtime(&t), &ps, a_typeLocSmoke};

    ObserversNotifier notifier;
    notifier.NotifiAll(event, a_observers);
    if(SIZE != a_observers.size()) {
        return false;
    }

    for(size_t i = 0; i < SIZE; ++i) {
        if(!(a_typeLocSmoke == a_controllers[i].GetEventTypeLocation())) {
            return false;
        }
    }

    return true;
}

// **** tests **** //

BEGIN_TEST(test_find_all_subscribers_one_event)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    vector<EventTypeLoc> typeLocSmoke;
    typeLocSmoke.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    ControllerTest controller(&subHandler, typeLocSmoke);

    set<IObserver*> observers;
    SubscribersFinder finder(subs);
    finder.FindControllers(typeLocSmoke[0], observers);

    ASSERT_EQUAL(1, observers.size());
END_TEST

BEGIN_TEST(test_find_and_notify_one_event_N_controllers)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);

    const size_t NUM_OF_CONTROLLERS = 5;
    vector<EventTypeLoc> typeLocSmoke;
    typeLocSmoke.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));

    ControllerTest controllers[NUM_OF_CONTROLLERS] = { ControllerTest(&subHandler, typeLocSmoke) \
                        , ControllerTest(&subHandler, typeLocSmoke), ControllerTest(&subHandler, typeLocSmoke) \
                        , ControllerTest(&subHandler, typeLocSmoke), ControllerTest(&subHandler, typeLocSmoke) };

    set<IObserver*> observers;
    SubscribersFinder finder(subs);
    finder.FindControllers(typeLocSmoke[0], observers);
    ASSERT_EQUAL(NUM_OF_CONTROLLERS, observers.size());
    ASSERT_THAT(FindAndCheckResult<NUM_OF_CONTROLLERS>(observers, typeLocSmoke[0], controllers));
END_TEST

BEGIN_SUITE(test_find_and_notify)
    TEST(test_find_all_subscribers_one_event)

    TEST(test_find_and_notify_one_event_N_controllers)
END_SUITE