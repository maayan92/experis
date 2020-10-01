#include "observersNotifierMT.hpp"
#include "notifyingTask.hpp"
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

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
