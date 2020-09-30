#include "observersNotifierMT.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

struct Notifier {
    Notifier(const Event& a_event, Atomic<size_t>& a_count, WaitersConditionVar& a_cv)
    : m_event(a_event)
    , m_count(a_count)
    , m_cv(a_cv)
    {}

    void Notify(IObserver* a_observer) {
        //TODO: exception safety
        a_observer->Notify(m_event);
        
        if(--m_count == 0) {
            m_cv.NotifyOne();
        }
    }

private:
    Event m_event;
    Atomic<size_t>& m_count;
    WaitersConditionVar& m_cv;
};

struct NotifyObserver : public IRunnable {
    NotifyObserver(IObserver* a_observer, Notifier& a_notifier)
    : m_observer(a_observer)
    , m_notifier(a_notifier)
    {}

    void operator()() {
        m_notifier.Notify(m_observer);
    }

private:
    IObserver* m_observer;
    Notifier& m_notifier;
};

struct CheckIfEndToNotify {
    CheckIfEndToNotify(Atomic<size_t>& a_count)
    : m_count(a_count)
    {}

    bool operator()() {
        return (0 < m_count);
    }

private:
    Atomic<size_t>& m_count;
};

ObserversNotifierMT::ObserversNotifierMT(size_t a_numOfThreads)
: m_mtx()
, m_cvDoneNotify()
, m_threads((a_numOfThreads > MAX_NUM_OF_THREADS) ? MAX_NUM_OF_THREADS : a_numOfThreads)
{
}

void ObserversNotifierMT::NotifyAll(const Event& a_event, set<IObserver*>& a_observers)
{
    Atomic<size_t> count(a_observers.size());

    Notifier notifier(a_event, count, m_cvDoneNotify);

    set<IObserver*>::iterator itr = a_observers.begin();
    set<IObserver*>::iterator end = a_observers.end();
    for(; itr != end; ++itr) {
        shared_ptr<NotifyObserver> notifyTask(new NotifyObserver(*itr, notifier));
        m_threads.Submit(notifyTask);
    }
    
    MutexLocker locker(m_mtx);
    m_cvDoneNotify.Wait(locker, CheckIfEndToNotify(count));
}

} // smart_house
