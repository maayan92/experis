#include "mu_test.h"
#include <vector>

#include "runnable.hpp"
#include "sensorAgentBucket.hpp"
#include "temperatureSensor.hpp"
#include "temperaturePayload.hpp"
#include "thread.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;
using namespace smart_house;

struct InsertSensor : public IRunnable {
    InsertSensor(SensorAgentBucket& a_agents, vector<DeviceId> a_deviceId, TemperatureSensor* a_sensors)
    : m_agents(a_agents)
    , m_deviceId(a_deviceId)
    , m_sensors(a_sensors)
    {}

    void operator()() {
        for(size_t i = 0; i < m_deviceId.size(); ++i) {
            m_agents.AddSensor(m_deviceId[i], &m_sensors[i]);
        }
    }

private:
    SensorAgentBucket& m_agents;
    vector<DeviceId> m_deviceId;
    TemperatureSensor* m_sensors;
};

BEGIN_TEST(test_sensors_bucket_add_sensor)
    DeviceId deviceId("Temprature-1-a");
    Device device = { deviceId, EventTypeLoc("ambient_temp", Location("1", "room_1_a")), "", "units:F; lower:-5; upper:55; period:12" };
    TemperatureSensor sensor(device);

    SensorAgentBucket agents;
    agents.AddSensor(deviceId, &sensor);

    IObserver* result = 0;
    agents.FindSensor(deviceId, result);
    result = dynamic_cast<TemperatureSensor*>(result);
    ASSERT_THAT(result);
    ASSERT_EQUAL(result, &sensor);
    ASSERT_EQUAL(1, agents.Size());
END_TEST

BEGIN_TEST(test_sensors_bucket_double_add_sensor)
    DeviceId deviceId("Temprature-1-a");
    Device device = { deviceId, EventTypeLoc("ambient_temp", Location("1", "room_1_a")), "", "units:F; lower:-5; upper:55; period:12" };
    TemperatureSensor sensor(device);

    SensorAgentBucket agents;
    agents.AddSensor(deviceId, &sensor);
    agents.AddSensor(deviceId, &sensor);

    ASSERT_EQUAL(1, agents.Size());
END_TEST

BEGIN_TEST(test_sensors_bucket_add_some_sensors_with_threads)
    vector<DeviceId> deviceId;
    deviceId.push_back("Temprature-1-a");
    deviceId.push_back("Temprature-2-a");
    deviceId.push_back("Temprature-3-a");
    deviceId.push_back("Temprature-4-a");
    deviceId.push_back("Temprature-5-a");
    EventTypeLoc typeLoc("ambient_temp", Location("1", "room_1_a"));
    Configuration config("units:F; lower:-5; upper:55; period:12");
    Device device[] = { { deviceId[0], typeLoc, string(), config }
                        , { deviceId[1], typeLoc, string(), config } 
                        , { deviceId[2], typeLoc, string(), config }
                        , { deviceId[3], typeLoc, string(), config }
                        , { deviceId[4], typeLoc, string(), config } };

    TemperatureSensor sensor[] = { TemperatureSensor(device[0])
                                , TemperatureSensor(device[1])
                                , TemperatureSensor(device[2])
                                , TemperatureSensor(device[3])
                                , TemperatureSensor(device[4]) };

    SensorAgentBucket agents;
    Thread<InsertSensor> t1(shared_ptr<InsertSensor>(new InsertSensor(agents, vector<DeviceId>(deviceId.begin(), deviceId.end()-2), sensor)));
    
    Thread<InsertSensor> t2(shared_ptr<InsertSensor>(new InsertSensor(agents, vector<DeviceId>(deviceId.begin()+2, deviceId.end()), sensor + 2)));

    t1.Join();
    t2.Join();
    ASSERT_EQUAL(5, agents.Size());
END_TEST

BEGIN_TEST(test_sensors_bucket_find_sensors_add_some_with_threads)
    vector<DeviceId> deviceId;
    deviceId.push_back("Temprature-1-a");
    deviceId.push_back("Temprature-2-a");
    deviceId.push_back("Temprature-3-a");
    deviceId.push_back("Temprature-4-a");
    deviceId.push_back("Temprature-5-a");
    EventTypeLoc typeLoc("ambient_temp", Location("1", "room_1_a"));
    Configuration config("units:F; lower:-5; upper:55; period:12");
    Device device[] = { { deviceId[0], typeLoc, string(), config }
                        , { deviceId[1], typeLoc, string(), config } 
                        , { deviceId[2], typeLoc, string(), config }
                        , { deviceId[3], typeLoc, string(), config }
                        , { deviceId[4], typeLoc, string(), config } };

    TemperatureSensor sensor[] = { TemperatureSensor(device[0])
                                , TemperatureSensor(device[1])
                                , TemperatureSensor(device[2])
                                , TemperatureSensor(device[3])
                                , TemperatureSensor(device[4]) };

    SensorAgentBucket agents;
    Thread<InsertSensor> t1(shared_ptr<InsertSensor>(new InsertSensor(agents, vector<DeviceId>(deviceId.begin(), deviceId.end()-2), sensor)));
    
    Thread<InsertSensor> t2(shared_ptr<InsertSensor>(new InsertSensor(agents, vector<DeviceId>(deviceId.begin()+2, deviceId.end()), sensor + 2)));

    t1.Join();
    t2.Join();

    for(size_t i = 0; i < 5; ++i) {
        IObserver* result = 0;
        agents.FindSensor(deviceId[i], result);
        result = dynamic_cast<TemperatureSensor*>(result);
        ASSERT_THAT(result);
        ASSERT_EQUAL(result, &sensor[i]);
    }

    ASSERT_EQUAL(5, agents.Size());
END_TEST

BEGIN_SUITE(test_sensor_agent_bucket)
    TEST(test_sensors_bucket_add_sensor)
    TEST(test_sensors_bucket_double_add_sensor)
    TEST(test_sensors_bucket_add_some_sensors_with_threads)
    TEST(test_sensors_bucket_find_sensors_add_some_with_threads)
END_SUITE