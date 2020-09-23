#ifndef IOBSERVERS_NOTIFIER_HPP
#define IOBSERVERS_NOTIFIER_HPP

#include <set>
#include "iObserver.hpp"
#include "uncopyable.hpp"

namespace smart_house {

class IObserversNotifier : private experis::Uncopyable{
public:
    virtual ~IObserversNotifier();

    virtual void NotifyAll(const Event& a_event, std::set<IObserver*>& a_observers) = 0;

protected:
    IObserversNotifier();
};

} // smart_house

#endif