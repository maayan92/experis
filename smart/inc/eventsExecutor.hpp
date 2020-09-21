#ifndef EVENTS_EXECUTOR_HPP
#define EVENTS_EXECUTOR_HPP

#include "iObserversNotifier.hpp"
#include "waitableQueue.hpp"
#include "threadPool.hpp"
#include "event.hpp"

namespace smart_house {

class EventsExecutor {
public:
    EventsExecutor(advcpp::WaitableQueue<Event>& a_eventQueue, IObserversNotifier* a_notifier);
    //~EventsExecutor() = default;

    void SendAllEvents(Subscriptions& a_subscriptions);

private:
    advcpp::WaitableQueue<Event>& m_eventQueue;
    IObserversNotifier* m_notifier;
};

} // smart_house

#endif