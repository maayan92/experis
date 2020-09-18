#ifndef CONTROLLER_SMOKER_HPP
#define CONTROLLER_SMOKER_HPP

#include <vector>
#include "iObserver.hpp"
#include "iSubscription.hpp"

namespace smart_house {

class ControllerTest : public IObserver {
public:
    explicit ControllerTest(ISubscription* a_subscription, const std::vector<EventTypeLoc>& a_typeLocArr);
    //virtual ~ControllerTest() = default;
    
    virtual void Notify(const Event& a_newEvent);
    EventTypeLoc GetEventTypeLocation() const;

private:
    ISubscription* m_subscription;
    EventTypeLoc m_eventTypeLocation;
    std::vector<EventTypeLoc> m_typeLocArr;
};

} // smart_house

#endif