#ifndef OBSERVERS_NOTIFIER_HPP
#define OBSERVERS_NOTIFIER_HPP

#include "iObserversNotifier.hpp"

namespace smart_house {

class ObserversNotifier : public IObserversNotifier {
public:
    //ObserversNotifier() = default;
    //~ObserversNotifier() = default;

    virtual void NotifyAll(const Event& a_event, std::set<IObserver*>& a_observers);
};

} // smart_house

#endif