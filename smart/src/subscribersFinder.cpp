#include "subscribersFinder.hpp"
using namespace std;
using namespace experis;

namespace smart_house {

SubscribersFinder::SubscribersFinder(Subscriptions& a_subscriptions)
: m_subscriptions(a_subscriptions)
{
}

void SubscribersFinder::findByTypeLocation(const EventType& a_type, const Location& a_location, set<IObserver*>& a_observers)
{
    set<IObserver*> allObservers;
    
    m_subscriptions.Find(EventTypeLoc(a_type, a_location), allObservers);
    a_observers.insert(allObservers.begin(), allObservers.end());
}

void SubscribersFinder::FindControllers(const EventTypeLoc& a_typeLocation, set<IObserver*>& a_observers)
{
    findByTypeLocation(a_typeLocation.m_type, a_typeLocation.m_location, a_observers);
    findByTypeLocation(a_typeLocation.m_type, Location("All", a_typeLocation.m_location.m_room), a_observers);
    findByTypeLocation(a_typeLocation.m_type, Location(a_typeLocation.m_location.m_floor, "All"), a_observers);
    findByTypeLocation(a_typeLocation.m_type, Location("All", "All"), a_observers);

    findByTypeLocation("All", a_typeLocation.m_location, a_observers);
    findByTypeLocation("All", Location("All", a_typeLocation.m_location.m_room), a_observers);
    findByTypeLocation("All", Location(a_typeLocation.m_location.m_floor, "All"), a_observers);
    findByTypeLocation("All", Location("All", "All"), a_observers);
}

} // smart_house