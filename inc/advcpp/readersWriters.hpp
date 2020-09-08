#ifndef READERS_WRITERS_HPP
#define READERS_WRITERS_HPP

#include "mutex.hpp"
#include "atomic.hpp"
#include "waitersConditionVar.hpp"
#include "uncopyable.hpp"

namespace advcpp {

class ReadersWriters : private experis::Uncopyable {
public:
    //ReadersWriters() = default;
    //~ReadersWriters() = default;

    void ReaderLock();
    void ReaderUnLock();

    void WriterLock();
    void WriterUnLock();

private:
    bool threreAreReaders() const;
    bool threreAreWriters() const;

private:
    experis::Mutex m_mtxReader;
    experis::Atomic<size_t> m_countReaders;
    experis::WaitersConditionVar m_cvReaders;

    experis::Mutex m_mtxWriter;
    experis::Atomic<size_t> m_countWriters;
    experis::WaitersConditionVar m_cvWriters;
};

} // advcpp

#endif