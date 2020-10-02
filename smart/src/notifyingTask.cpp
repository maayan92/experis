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
, m_logFile(GetFileName().c_str())
{}

void Notifier::Notify(IObserver* a_observer) {
    try {
        a_observer->Notify(m_event);
    } catch(const exception& exc) {
        MutexLocker locker(m_mtx);
        stringstream msg;
        CompressNotifyFailToMsg(exc.what(), msg);
        LOGINFO(m_logFile, msg.str());
    }
    
    if(--m_count == 0) {
        m_cv.NotifyOne();
    }
}

void Notifier::CompressNotifyFailToMsg(const char* a_what, stringstream& a_msg)
{
    a_msg << "\nexeption thrown: " << a_what;

    a_msg << "\nevent: ";
    a_msg << " time - " << m_event.m_timestamp->tm_hour << ":" << m_event.m_timestamp->tm_min;
    a_msg << " | type - " << m_event.m_typeAndLocation.m_type;
    a_msg << " | location - floor - " << m_event.m_typeAndLocation.m_location.m_floor;
    a_msg << " , room - " << m_event.m_typeAndLocation.m_location.m_room;
    a_msg << " | data - ";
    m_event.m_data->Print(a_msg);
}

} // smart_house