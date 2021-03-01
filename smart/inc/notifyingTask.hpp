#ifndef NOTIFYING_TASK_HPP
#define NOTIFYING_TASK_HPP

#include <fstream>
#include "waitersConditionVar.hpp"
#include "iObserver.hpp"
#include "runnable.hpp"
#include "event.hpp"
#include "fileLog.hpp"

namespace smart_house {

struct Notifier {
    Notifier(const Event& a_event, experis::Atomic<size_t>& a_count, experis::WaitersConditionVar& a_cv);
    //~Notifier() = default;

    void Notify(IObserver* a_observer);

private:
    experis::Mutex m_mtx;
    Event m_event;
    experis::Atomic<size_t>& m_count;
    experis::WaitersConditionVar& m_cv;
    experis::FileLog& m_log;
    std::ofstream m_logFile;
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