#include "notifyingTask.hpp"
#include <sstream>
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

NotifyObserver::NotifyObserver(IObserver* a_observer, Notifier& a_notifier)
: m_observer(a_observer)
, m_notifier(a_notifier)
{}

void NotifyObserver::operator()() {
    m_notifier.Notify(m_observer);
}

// Notifier:

Notifier::Notifier(const Event& a_event, Atomic<size_t>& a_count, WaitersConditionVar& a_cv)
: m_event(a_event)
, m_count(a_count)
, m_cv(a_cv)
, m_logFile("notifyFail_log.txt")
{}

void Notifier::Notify(IObserver* a_observer) {
    try {
        a_observer->Notify(m_event);
    } catch(const exception& exc) {
        MutexLocker locker(m_mtx);
        stringstream msg;
        msg << "exeption thrown: " << exc.what() << '\n';
        msg << m_event;
        LOGINFO(m_logFile, msg.str());
    }
    
    if(--m_count == 0) {
        m_cv.NotifyOne();
    }
}

} // smart_house