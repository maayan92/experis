#ifndef EVENTS_EXECUTOR_HPP
#define EVENTS_EXECUTOR_HPP

#include "iObserversNotifier.hpp"
#include "iSubscribersFinder.hpp"
#include "subscriptions.hpp"
#include "waitableQueue.hpp"
#include "threadPool.hpp"
#include "event.hpp"

namespace smart_house {

class EventsExecutor : private experis::Uncopyable {
public:
    EventsExecutor(advcpp::WaitableQueue<Event>& a_eventQueue, IObserversNotifier* a_notifier, ISubscribersFinder* a_finder);
    //~EventsExecutor() = default;

    void SendAllEvents();
    void ShutDown();

private:
    experis::AtomicFlag m_shutDown;
    advcpp::WaitableQueue<Event>& m_eventQueue;
    IObserversNotifier* m_notifier;
    ISubscribersFinder* m_finder;
};

} // smart_house

#endif