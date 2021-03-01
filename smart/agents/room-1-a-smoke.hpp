#ifndef ROOM_1_A_SMOKE_HPP
#define ROOM_1_A_SMOKE_HPP

#include <sstream>
#include "iSubscription.hpp"
#include "absSensor.hpp"
#include "device.hpp"
#include "fileLog.hpp"

namespace smart_house {

struct Room1aSmokePayload : public IPayload {

    Room1aSmokePayload()
    : m_hasSmokeInTheRoom()
    , m_activateSprinklers()
    {}

    Room1aSmokePayload(bool a_hasSmokeInTheRoom, bool a_activateSprinklers)
    : m_hasSmokeInTheRoom(a_hasSmokeInTheRoom)
    , m_activateSprinklers(a_activateSprinklers)
    {}

    bool m_hasSmokeInTheRoom;
    bool m_activateSprinklers;

    virtual void Print(std::ostream& a_os) const {
        a_os << "in room 1_a: there is " << (m_hasSmokeInTheRoom ? "" : "no ") << "smoke, and the sprinklers are "
            << (m_activateSprinklers ? "" : "not ") << "activated" << '\n';
    }
};

//sensor
class Room1aSmoke : public Sensor {
public:
    Room1aSmoke(ISubscription* a_subscription, Device& a_device);
    virtual ~Room1aSmoke();

    virtual void CreateEvent(const SensorInfo& a_info, struct Event& a_event);

private:
    ISubscription* m_subscription;
    Device m_device;
    experis::FileLog& m_log;
    std::ofstream m_logFile;
};

} // smart_house

#endif