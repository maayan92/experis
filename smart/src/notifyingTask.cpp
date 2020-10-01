#include "notifyingTask.hpp"
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

const size_t FILE_NAME_SIZE = 128; 

static string GetFileName()
{
    char date[FILE_NAME_SIZE];
    time_t currentTime;
    time(&currentTime);

    strftime(date, FILE_NAME_SIZE, "%Fnotify_log.txt", localtime(&currentTime));

    return std::string(date);
}

Notifier::Notifier(const Event& a_event, Atomic<size_t>& a_count, WaitersConditionVar& a_cv)
: m_event(a_event)
, m_count(a_count)
, m_cv(a_cv)
, m_errorsLog(GetFileName().c_str())
{}

Notifier::~Notifier()
{
    m_errorsLog.close();
}

void Notifier::Notify(IObserver* a_observer) {
    try {
        a_observer->Notify(m_event);
    } catch(const exception& exc) {
        MutexLocker locker(m_mtx);
        
        WriteToFile(exc.what());
    }
    
    if(--m_count == 0) {
        m_cv.NotifyOne();
    }
}

void Notifier::WriteToFile(const char* a_what)
{
    m_errorsLog << "exeption: " << a_what;

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

} // smart_house