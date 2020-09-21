#include "eventsExecutor.hpp"
#include "subscribersFinder.hpp"
using namespace std;

namespace smart_house {

EventsExecutor::EventsExecutor(advcpp::WaitableQueue<Event>& a_eventQueue, IObserversNotifier* a_notifier)
: m_eventQueue(a_eventQueue)
, m_notifier(a_notifier)
{
}

void EventsExecutor::SendAllEvents(Subscriptions& a_subscriptions)
{
    SubscribersFinder finder(a_subscriptions);

    for(;;) {
        Event event;
        m_eventQueue.Deque(event);
        
        set<IObserver*> observers;
        finder.FindControllers(event.m_typeAndLocation, observers);
        m_notifier->NotifyAll(event, observers);
    }
}

} // smart_house