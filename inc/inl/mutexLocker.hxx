
namespace experis {

inline MutexLocker::MutexLocker(Mutex &a_mutex)
: m_mutexLocker(a_mutex) {
    a_mutex.Lock();
}

inline MutexLocker::~MutexLocker() {
    m_mutexLocker.Unlock();
}

inline void MutexLocker::Lock() {
    m_mutexLocker.Lock();
}

inline void MutexLocker::Unlock() {
    m_mutexLocker.Unlock();
}

inline Mutex& MutexLocker::GetMutex() {
    return m_mutexLocker;
}

} // experis
