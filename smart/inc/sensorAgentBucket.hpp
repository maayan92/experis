#ifndef SENSOR_AGENT_BUCKET_HPP
#define SENSOR_AGENT_BUCKET_HPP

#include <map>
#include "mutex.hpp"
#include "typedefs.hpp"
#include "uncopyable.hpp"
#include "iObserver.hpp"
#include "shared_ptr.hpp"

namespace smart_house {

class SensorAgentBucket : private experis::Uncopyable {
    typedef std::map<experis::DeviceId, IObserver*> Agents;
public:
    //SensorAgentBucket() = default;
    //~SensorAgentBucket() = default;

    void AddSensor(const experis::DeviceId& a_deviceId, IObserver* a_sensor);
    void FindSensor(const experis::DeviceId& a_deviceId, IObserver*& a_sensor);
    void RemoveSensor(const experis::DeviceId& a_deviceId);

    size_t Size() const;

private:
    mutable experis::Mutex m_mtx;
    Agents m_agents;
};

} // smart_house

#endif