#include "eventCreatorMT.hpp"
#include "shared_ptr.hpp"
#include "runnable.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

struct SetEvent : public IRunnable {
    SetEvent(const SensorInfo& a_info, IObserver* a_sensor, WaitableQueue<Event>& a_events)
    : m_info(a_info)
    , m_sensor(a_sensor)
    , m_events(a_events)
    {}

    void operator()() {
        Event event;
        m_sensor->CreateEvent(m_info, event);
        m_events.Enque(event);
    }

private:
    SensorInfo m_info;
    IObserver* m_sensor;
    WaitableQueue<Event>& m_events;
};

EventCreatorMT::EventCreatorMT(advcpp::WaitableQueue<Event>& a_events, size_t a_numOfThreads)
: m_events(a_events)
, m_threads((a_numOfThreads > MAX_NUM_OF_THREADS) ? MAX_NUM_OF_THREADS : a_numOfThreads)
{
}

void EventCreatorMT::CreateEvent(const SensorInfo& a_info, IObserver* a_sensor)
{
    shared_ptr<SetEvent> setEvent(new SetEvent(a_info, a_sensor, m_events));
    m_threads.Submit(setEvent);
}

} // smart_house