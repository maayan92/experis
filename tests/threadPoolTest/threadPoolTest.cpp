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

BEGIN_TEST(test_thread_pool_one_threads_N_tasks)
    ThreadPool threads(1);

    size_t count = 0;
    shared_ptr<Incrementer > newTask(new Incrementer(count));

    size_t N = 10000;
    for(size_t i = 0 ; i < N ; ++i) {
        threads.Submit(newTask);
    }

    threads.ShutDown();

    ASSERT_EQUAL(count, N);
END_TEST

BEGIN_TEST(test_N_threads_M_tasks_N_enque_M_deque)
    ThreadPool threads(10);

    threads.ShutDown();

    //ASSERT_EQUAL();
END_TEST

BEGIN_SUITE(test_thread_pool)
    TEST(test_thread_pool_one_threads_N_tasks)
    //TEST(test_N_threads_M_tasks_N_enque_M_deque)
END_SUITE