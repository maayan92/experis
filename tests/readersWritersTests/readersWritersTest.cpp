#include "readersWriters.hpp"
#include "threadPool.hpp"
#include "mu_test.h"
#include <climits>
#include<iomanip>
#include<iostream>
using namespace std;
using namespace advcpp;
using namespace experis;

struct Read : public IRunnable {
    Read(ReadersWriters& a_readersWriters, Atomic<size_t>& a_counter)
    : m_readersWriters(a_readersWriters)
    , m_counter(a_counter)
    {}

    void operator()() {
        m_readersWriters.ReaderLock();
        cout << m_counter << '\n';
        m_readersWriters.ReaderUnLock();
    }

private:
    ReadersWriters& m_readersWriters;
    Atomic<size_t>& m_counter;
};

struct Write : public IRunnable {
    Write(ReadersWriters& a_readersWriters, Atomic<size_t>& a_counter)
    : m_readersWriters(a_readersWriters)
    , m_counter(a_counter)
    {}

    void operator()() {
        m_readersWriters.WriterLock();
        ++m_counter;
        m_readersWriters.WriterUnLock();
    }

private:
    ReadersWriters& m_readersWriters;
    Atomic<size_t>& m_counter;
};

BEGIN_TEST(test_readers_writers_counter)
    ReadersWriters readersWriters;
    ThreadPool threads(2);

    Atomic<size_t> counter;
    shared_ptr<Read> reader(new Read(readersWriters, counter));

    size_t NUM_READER = 10;
    for(size_t i = 0 ; i < NUM_READER ; ++i) {
        threads.Submit(reader);
    }
    
    shared_ptr<Write> writer(new Write(readersWriters, counter));
    size_t NUM_WRITERS = 3;
    for(size_t i = 0 ; i < NUM_WRITERS ; ++i) {
        threads.Submit(writer);
    }

    threads.ShutDown();
    ASSERT_EQUAL(counter, 3);
END_TEST

BEGIN_SUITE(test_readers_writers)
    TEST(test_readers_writers_counter)
END_SUITE
