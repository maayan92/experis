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

template<typename T>
static T FillValues(T a_value, T a_copy)
{
    return  (a_value < 0) ? --a_copy : ++a_copy;
}

BEGIN_TEST(test_two_threads_two_tasks_one_enque_one_deque)
    WaitableQueue<int> waQueue(5);
    const size_t EQ = 6;
    const size_t DQ = 3;

    ThreadPool threads(2);

    vector<int> values(EQ, 1);
    transform(++values.begin(), values.end(), values.begin(), ++values.begin(), FillValues<int>);
    shared_ptr<waitableQueueEnque<int> > enqueTask(new waitableQueueEnque<int>(waQueue, values));
    threads.Submit(enqueTask);

    vector<int> result(DQ);
    shared_ptr<waitableQueueDeque<int> > dequeTask(new waitableQueueDeque<int>(waQueue, result));
    threads.Submit(dequeTask);

    threads.ShutDown();

    ASSERT_EQUAL(EQ - DQ, waQueue.Size());
END_TEST

static void FillTasksEnque(WaitableQueue<int>& a_waQueue, ThreadPool& a_threads, size_t a_numOfEnque, size_t a_size)
{
    vector<vector<int> > values;
    values.reserve(a_numOfEnque);
    
    for(size_t i = 0 ; i < a_numOfEnque ; ++i) {
        values.push_back(vector<int>(a_size, 1));
        typename vector<int>::iterator itr = ++values[i].begin();
        transform(itr, values[i].end(), values[i].begin(), itr, FillValues<int>);
        shared_ptr<waitableQueueEnque<int> > enqueTask(new waitableQueueEnque<int>(a_waQueue, values[i]));
        a_threads.Submit(enqueTask);
    }
}

static void FillTasksDeque(WaitableQueue<int>& a_waQueue, ThreadPool& a_threads, size_t a_numOfDeque, size_t a_size)
{
    vector<vector<int> > result;
    result.reserve(a_numOfDeque);
    
    for(size_t i = 0 ; i < a_numOfDeque ; ++i) {
        result.push_back(vector<int>(a_size));
        shared_ptr<waitableQueueEnque<int> > dequeTask(new waitableQueueEnque<int>(a_waQueue, result[i]));
        a_threads.Submit(dequeTask);
    }
}

BEGIN_TEST(test_N_threads_M_tasks_N_enque_M_deque)
    WaitableQueue<int> waQueue(20);
    const size_t EQ = 6;
    const size_t DQ = 7;
    const size_t NUM_OF_ENQUE = 10;
    const size_t NUM_OF_DEQUE = 5;
    
    ThreadPool threads(10);

    FillTasksEnque(waQueue, threads, NUM_OF_ENQUE, EQ);
    FillTasksDeque(waQueue, threads, NUM_OF_DEQUE, DQ);

    threads.ShutDown();

    ASSERT_EQUAL((EQ * NUM_OF_ENQUE) - (DQ * NUM_OF_DEQUE), waQueue.Size());
END_TEST

BEGIN_SUITE(test_thread_pool)
    TEST(test_two_threads_two_tasks_one_enque_one_deque)
    //TEST(test_N_threads_M_tasks_N_enque_M_deque)
END_SUITE