#ifndef ROOM_1_A_APRINKLER_HPP
#define ROOM_1_A_APRINKLER_HPP

#include <sstream>
#include "iSubscription.hpp"
#include "absController.hpp"
#include "device.hpp"
#include "fileLog.hpp"

namespace smart_house {

//controller
class Room1aSprinkler : public Controller {
public:
    Room1aSprinkler(ISubscription* a_subscription, Device& a_device);
    virtual ~Room1aSprinkler();

    virtual void Notify(const Event& a_newEvent);

private:
    ISubscription* m_subscription;
    Device m_device;
    experis::FileLog& m_log;
    std::ofstream m_logFile;
};

} // smart_house

#endif