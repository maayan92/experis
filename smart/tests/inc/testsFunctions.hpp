#ifndef TESTS_FUNCTIONS_HPP
#define TESTS_FUNCTIONS_HPP

#include <vector>
#include <unistd.h>
#include "event.hpp"
#include "controllerTest.hpp"
#include "payloadSmoke.hpp"
#include "eventsExecutor.hpp"

smart_house::Event CreateEvent(const smart_house::EventTypeLoc& a_typeLoc)
{
    time_t t;
    time(&t);
    advcpp::shared_ptr<smart_house::PayloadSmoke> ps(new smart_house::PayloadSmoke());
    smart_house::Event event = {localtime(&t), ps, a_typeLoc};
    return event;
}

template<size_t SIZE>
bool CheckResult(const smart_house::EventTypeLoc& a_typeLoc, smart_house::ControllerTest* a_controllers)
{
    for(size_t i = 0; i < SIZE; ++i) {
        if(!(a_typeLoc == a_controllers[i].GetEventTypeLocation())) {
            return false;
        }
    }

    return true;
}

template<size_t SIZE>
bool CheckResult(const smart_house::EventTypeLoc& a_typeLoc, const std::vector<smart_house::ControllerTest*>& a_controllers)
{
    for(size_t i = 0; i < SIZE; ++i) {
        if(!(a_typeLoc == a_controllers[i]->GetEventTypeLocation())) {
            return false;
        }
    }

    return true;
}

struct ShutDownTask : public experis::IRunnable {
    ShutDownTask(smart_house::EventsExecutor& a_executor, size_t a_time)
    : m_executor(a_executor)
    , m_time(a_time)
    {}

    virtual void operator()() {
        sleep(m_time);
        m_executor.ShutDown();
    }

private:
    smart_house::EventsExecutor& m_executor;
    size_t m_time;
};

struct EventEnque : public experis::IRunnable {
    EventEnque(advcpp::WaitableQueue<smart_house::Event>& a_events, std::vector<smart_house::EventTypeLoc>& a_typeLoc)
    : m_events(a_events)
    , m_typeLoc(a_typeLoc)
    {}

    virtual void operator()() {
        sleep(1);
        for(size_t i = 0; i < m_typeLoc.size(); ++i) {
            m_events.Enque(CreateEvent(m_typeLoc[i]));
        }
    }

private:
    advcpp::WaitableQueue<smart_house::Event>& m_events;
    std::vector<smart_house::EventTypeLoc>& m_typeLoc;
};

#endif