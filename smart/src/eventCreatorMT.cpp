#include "eventCreatorMT.hpp"
#include "shared_ptr.hpp"
#include "runnable.hpp"
#include <sstream>
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

struct EventUseElements {

    EventUseElements(WaitableQueue<Event>& a_events, FileLog& a_eventsLog, FileLog& a_createEventFailLog)
    : m_events(a_events)
    , m_eventsLog(a_eventsLog)
    , m_createEventFailLog(a_createEventFailLog)
    {}

    WaitableQueue<Event>& m_events;
    FileLog& m_eventsLog;
    FileLog& m_createEventFailLog;

};

struct SetEvent : public IRunnable {
    SetEvent(const SensorInfo& a_info, IObserver* a_sensor, shared_ptr<EventUseElements> a_eventsUse)
    : m_info(a_info)
    , m_sensor(a_sensor)
    , m_eventsUse(a_eventsUse)
    {}

    void operator()() {
        Event event;
        stringstream msg;

        try {
            m_sensor->CreateEvent(m_info, event);
        } catch(const exception& exc) {
            msg << "exeption thrown: " << exc.what();
            LOGINFO(m_eventsUse->m_createEventFailLog, msg.str());

            return;
        }
       
        msg << event;
        LOGINFO(m_eventsUse->m_eventsLog, msg.str());
        m_eventsUse->m_events.Enque(event);
    }

private:
    SensorInfo m_info;
    IObserver* m_sensor;
    shared_ptr<EventUseElements> m_eventsUse;
};

EventCreatorMT::EventCreatorMT(advcpp::WaitableQueue<Event>& a_events, size_t a_numOfThreads)
: m_events(a_events)
, m_threads((a_numOfThreads > MAX_NUM_OF_THREADS) ? MAX_NUM_OF_THREADS : a_numOfThreads)
, m_eventsLog("events_log.txt")
, m_createEventFailLog("createEventFail_log.txt")
{
}

void EventCreatorMT::CreateEvent(const SensorInfo& a_info, IObserver* a_sensor)
{
    shared_ptr<EventUseElements> send(new EventUseElements(m_events, m_eventsLog, m_createEventFailLog));
    shared_ptr<SetEvent> setEvent(new SetEvent(a_info, a_sensor, send));
    m_threads.Submit(setEvent);
}

} // smart_house