#include "readersWriters.hpp"
#include "threadPool.hpp"
#include "mu_test.h"
#include <climits>
#include<iomanip>
#include<iostream>
#include <unistd.h>
using namespace std;
using namespace advcpp;
using namespace experis;

struct Read : public IRunnable {
    Read(ReadersWriters& a_readersWriters, size_t& a_numOfWriters, Atomic<size_t>& a_numOfReaders)
    : m_readersWriters(a_readersWriters)
    , m_numOfReaders(a_numOfReaders)
    , m_numOfWriters(a_numOfWriters)
    , m_result(true)
    {}

    void operator()() {
        m_readersWriters.ReaderLock();
        ++m_numOfReaders;
  
        for(size_t i = 0 ; i < 10 ; ++i) {
            m_result &= (0 == m_numOfWriters);
        }
  
        --m_numOfReaders;
        m_readersWriters.ReaderUnLock();
    }

    bool GetResult() const { return m_result; }

private:
    ReadersWriters& m_readersWriters;
    Atomic<size_t>& m_numOfReaders;
    size_t& m_numOfWriters;
    bool m_result;
};

struct Write : public IRunnable {
    Write(ReadersWriters& a_readersWriters, size_t& a_numOfWriters, Atomic<size_t>& a_numOfReaders)
    : m_readersWriters(a_readersWriters)
    , m_numOfReaders(a_numOfReaders)
    , m_numOfWriters(a_numOfWriters)
    , m_result(true)
    {}

    void operator()() {
        m_readersWriters.WriterLock();
        ++m_numOfWriters;

        for(size_t i = 0 ; i < 10 ; ++i) {
            m_result &= (0 == m_numOfReaders);
            m_result &= (1 == m_numOfWriters);
        }

        --m_numOfWriters;
        m_readersWriters.WriterUnLock();
    }

    bool GetResult() const { return m_result; }

private:
    ReadersWriters& m_readersWriters;
    Atomic<size_t>& m_numOfReaders;
    size_t& m_numOfWriters;
    bool m_result;
};

// **** tests: **** //

BEGIN_TEST(test_readers_writers_check_num_of_readers_writers)
    ReadersWriters readersWriters;
    ThreadPool threads(0);
    size_t NUM_READER = 500;
    size_t NUM_WRITERS = 5;

    Atomic<size_t> numOfReaders;
    size_t numOfWriters = 0;
    shared_ptr<Read> reader(new Read(readersWriters, numOfWriters, numOfReaders));
    shared_ptr<Write> writer(new Write(readersWriters, numOfWriters, numOfReaders));

    for(size_t i = 0 ; i < NUM_WRITERS ; ++i) {
        for(size_t i = 0 ; i < NUM_READER ; ++i) {
            threads.Submit(reader);
        }
        threads.Submit(writer);
    }

    threads.AddThread(10);
    threads.ShutDown();
    ASSERT_THAT(reader->GetResult());
    ASSERT_THAT(writer->GetResult());
    ASSERT_EQUAL(numOfReaders, 0);
    ASSERT_EQUAL(numOfWriters, 0);
END_TEST

BEGIN_SUITE(test_readers_writers)
    TEST(test_readers_writers_check_num_of_readers_writers)
END_SUITE
