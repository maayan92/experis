#include "eventCreatorMT.hpp"
#include "shared_ptr.hpp"
#include "runnable.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

struct SetEvent : public IRunnable {
    SetEvent(const string& a_data, ISensorAgent* a_sensor, WaitableQueue<Event>& a_events)
    : m_data(a_data)
    , m_sensor(a_sensor)
    , m_events(a_events)
    {}

    void operator()() {
        Event event;
        m_sensor->CreateEvent(m_data, event);
        m_events.Enque(event);
    }

private:
    string m_data;
    ISensorAgent* m_sensor;
    WaitableQueue<Event>& m_events;
};

EventCreatorMT::EventCreatorMT(advcpp::WaitableQueue<Event>& a_events, size_t a_numOfThreads)
: m_events(a_events)
, m_threads((a_numOfThreads > MAX_NUM_OF_THREADS) ? MAX_NUM_OF_THREADS : a_numOfThreads)
{
}

void EventCreatorMT::CreateEvent(const string& a_data, ISensorAgent* a_sensor)
{
    shared_ptr<SetEvent> setEvent(new SetEvent(a_data, a_sensor, m_events));
    m_threads.Submit(setEvent);
}

} // smart_house