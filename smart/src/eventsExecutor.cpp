#include "eventsExecutor.hpp"
using namespace std;
using namespace advcpp;

namespace smart_house {

EventsExecutor::EventsExecutor(WaitableQueue<Event>& a_eventQueue, IObserversNotifier& a_notifier, ISubscribersFinder* a_finder)
: m_shutDown(false)
, m_eventQueue(a_eventQueue)
, m_notifier(a_notifier)
, m_finder(a_finder)
{
}

void EventsExecutor::SendAllEvents()
{    
    for(;;) {
        Event event;
        m_eventQueue.Deque(event);
        if(!event.isValid()) {
            return;
        }

        set<IObserver*> observers;
        m_finder->FindControllers(event.m_typeAndLocation, observers);
        m_notifier.NotifyAll(event, observers);
        
        if(m_shutDown.GetValue()) {
            return;
        }
    }
}

void EventsExecutor::ShutDown()
{
    if(m_shutDown.CheckAndSet()) {
        m_eventQueue.ShutDown();
    }
}

} // smart_house
