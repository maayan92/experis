#include "mu_test.h"

#include "eventCreatorMT.hpp"
#include "temperatureSensor.hpp"
#include "temperaturePayload.hpp"
using namespace std;
using namespace advcpp;
using namespace smart_house;

BEGIN_TEST(test_event_creator_one_event)
    WaitableQueue<Event> events;

    Device device = { "Temprature-1-a", EventTypeLoc("ambient_temp", Location("1", "room_1_a")), string(), "units: F; lower: -5; upper:55; period: 12" };
    TemperatureSensor sensor(device);

    {
        EventCreatorMT creator(events);
        time_t cTime = time(NULL);
        creator.CreateEvent(SensorInfo("Temprature-1-a", "42C|rising", localtime(&cTime)), &sensor);
    }
    ASSERT_EQUAL(1, events.Size());

    Event event;
    events.Deque(event);

    ASSERT_THAT(!event.IsNotValid());
    ASSERT_THAT(device.m_typeLocation == event.m_typeAndLocation);
    shared_ptr<TemperaturePayload> data;
    event.m_data.Swap(data);
    ASSERT_THAT(data);
    ASSERT_THAT(data->m_tempRising);
    ASSERT_EQUAL(42.0, data->m_currentTemp);
END_TEST

BEGIN_TEST(test_event_creator_multi_events_one_sensor)
    WaitableQueue<Event> events;

    Device device = { "Temprature-1-a", EventTypeLoc("ambient_temp", Location("1", "room_1_a")), string(), "units: F; lower: -5; upper:55; period: 12" };
    TemperatureSensor sensor(device);
    
    {
        EventCreatorMT creator(events);
        for(size_t i = 0; i < 1000; ++i) {
            time_t cTime = time(NULL);
            creator.CreateEvent(SensorInfo("Temprature-1-a", "42C|rising", localtime(&cTime)), &sensor);
        }
    }

    ASSERT_EQUAL(1000, events.Size());
END_TEST

BEGIN_TEST(test_event_creator_multi_events_multi_sensor)
    WaitableQueue<Event> events;

    Device deviceFirst = { "Temprature-1-a", EventTypeLoc("ambient_temp", Location("1", "room_1_a")), string(), "units: F; lower: -5; upper:55; period: 12" };
    TemperatureSensor sensorFirst(deviceFirst);
    Device deviceSecond = { "Temprature-2-a", EventTypeLoc("ambient_temp", Location("1", "room_1_a")), string(), "units: F; lower: -5; upper:55; period: 12" };
    TemperatureSensor sensorSecond(deviceSecond);
    Device deviceTheard = { "Temprature-3-a", EventTypeLoc("ambient_temp", Location("1", "room_1_a")), string(), "units: F; lower: -5; upper:55; period: 12" };
    TemperatureSensor sensorTheard(deviceTheard);

    {
        EventCreatorMT creator(events);
        for(size_t i = 0; i < 1000; ++i) {
            time_t cTime = time(NULL);
            creator.CreateEvent(SensorInfo("Temprature-1-a", "42C|rising", localtime(&cTime)), &sensorFirst);
            creator.CreateEvent(SensorInfo("Temprature-2-a", "42C|rising", localtime(&cTime)), &sensorSecond);
            creator.CreateEvent(SensorInfo("Temprature-3-a", "42C|rising", localtime(&cTime)), &sensorTheard);
        }
    }

    ASSERT_EQUAL(3000, events.Size());
END_TEST

BEGIN_SUITE(test_event_creator)
    TEST(test_event_creator_one_event)
    TEST(test_event_creator_multi_events_one_sensor)
    TEST(test_event_creator_multi_events_multi_sensor)
END_SUITE