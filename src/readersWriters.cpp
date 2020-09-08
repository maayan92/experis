#include "readersWriters.hpp"
#include "mutexLocker.hpp"
#include "additionalStructures.hpp"
using namespace experis;
using namespace advcpp;

void ReadersWriters::ReaderLock()
{
    {
        MutexLocker locker(m_mtxReader);
        m_cvReaders.Wait(locker, ObjectFuncExecutor<ReadersWriters, &ReadersWriters::threreAreWriters>(*this));
    }

    ++m_countReaders;
}

void ReadersWriters::ReaderUnLock()
{
    --m_countReaders;

    if(!threreAreReaders()) {
        m_cvWriters.NotifyAll();
    }
}

void ReadersWriters::WriterLock()
{
    ++m_countWriters;
    m_mtxWriter.Lock();
    m_cvWriters.Wait(m_mtxWriter, ObjectFuncExecutor<ReadersWriters, &ReadersWriters::threreAreReaders>(*this));
}

void ReadersWriters::WriterUnLock()
{
    --m_countWriters;
    if(!threreAreWriters()) {
        m_cvReaders.NotifyAll();
    }

    m_mtxWriter.Unlock();
}

bool ReadersWriters::threreAreReaders() const
{
    return m_countReaders > 0;
}

bool ReadersWriters::threreAreWriters() const
{
    return m_countWriters > 0;
}