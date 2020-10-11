#include "mu_test.h"

#include "parser.hpp"
#include "configuration.hpp"
using namespace std;
using namespace smart_house;

BEGIN_TEST(test_parser_one_device)
    string buffer("[ light-1-a-2 ]|type = PhilipsHue|room = room_1_a|floor = 1|log = lights|config = iot:1008,sat:242, brigh:154, hue:8200|");

    Parser parser;
    Device result;
    parser.Parse(buffer, result);

    ASSERT_EQUAL("light-1-a-2", result.m_deviceId);
    ASSERT_EQUAL("PhilipsHue", result.m_typeLocation.m_type);
    ASSERT_THAT(Location("1", "room_1_a") == result.m_typeLocation.m_location);
    ASSERT_EQUAL("lights", result.m_log);
    ASSERT_EQUAL("iot:1008,sat:242, brigh:154, hue:8200", result.m_config);
END_TEST

BEGIN_TEST(test_parser_one_device_without_config)
    string buffer("[ light-1-a-2 ]|type = PhilipsHue|room = room_1_a|floor = 1|log = lights|");

    Parser parser;
    Device result;
    parser.Parse(buffer, result);

    ASSERT_EQUAL("light-1-a-2", result.m_deviceId);
    ASSERT_EQUAL("PhilipsHue", result.m_typeLocation.m_type);
    ASSERT_THAT(Location("1", "room_1_a") == result.m_typeLocation.m_location);
    ASSERT_EQUAL("lights", result.m_log);
    ASSERT_EQUAL("", result.m_config);
END_TEST

BEGIN_TEST(test_configuration_from_file)
    ifstream file("configuration.txt");

    Parser parser;
    Configuration config(parser);
    config.ReadFile(file);

    vector<Device> devices;
    Device device1 = { "light-1-a-1", EventTypeLoc("PhilipsHue", Location("1", "room_1_a")), "lights", "iot:1003,sat:242, brigh:154, hue:8200" };
    Device device2 = { "light-1-a-2", EventTypeLoc("PhilipsHue", Location("1", "room_1_a")), "lights", "iot:1008,sat:242, brigh:154, hue:8200" };
    Device device3 = { "badge-reader-4-g", EventTypeLoc("IDentCard", Location("4", "entrance_4_g")), "security", "{Token: “78DF6A2BA25DA87”, Event: “badge id”}" };
    Device device4 = { "door-4-a", EventTypeLoc("ZigBeeLock", Location("4", "room_4_a")), "security", "{Token: “78DF6A2BA25DA87”, Event: “badge id”, From: “entrance_4_g”}" };
    Device device5 = { "room-1-a-smoke", EventTypeLoc("smoke_detector", Location("1", "room_1_a")), "safety", "" };
    Device device6 = { "room-1-a-sprinkler", EventTypeLoc("sprinx", Location("1", "room_1_a")), "safety", "" };

    devices.push_back(device1);
    devices.push_back(device2);
    devices.push_back(device3);
    devices.push_back(device4);
    devices.push_back(device5);
    devices.push_back(device6);

    vector<Device> result;
    config.GetDevices(result);

    ASSERT_THAT(devices[0] == result[0]);
    ASSERT_THAT(devices[1] == result[1]);
    ASSERT_THAT(devices[2] == result[2]);
    ASSERT_THAT(devices[3] == result[3]);
    ASSERT_THAT(devices[4] == result[4]);
    ASSERT_THAT(devices[5] == result[5]);
END_TEST

BEGIN_SUITE(test_configuration)
    TEST(test_parser_one_device)
    TEST(test_parser_one_device_without_config)
    TEST(test_configuration_from_file)
END_SUITE