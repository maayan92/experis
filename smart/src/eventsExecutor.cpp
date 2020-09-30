#include "eventsExecutor.hpp"
using namespace std;
using namespace advcpp;

namespace smart_house {

EventsExecutor::EventsExecutor(WaitableQueue<Event>& a_eventQueue, IObserversNotifier& a_notifier, ISubscribersFinder& a_finder)
: m_shutDown(false)
, m_eventQueue(a_eventQueue)
, m_notifier(a_notifier)
, m_finder(a_finder)
{
}

void EventsExecutor::SendAllEvents()
{    
    set<IObserver*> observers;
    for(;;) {
        Event event;
        m_eventQueue.Deque(event);
        if(event.IsNotValid()) {
            return;
        }
        
        m_finder.FindControllers(event.m_typeAndLocation, observers);
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

// protected functions:

void EventsExecutor::SendEvents(size_t a_numOfEvents)
{
    set<IObserver*> observers;
    for(size_t i = 0; i < a_numOfEvents; ++i) {
        Event event;
        m_eventQueue.Deque(event);
        
        m_finder.FindControllers(event.m_typeAndLocation, observers);
        m_notifier.NotifyAll(event, observers);
    }
}

void EventsExecutor::SendEventsUntil(Event const& a_endEvent)
{
    set<IObserver*> observers;
    for(;;) {
        Event event;
        m_eventQueue.Deque(event);
        if(event == a_endEvent) {
            return;
        }
        
        m_finder.FindControllers(event.m_typeAndLocation, observers);
        m_notifier.NotifyAll(event, observers);
    }
}

} // smart_house
