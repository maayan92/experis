#include "waitableQueue.hpp"
#include "threadPool.hpp"
#include "threadClasses.hpp"
#include "mu_test.h"
#include <climits>
#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace experis;
using namespace advcpp;
using namespace std;

class Incrementer : public IRunnable {
public:
    Incrementer(size_t& a_count)
    : m_count(a_count)
    {}

    void operator()() {
        ++m_count;
    }

private:
    size_t& m_count;
};

class AtomicIncrementer : public IRunnable {
public:
    AtomicIncrementer(Atomic<size_t>& a_count)
    : m_count(a_count)
    {}

    void operator()() {
        ++m_count;
    }

private:
    Atomic<size_t>& m_count;
};

BEGIN_TEST(test_thread_pool_one_threads_N_tasks)
    ThreadPool threads(1);

    size_t count = 0;
    shared_ptr<Incrementer> newTask(new Incrementer(count));

    size_t N = 10000;
    for(size_t i = 0 ; i < N ; ++i) {
        threads.Submit(newTask);
    }

    threads.ShutDown();

    ASSERT_EQUAL(count, N);
END_TEST

BEGIN_TEST(test_thread_pool_N_threads_M_tasks)
    ThreadPool threads(5);

    Atomic<size_t> count;
    shared_ptr<AtomicIncrementer> newTask(new AtomicIncrementer(count));

    size_t N = 10000;
    for(size_t i = 0 ; i < N ; ++i) {
        threads.Submit(newTask);
    }

    threads.ShutDown();

    ASSERT_EQUAL(count, N);
END_TEST

BEGIN_TEST(test_thread_pool_add_thread_default)
    const size_t NUM_OF_THREAD = 5;
    ThreadPool threads(NUM_OF_THREAD);

    threads.AddThread();

    ASSERT_EQUAL(NUM_OF_THREAD + 1, threads.NumOfThread());
END_TEST

BEGIN_TEST(test_thread_pool_add_N_threads)
    const size_t NUM_OF_THREAD = 5;
    const size_t NUM_OF_THREAD_TO_ADD = 5;

    ThreadPool threads(NUM_OF_THREAD);

    threads.AddThread(NUM_OF_THREAD_TO_ADD);

    ASSERT_EQUAL(NUM_OF_THREAD + NUM_OF_THREAD_TO_ADD, threads.NumOfThread());
END_TEST

BEGIN_TEST(test_thread_pool_submit_task)
    const size_t NUM_OF_THREAD = 5;
    ThreadPool threads(NUM_OF_THREAD);
    ASSERT_EQUAL(0, threads.NumOfTasks());

    size_t count = 0;
    shared_ptr<Incrementer> newTask(new Incrementer(count));
    threads.Submit(newTask);

    ASSERT_EQUAL(1, threads.NumOfTasks());
END_TEST

BEGIN_SUITE(test_thread_pool)
    TEST(test_thread_pool_one_threads_N_tasks)
    TEST(test_thread_pool_N_threads_M_tasks)

    TEST(test_thread_pool_add_thread_default)
    TEST(test_thread_pool_add_N_threads)

    TEST(test_thread_pool_submit_task)
END_SUITE