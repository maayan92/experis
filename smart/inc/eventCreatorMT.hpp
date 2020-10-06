#ifndef EVENT_CREATOR_MT_HPP
#define EVENT_CREATOR_MT_HPP

#include "iEventCreator.hpp"
#include "waitableQueue.hpp"
#include "threadPool.hpp"
#include "fileLog.hpp"
#include "event.hpp"

namespace smart_house {

class EventCreatorMT : public IEventCreator {
public:
    explicit EventCreatorMT(advcpp::WaitableQueue<Event>& a_events, size_t a_numOfThreads = DEFAULT_NUM_OF_THREADS);
    //~EventCreatorMT() = default;

    virtual void CreateEvent(const SensorInfo& a_info, IObserver* a_sensor);

private:
    static const size_t DEFAULT_NUM_OF_THREADS = 2;
    static const size_t MAX_NUM_OF_THREADS = 8;

    advcpp::WaitableQueue<Event>& m_events;
    experis::FileLog m_eventsLog;
    experis::FileLog m_createEventFailLog;
    advcpp::ThreadPool m_threads;
};

} // smart_house

#endif