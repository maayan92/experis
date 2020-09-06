#include "threadGroup.hpp"
#include "testClasses.hpp"
#include "threadClasses.hpp"
#include "mu_test.h"
#include <climits>
#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace advcpp;
using namespace experis;
using namespace std;

template<typename T>
static T FillValues(T a_value, T a_copy)
{
    return  (a_value < 0) ? --a_copy : ++a_copy;
}

template<typename T>
static bool CompareValues(vector<T>& a_left, vector<T>& a_right)
{
    if(a_left.front() == a_right.front()) {
        a_left.erase(a_left.begin());
        a_right.erase(a_right.begin());
        return true;
    }

    return false;
}

template<typename T>
static bool CheckResult(vector<vector<T> >& a_result, vector<vector<T> >& a_values, size_t a_size)
{
    typedef typename vector<vector<T> >::iterator iterator;
    iterator itrFind;
    iterator itrValBegin = a_values.begin();
    iterator itrValEnd = a_values.end();
    iterator itrResultBegin = a_result.begin();
    iterator itrResultEnd = a_result.end();

    for(size_t i = 0 ; i < a_size ; ++i) {
        itrFind = find_first_of(itrResultBegin, itrResultEnd, itrValBegin, itrValEnd, CompareValues<T>);
        if(itrFind == itrResultEnd) {
            return false;
        }
    }
    return true;
}

template<typename T, typename Action>
static void EnqueThreads(ThreadGroup<T, Action>& a_threads, vector<vector<T> >& a_values, size_t a_size)
{
    for(size_t i = 0 ; i < a_values.size() ; ++i) {
        size_t startValue = ((i % 2 == 0) ? 1 : -1) * (a_size * (i/2) + 1);
        a_values[i] = vector<T>(a_size, startValue);

        typename vector<T>::iterator itr = ++a_values[i].begin();
        transform(itr, a_values[i].end(), a_values[i].begin(), itr, FillValues<T>);
        a_threads.CreateNewThread(a_values[i]);
    }
}

template<typename T, typename Action>
static void DequeThreads(ThreadGroup<T, Action>& a_threads, vector<vector<T> >& a_result, size_t a_size)
{
    for(size_t i = 0 ; i < a_result.size() ; ++i) {
        a_result[i] = vector<T>(a_size);
        a_threads.CreateNewThread(a_result[i]);
    }
}

// **** tests **** //

BEGIN_TEST(test_waitable_queue_enque_one)
    WaitableQueue<int> waQueue(5);
    ASSERT_THAT(waQueue.Empty());

    waQueue.Enque(1);
    ASSERT_THAT(!waQueue.Empty());
END_TEST

BEGIN_TEST(test_waitable_queue_deque_one)
    WaitableQueue<int> waQueue(5);
    waQueue.Enque(4);
    waQueue.Enque(8);
    int value;
    waQueue.Deque(value);
    ASSERT_EQUAL(1, waQueue.Size());
    ASSERT_EQUAL(4, value);
END_TEST

BEGIN_TEST(test_waitable_queue_check_fifo)
    WaitableQueue<Pow> waQueue(5);
    for(int i = 0 ; i < 5 ; ++i) {
        waQueue.Enque(Pow(i + 1));
    }
    
    for(size_t i = 0 ; i < 5 ; ++i) {
        Pow value;
        waQueue.Deque(value);
        
        ASSERT_EQUAL(value.GetValue(), pow(i + 1, 2));
    }
    ASSERT_THAT(waQueue.Empty());
END_TEST

BEGIN_TEST(test_multi_threads_one_enque_one_deque)
    WaitableQueue<int> waQueue(5);
    const size_t EQ = 6;
    const size_t DQ = 3;

    vector<vector<int> > values(1);
    ThreadGroup<int, waitableQueueEnque<int> > threadsEnque(waQueue);
    EnqueThreads(threadsEnque, values, EQ);

    vector<vector<int> > result(1);
    ThreadGroup<int, waitableQueueDeque<int> > threadsDeque(waQueue);
    DequeThreads(threadsDeque, result, DQ);

    threadsEnque.JoinAll();
    threadsDeque.JoinAll();

    ASSERT_EQUAL(EQ - DQ, waQueue.Size());
    ASSERT_THAT(CheckResult(result, values, EQ - DQ));
END_TEST

BEGIN_TEST(test_multi_threads_two_enque_one_deque)
    WaitableQueue<int> waQueue(10000);
    const size_t EQ = 8000;
    const size_t DQ = 10000;

    vector<vector<int> > values(2);
    ThreadGroup<int, waitableQueueEnque<int> > threadsEnque(waQueue);
    EnqueThreads(threadsEnque, values, EQ);
    
    vector<vector<int> > result(1);
    ThreadGroup<int, waitableQueueDeque<int> > threadsDeque(waQueue);
    DequeThreads(threadsDeque, result, DQ);

    threadsEnque.JoinAll();
    threadsDeque.JoinAll();

    ASSERT_EQUAL((EQ * 2) - DQ, waQueue.Size());
    ASSERT_THAT(CheckResult(result, values, (EQ * 2) - DQ));
END_TEST

