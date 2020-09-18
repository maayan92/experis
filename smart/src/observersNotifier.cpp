#include "observersNotifier.hpp"
using namespace std;

namespace smart_house {

void ObserversNotifier::NotifiAll(const Event& a_event, set<IObserver*>& a_observers)
{
    for(set<IObserver*>::iterator itr = a_observers.begin(); itr != a_observers.end(); ++itr) {
        (*itr)->Notify(a_event);
    }
}

} // smart_house