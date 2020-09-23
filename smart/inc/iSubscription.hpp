#ifndef ISUBSCRIPTION_HPP
#define ISUBSCRIPTION_HPP

#include "eventTypeLoc.hpp"
#include "iObserver.hpp"

namespace smart_house {

class ISubscription {
public:
    virtual ~ISubscription();

    virtual void Subscribe(const EventTypeLoc& a_eventTypeLocation, IObserver* a_observer) = 0;
    //virtual void UnSubscribe(const EventTypeLoc& a_eventTypeLocation, const IObserver* a_controller) = 0;

protected:
    ISubscription();
};

} // smart_house

#endif