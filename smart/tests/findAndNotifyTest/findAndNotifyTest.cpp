#include "mu_test.h"
#include "testsFunctions.hpp"
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
static bool CheckAllControllers(vector<ControllerTest*>& a_allControllers, EventTypeLoc& a_typeLoc, Subscriptions& a_subs)
{
    set<IObserver*> observers;
    SubscribersFinder(a_subs).FindControllers(a_typeLoc, observers);
    ObserversNotifier().NotifyAll(CreateEvent(a_typeLoc), observers);
    
    for(size_t i = 0; i < a_allControllers.size(); ++i) {
        if(!CheckResult<SIZE>(a_typeLoc, a_allControllers[i])) {
            return false;
        }
    }

    return true;
}

// **** tests **** //

BEGIN_TEST(test_notify_all_subscribers_one_observer_one_event)
    Subscriptions subs;
    SensorAgentBucket sensors;
    SubscriptionHandler subHandler(subs, sensors);
    vector<EventTypeLoc> typeLocSmoke;
    typeLocSmoke.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    ControllerTest controllers[] = { ControllerTest(&subHandler, typeLocSmoke) };

    set<IObserver*> observers;
    SubscribersFinder(subs).FindControllers(typeLocSmoke[0], observers);

    ASSERT_EQUAL(1, observers.size());

    ObserversNotifier().NotifyAll(CreateEvent(typeLocSmoke[0]), observers);
    ASSERT_THAT(CheckResult<1>(typeLocSmoke[0], controllers));
END_TEST

BEGIN_TEST(test_find_and_notify_one_event_N_controllers)
    Subscriptions subs;
    SensorAgentBucket sensors;
    SubscriptionHandler subHandler(subs, sensors);

    const size_t NUM_OF_CONTROLLERS = 5;
    vector<EventTypeLoc> typeLocSmoke;
    typeLocSmoke.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));

    ControllerTest controllers[] = { ControllerTest(&subHandler, typeLocSmoke)
                        , ControllerTest(&subHandler, typeLocSmoke), ControllerTest(&subHandler, typeLocSmoke)
                        , ControllerTest(&subHandler, typeLocSmoke), ControllerTest(&subHandler, typeLocSmoke) };

    set<IObserver*> observers;
    SubscribersFinder finder(subs);
    finder.FindControllers(typeLocSmoke[0], observers);

    ASSERT_EQUAL(NUM_OF_CONTROLLERS, observers.size());
    ObserversNotifier().NotifyAll(CreateEvent(typeLocSmoke[0]), observers);
    ASSERT_THAT(CheckResult<5>(typeLocSmoke[0], controllers));
END_TEST

BEGIN_TEST(test_find_and_notify_one_event_no_subscriptions_N_Notify)
    Subscriptions subs;
    SensorAgentBucket sensors;
    SubscriptionHandler subHandler(subs, sensors);

    vector<EventTypeLoc> typeLocSmoke;
    typeLocSmoke.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    EventTypeLoc typeLoc = EventTypeLoc("SMOKE_DETECTED", Location("2", "room_1_a"));

    ControllerTest controllers[] = { ControllerTest(&subHandler, typeLocSmoke)
                        , ControllerTest(&subHandler, typeLocSmoke), ControllerTest(&subHandler, typeLocSmoke) };

    set<IObserver*> observers;
    SubscribersFinder(subs).FindControllers(typeLoc, observers);

    ASSERT_EQUAL(0, observers.size());
    for(size_t i = 0; i < 10; ++i) {
        ObserversNotifier().NotifyAll(CreateEvent(typeLoc), observers);
    }
    ASSERT_THAT(CheckResult<3>(EventTypeLoc(), controllers));
END_TEST

BEGIN_TEST(test_find_and_notify_N_event_M_controllers)
    Subscriptions subs;
    SensorAgentBucket sensors;
    SubscriptionHandler subHandler(subs, sensors);
    
    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("SMOKE_DETECTED", Location("1", "room_1_a")));
    ControllerTest controllersS[] = { ControllerTest(&subHandler, typeLoc)
                        , ControllerTest(&subHandler, typeLoc), ControllerTest(&subHandler, typeLoc)};

    typeLoc.push_back(EventTypeLoc("NOISE_LEVEL", Location("1", "room_2_a")));
    ControllerTest controllersSN[] = { ControllerTest(&subHandler, typeLoc)
                        , ControllerTest(&subHandler, typeLoc), ControllerTest(&subHandler, typeLoc)};

    typeLoc.push_back(EventTypeLoc("ENTRANCE_REQUEST", Location("2", "room_1_a")));
    ControllerTest controllersSNE[] = { ControllerTest(&subHandler, typeLoc)
                        , ControllerTest(&subHandler, typeLoc), ControllerTest(&subHandler, typeLoc)};

    vector<ControllerTest*> allControllers;
    allControllers.push_back(controllersS);
    allControllers.push_back(controllersSN);
    allControllers.push_back(controllersSNE);

    ASSERT_THAT(CheckAllControllers<3>(allControllers, typeLoc[0], subs));
    
    allControllers.erase(allControllers.begin());
    ASSERT_THAT(CheckAllControllers<3>(allControllers, typeLoc[1], subs));
    
    allControllers.erase(allControllers.begin());
    ASSERT_THAT(CheckAllControllers<3>(allControllers, typeLoc[2], subs));
END_TEST

BEGIN_SUITE(test_find_and_notify)
    TEST(test_notify_all_subscribers_one_observer_one_event)
    TEST(test_find_and_notify_one_event_N_controllers)
    TEST(test_find_and_notify_one_event_no_subscriptions_N_Notify)
    TEST(test_find_and_notify_N_event_M_controllers)
END_SUITE