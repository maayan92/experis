#ifndef OBSERVERS_NOTIFIER_HPP
#define OBSERVERS_NOTIFIER_HPP

#include "IObserversNotifier.hpp"

namespace smart_house {

class ObserversNotifier : public IObserversNotifier {
public:
    //ObserversNotifier() = default;
    //~ObserversNotifier() = default;

    virtual void NotifiAll(const Event& a_event, std::set<IObserver*>& a_observers);
};

} // smart_house

#endif