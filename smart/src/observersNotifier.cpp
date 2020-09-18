#include "observersNotifier.hpp"
using namespace std;

namespace smart_house {

void ObserversNotifier::NotifiAll(const Event& a_event, set<IObserver*>& a_observers)
{
    set<IObserver*>::iterator itrEnd = a_observers.end();
    for(set<IObserver*>::iterator itr = a_observers.begin(); itr != itrEnd; ++itr) {
        (*itr)->Notify(a_event);
    }
}

} // smart_house