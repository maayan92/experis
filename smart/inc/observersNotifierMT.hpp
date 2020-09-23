#ifndef OBSERVERS_NOTIFIER_MT_HPP
#define OBSERVERS_NOTIFIER_MT_HPP

#include "iObserversNotifier.hpp"
#include "waitersConditionVar.hpp"
#include "readersWriters.hpp"
#include "threadPool.hpp"

namespace smart_house {

class ObserversNotifierMT : public IObserversNotifier, private experis::Uncopyable {
public:
    explicit ObserversNotifierMT(size_t a_numOfThreads = MAX_NUM_OF_THREADS);
    //~ObserversNotifierMT() = default;

    virtual void NotifyAll(const Event& a_event, std::set<IObserver*>& a_observers);

private:
    static const size_t MAX_NUM_OF_THREADS = 8;

    experis::Mutex m_mtx;
    experis::WaitersConditionVar m_cvDoneNotify;
    advcpp::ThreadPool m_threads;
};

} // smart_house

#endif