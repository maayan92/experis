#include "sensorAgentBucket.hpp"
#include "mutexLocker.hpp"
#include <algorithm>
using namespace std;
using namespace experis;

namespace smart_house {

void SensorAgentBucket::AddSensor(const DeviceId& a_deviceId, ISensorAgent* a_sensor)
{
    MutexLocker locker(m_mtx);
    m_agents.insert(make_pair(a_deviceId, a_sensor));
}

void SensorAgentBucket::FindSensor(const DeviceId& a_deviceId, ISensorAgent* a_sensor)
{
    MutexLocker locker(m_mtx);
    Agents::iterator itr = m_agents.find(a_deviceId);
    if(itr != m_agents.end()) {
        a_sensor = itr->second;
    }
}

void SensorAgentBucket::RemoveSensor(const DeviceId& a_deviceId)
{
    MutexLocker locker(m_mtx);
    m_agents.erase(a_deviceId);
}

size_t SensorAgentBucket::Size() const
{
    MutexLocker locker(m_mtx);
    return m_agents.size();
}

} // smart_house