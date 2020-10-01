#ifndef NOTIFYING_TASK_HPP
#define NOTIFYING_TASK_HPP

#include <fstream>
#include "waitersConditionVar.hpp"
#include "iObserver.hpp"
#include "runnable.hpp"
#include "event.hpp"

namespace smart_house {

struct Notifier {
    Notifier(const Event& a_event, experis::Atomic<size_t>& a_count, experis::WaitersConditionVar& a_cv);
    ~Notifier();

    void Notify(IObserver* a_observer);

private:
    void WriteToFile(const char* a_what);

private:
    experis::Mutex m_mtx;
    Event m_event;
    experis::Atomic<size_t>& m_count;
    experis::WaitersConditionVar& m_cv;
    std::ofstream m_errorsLog;
};

struct NotifyObserver : public experis::IRunnable {
    NotifyObserver(IObserver* a_observer, Notifier& a_notifier);
    //~NotifyObserver() = default;

    void operator()();

private:
    IObserver* m_observer;
    Notifier& m_notifier;
};

} // smart_house

#endif