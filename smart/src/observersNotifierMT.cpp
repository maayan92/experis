#include "observersNotifierMT.hpp"
#include <fstream>
using namespace std;
using namespace advcpp;
using namespace experis;

namespace smart_house {

const size_t FILE_NAME_SIZE = 128; 

static string GetFileName()
{
    char date[FILE_NAME_SIZE];
    time_t currentTime;
    time(&currentTime);

    strftime(date, FILE_NAME_SIZE, "%Fnotify_log.txt", localtime(&currentTime));

    return string(date);
}

struct Notifier {
    Notifier(const Event& a_event, Atomic<size_t>& a_count, WaitersConditionVar& a_cv)
    : m_event(a_event)
    , m_count(a_count)
    , m_cv(a_cv)
    , m_fileName(GetFileName())
    , m_errorsLog(m_fileName.c_str())
    {}

    ~Notifier()
    {
        m_errorsLog.close();
    }

    void Notify(IObserver* a_observer) {
        try {
            a_observer->Notify(m_event);
        } catch(const exception& exc) {
            MutexLocker locker(m_mtx);

            m_errorsLog << "exeption: " << exc.what();

            m_errorsLog << "\nevent: ";
            m_errorsLog << "\ntime - " << m_event.m_timestamp->tm_hour << ":" << m_event.m_timestamp->tm_min;
            m_errorsLog << "\ntype - " << m_event.m_typeAndLocation.m_type;
            m_errorsLog << "\nlocation - floor - " << m_event.m_typeAndLocation.m_location.m_floor;
            m_errorsLog << "| room - " << m_event.m_typeAndLocation.m_location.m_room;
            m_errorsLog << "\ndata - ";
            m_event.m_data->Print(m_errorsLog);

            m_errorsLog << "\n\n";

            m_errorsLog.flush();
        }
        
        if(--m_count == 0) {
            m_cv.NotifyOne();
        }
    }

private:
    Mutex m_mtx;
    Event m_event;
    Atomic<size_t>& m_count;
    WaitersConditionVar& m_cv;
    string m_fileName;
    ofstream m_errorsLog;
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
