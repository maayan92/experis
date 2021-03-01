#ifndef DOOR_4_A_HPP
#define DOOR_4_A_HPP

#include <sstream>
#include "iSubscription.hpp"
#include "absController.hpp"
#include "device.hpp"
#include "fileLog.hpp"

namespace smart_house {

struct Door4aConfigData {

    std::string m_token;
    std::string m_event;
    std::string m_from;

};

//controller
class Door4a : public Controller {
public:
    Door4a(ISubscription* a_subscription, Device& a_device);
    virtual ~Door4a();

    virtual void Notify(const Event& a_newEvent);

private:
    void parseConfig();
    std::string getNextValue(const std::string& a_valName, size_t& a_end);

private:
    ISubscription* m_subscription;
    Device m_device;
    experis::FileLog& m_log;
    std::ofstream m_logFile;
    Door4aConfigData m_data;
};

} // smart_house

#endif