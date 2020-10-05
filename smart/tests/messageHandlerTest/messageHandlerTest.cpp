#include "mu_test.h"

#include "protocol.hpp"
#include "messageHandler.hpp"
#include "eventCreatorMT.hpp"
#include "temperatureSensor.hpp"
#include "temperaturePayload.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;
using namespace smart_house;

BEGIN_TEST(test_message_handler_one_data)
    WaitableQueue<Event> events;

    Device device = { "Temprature-1-a", EventTypeLoc("ambient_temp", Location("1", "room_1_a")), string(), "units: F; lower: -5; upper:55; period: 12" };
    TemperatureSensor* sensorTemp = new TemperatureSensor(device);

    SensorAgentBucket sensors;
    sensors.AddSensor("Temprature-1-a", sensorTemp);
    ASSERT_EQUAL(1, sensors.Size());

    string result;
    time_t currentTime = time(NULL);
    Protocol::Pack(result, SensorInfo("Temprature-1-a", "42C|rising", localtime(&currentTime)));
    {
        EventCreatorMT creator(events);
        messageHandler handler(sensors, creator);
        
        handler.HandleMsg(result.c_str());
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

BEGIN_TEST(test_message_handler_one_data_not_register_sensor)
    WaitableQueue<Event> events;

    Device device = { "Temprature-1-a", EventTypeLoc("ambient_temp", Location("1", "room_1_a")), string(), "units: F; lower: -5; upper:55; period: 12" };
    TemperatureSensor* sensorTemp = new TemperatureSensor(device);

    SensorAgentBucket sensors;
    sensors.AddSensor("Temprature-1-a", sensorTemp);
    ASSERT_EQUAL(1, sensors.Size());
  
    string result;
    time_t currentTime = time(NULL);
    Protocol::Pack(result, SensorInfo("Temprature-2", "42C|rising", localtime(&currentTime)));
    {
        EventCreatorMT creator(events);
        messageHandler handler(sensors, creator);
        
        handler.HandleMsg(result.c_str());
    }

    ASSERT_EQUAL(0, events.Size());
END_TEST

BEGIN_TEST(test_message_handler_multi_data_with_half_msg)
    WaitableQueue<Event> events;

    Device device = { "Temprature-1-a", EventTypeLoc("ambient_temp", Location("1", "room_1_a")), string(), "units: F; lower: -5; upper:55; period: 12" };
    TemperatureSensor* sensorTemp = new TemperatureSensor(device);

    SensorAgentBucket sensors;
    sensors.AddSensor("Temprature-1-a", sensorTemp);
    ASSERT_EQUAL(1, sensors.Size());

    {
        EventCreatorMT creator(events);
        messageHandler handler(sensors, creator);
    
        string result1;
        time_t currentTime = time(NULL);
        Protocol::Pack(result1, SensorInfo("Temprature-1-a", "42C|rising", localtime(&currentTime)));
        
        string result2;
        currentTime = time(NULL);
        Protocol::Pack(result2, SensorInfo("Temprature-1-a", "30C|dropping", localtime(&currentTime)));

        string result3;
        currentTime = time(NULL);
        Protocol::Pack(result3, SensorInfo("Temprature-1-a", "25C|dropping", localtime(&currentTime)));


        string msg(result1 + result2);
        msg += string(result3, 0, 5);
        handler.HandleMsg(msg.c_str());
    }

    ASSERT_EQUAL(2, events.Size());
END_TEST

BEGIN_TEST(test_message_handler_multi_data_half_msg_and_complete_msg)
    WaitableQueue<Event> events;

    Device device = { "Temprature-1-a", EventTypeLoc("ambient_temp", Location("1", "room_1_a")), string(), "units: F; lower: -5; upper:55; period: 12" };
    TemperatureSensor* sensorTemp = new TemperatureSensor(device);

    SensorAgentBucket sensors;
    sensors.AddSensor("Temprature-1-a", sensorTemp);
    ASSERT_EQUAL(1, sensors.Size());

    {
        EventCreatorMT creator(events);
        messageHandler handler(sensors, creator);
    
        string result1;
        time_t currentTime = time(NULL);
        Protocol::Pack(result1, SensorInfo("Temprature-1-a", "42C|rising", localtime(&currentTime)));
        
        string result2;
        currentTime = time(NULL);
        Protocol::Pack(result2, SensorInfo("Temprature-1-a", "30C|dropping", localtime(&currentTime)));

        string result3;
        currentTime = time(NULL);
        Protocol::Pack(result3, SensorInfo("Temprature-1-a", "25C|dropping", localtime(&currentTime)));


        string msg(result1 + result2);
        msg += string(result3, 0, 5);
        handler.HandleMsg(msg.c_str());
    
        msg = string(result3, 5);
        msg += result1;
        handler.HandleMsg(msg.c_str());
    }

    ASSERT_EQUAL(4, events.Size());
END_TEST

BEGIN_SUITE(test_message_handler)
    TEST(test_message_handler_one_data)
    TEST(test_message_handler_one_data_not_register_sensor)
    TEST(test_message_handler_multi_data_with_half_msg)
    TEST(test_message_handler_multi_data_half_msg_and_complete_msg)
END_SUITE