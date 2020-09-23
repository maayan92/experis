#ifndef ISUBSCRIBERS_FINDER_HPP
#define ISUBSCRIBERS_FINDER_HPP

#include <set>
#include "uncopyable.hpp"
#include "eventTypeLoc.hpp"
#include "iObserver.hpp"

namespace smart_house {

class ISubscribersFinder : private experis::Uncopyable{
public:
    virtual ~ISubscribersFinder();

    virtual void FindControllers(const EventTypeLoc& a_typeLocation, std::set<IObserver*>& a_observers) = 0;

protected:
    ISubscribersFinder();
};

} // smart_house

#endif