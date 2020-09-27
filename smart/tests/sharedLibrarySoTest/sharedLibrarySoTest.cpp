#include "mu_test.h"
#include <iostream>
#include <fstream>
#include <vector>

#include "sharedLibrarySo.hpp"
#include "subscriptionHandler.hpp"
#include "subscriptions.hpp"
#include "HvacPayload.hpp"
using namespace std;
using namespace smart_house;

static string GetValue(string& a_buffer, size_t& a_position)
{
    size_t pos = a_buffer.find(":", a_position + 1) + 2;
    size_t posLast = a_buffer.find("\t", pos);
    a_position = posLast;
    string result = a_buffer.substr(pos, posLast - pos);

    return result;
}

static bool CheckNotifyResultHvac(ifstream& a_logFile, const Event& a_event, size_t a_numOfEvents)
{
    string buffer;
    size_t pos = 0;

    while(getline(a_logFile, buffer) && a_numOfEvents > 0) {
        if(GetValue(buffer, pos) != a_event.m_typeAndLocation.m_type) {
            return false;
        }
        if(GetValue(buffer, pos) != a_event.m_typeAndLocation.m_location.m_room) {
            return false;
        }
        if(GetValue(buffer, pos) != a_event.m_typeAndLocation.m_location.m_floor) {
            return false;
        }

        GetValue(buffer, pos);
        
        HvacPayload* data = dynamic_cast<HvacPayload*>(a_event.m_data);
        if(GetValue(buffer, pos) != data->m_iot) {
            return false;
        }
        if(GetValue(buffer, pos) != data->m_tmp) {
            return false;
        }
        if(GetValue(buffer, pos) != data->m_shutdown) {
            return false;
        }
        --a_numOfEvents;
    }
    return true;
}

// **** tests: **** //

BEGIN_TEST(test_shared_library_so_one_event_one_observer)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    SharedLibrarySo observers("./libControllerHVAC.so");

    typedef IObserver* (*ObserverFactory)(ISubscription*, vector<EventTypeLoc>&);
    ObserverFactory factory = observers.SymbolAddr<ObserverFactory>("CreateObserver");

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("TestHVAC", Location("1", "room_1_a")));
    IObserver* o = factory(&subHandler, typeLoc);

    time_t t;
    time(&t);
    HvacPayload data("10.10.1.64", "77", "Fire_Detected|ROOM_EMPTY");

    Event event = { localtime(&t), &data, typeLoc[0] };
    o->Notify(event);

    ifstream logFile("hvac_log.txt");

    ASSERT_THAT(CheckNotifyResultHvac(logFile, event, 1));
END_TEST

BEGIN_TEST(test_shared_library_so_one_observer_all_floor_event)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    SharedLibrarySo observers("./libControllerHVAC.so");

    typedef IObserver* (*ObserverFactory)(ISubscription*, vector<EventTypeLoc>&);
    ObserverFactory factory = observers.SymbolAddr<ObserverFactory>("CreateObserver");

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("All", Location("1", "room_1_a")));
    IObserver* o = factory(&subHandler, typeLoc);

    time_t t;
    time(&t);
    HvacPayload data("10.10.1.64", "77", "Fire_Detected|ROOM_EMPTY");

    Event event = { localtime(&t), &data, EventTypeLoc("TestHVAC", Location("1", "room_1_a")) };
    o->Notify(event);

    ifstream logFile("hvac_log.txt");

    ASSERT_THAT(CheckNotifyResultHvac(logFile, event, 1));
END_TEST

BEGIN_TEST(test_shared_library_so_multi_events_one_observer)
    Subscriptions subs;
    SubscriptionHandler subHandler(subs);
    SharedLibrarySo observers("./libControllerHVAC.so");

    typedef IObserver* (*ObserverFactory)(ISubscription*, vector<EventTypeLoc>&);
    ObserverFactory factory = observers.SymbolAddr<ObserverFactory>("CreateObserver");

    vector<EventTypeLoc> typeLoc;
    typeLoc.push_back(EventTypeLoc("All", Location("1", "room_1_a")));
    typeLoc.push_back(EventTypeLoc("TestHVAC", Location("2", "room_1_b")));
    typeLoc.push_back(EventTypeLoc("HVAC", Location("3", "All")));
    IObserver* o = factory(&subHandler, typeLoc);

    time_t t;
    time(&t);
    HvacPayload data("10.10.1.64", "77", "Fire_Detected|ROOM_EMPTY");

    Event event = { localtime(&t), &data, EventTypeLoc("TestHVAC", Location("2", "room_1_a")) };
    Event event2 = { localtime(&t), &data, EventTypeLoc("HVAC", Location("1", "room_1_a")) };
    o->Notify(event);
    o->Notify(event2);

    ifstream logFile("hvac_log.txt");

    ASSERT_THAT(CheckNotifyResultHvac(logFile, event, 1));
    ASSERT_THAT(CheckNotifyResultHvac(logFile, event2, 1));
END_TEST

BEGIN_SUITE(test_shared_library)
    TEST(test_shared_library_so_one_event_one_observer)
    TEST(test_shared_library_so_one_observer_all_floor_event)
    TEST(test_shared_library_so_multi_events_one_observer)
END_SUITE