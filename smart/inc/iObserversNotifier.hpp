#ifndef IOBSERVERS_NOTIFIER_HPP
#define IOBSERVERS_NOTIFIER_HPP

#include <set>
#include "eventTypeLoc.hpp"
#include "iObserver.hpp"

namespace smart_house {

class IObserversNotifier {
public:
    virtual ~IObserversNotifier();

    virtual void NotifiAll(const Event& a_event, std::set<IObserver*>& a_observers) = 0;
};

} // smart_house

#endif