BEGIN_TEST(test_multi_threads_one_enque_two_deque)
    WaitableQueue<int> waQueue(5);
    const size_t EQ = 5;
    const size_t DQ = 2;

    vector<vector<int> > values(1);
    ThreadGroup<int, waitableQueueEnque<int> > threadsEnque(waQueue);
    EnqueThreads(threadsEnque, values, EQ);
    
    vector<vector<int> > result(2);
    ThreadGroup<int, waitableQueueDeque<int> > threadsDeque(waQueue);
    DequeThreads(threadsDeque, result, DQ);

    threadsEnque.JoinAll();
    threadsDeque.JoinAll();

    ASSERT_EQUAL(EQ - (DQ * 2), waQueue.Size());
    ASSERT_THAT(CheckResult(result, values, EQ - (DQ * 2)));
END_TEST

BEGIN_TEST(test_multi_threads_N_enque_M_deque)
    WaitableQueue<int> waQueue(1000);
    const size_t EQ = 1000;
    const size_t DQ = 1000;

    vector<vector<int> > values(4);
    ThreadGroup<int, waitableQueueEnque<int> > threadsEnque(waQueue);
    EnqueThreads(threadsEnque, values, EQ);
    
    vector<vector<int> > result(3);
    ThreadGroup<int, waitableQueueDeque<int> > threadsDeque(waQueue);
    DequeThreads(threadsDeque, result, DQ);

    threadsEnque.JoinAll();
    threadsDeque.JoinAll();

    ASSERT_EQUAL((EQ * 4) - (DQ * 3), waQueue.Size());
    ASSERT_THAT((CheckResult(result, values, (EQ * 4) - (DQ * 3))));
END_TEST

BEGIN_TEST(test_multi_threads_default_CTOR)
    WaitableQueue<int> waQueue;
    const size_t EQ = 3000000;
    const size_t DQ = 2000000;

    vector<vector<int> > values(4);
    ThreadGroup<int, waitableQueueEnque<int> > threadsEnque(waQueue);
    EnqueThreads(threadsEnque, values, EQ);
    
    vector<vector<int> > result(1);
    ThreadGroup<int, waitableQueueDeque<int> > threadsDeque(waQueue);
    DequeThreads(threadsDeque, result, DQ);

    threadsEnque.JoinAll();
    threadsDeque.JoinAll();

    ASSERT_EQUAL((EQ * 4) - DQ, waQueue.Size());
END_TEST

template<typename T>
struct ShutDown {
    ShutDown(WaitableQueue<T>& a_waQueue)
    : m_waQueue(a_waQueue)
    {}
    
    void operator()() {
        m_waQueue.ShutDown();
    }

private:
    WaitableQueue<T>& m_waQueue;
};

BEGIN_TEST(test_multi_threads_one_enque_one_deque_shut_down)
    size_t capacity = 5;
    WaitableQueue<int> waQueue(capacity);
    const size_t EQ = 10;
    const size_t DQ = 3;

    vector<vector<int> > values(1);
    ThreadGroup<int, waitableQueueEnque<int> > threadsEnque(waQueue);
    EnqueThreads(threadsEnque, values, EQ);

    vector<vector<int> > result(1);
    ThreadGroup<int, waitableQueueDeque<int> > threadsDeque(waQueue);
    DequeThreads(threadsDeque, result, DQ);

    shared_ptr<ShutDown<int> > shrPtr(new ShutDown<int>(waQueue));
    Thread<ShutDown<int> > threadShutDown(shrPtr);

    threadShutDown.Yeild();
    threadsEnque.JoinAll();
    threadsDeque.JoinAll();
    //waQueue.ShutDown();
    threadShutDown.Join();

    size_t sizeResult = ((EQ - DQ) > capacity) ? capacity : 0;
    ASSERT_EQUAL(sizeResult, waQueue.Size());
    ASSERT_THAT(CheckResult(result, values, DQ));
END_TEST

BEGIN_TEST(test_waitable_queue_size)
    WaitableQueue<int> waQueue(5);
    ASSERT_EQUAL(waQueue.Size(), 0);

    waQueue.Enque(1);
    ASSERT_EQUAL(waQueue.Size(), 1);

    int val;
    waQueue.Deque(val);
    ASSERT_EQUAL(waQueue.Size(), 0);
END_TEST

BEGIN_TEST(test_waitable_queue_empty)
    WaitableQueue<int> waQueue(5);
    ASSERT_THAT(waQueue.Empty());
END_TEST

BEGIN_TEST(test_waitable_queue_not_empty)
    WaitableQueue<int> waQueue(5);
    waQueue.Enque(1);
    ASSERT_THAT(!waQueue.Empty());
END_TEST

BEGIN_SUITE(test_waitable_queue)
    TEST(test_waitable_queue_enque_one)
    TEST(test_waitable_queue_deque_one)

    TEST(test_waitable_queue_check_fifo)

    TEST(test_multi_threads_one_enque_one_deque)
    TEST(test_multi_threads_two_enque_one_deque)
    TEST(test_multi_threads_one_enque_two_deque)
    TEST(test_multi_threads_N_enque_M_deque)
    //TEST(test_multi_threads_default_CTOR)
    TEST(test_multi_threads_one_enque_one_deque_shut_down)
    
    TEST(test_waitable_queue_size)

    TEST(test_waitable_queue_empty)
    TEST(test_waitable_queue_not_empty)
END_SUITE