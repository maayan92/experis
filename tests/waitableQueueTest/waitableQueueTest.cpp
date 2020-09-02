#include "waitableQueue.hpp"
#include "thread.hpp"
#include "testClasses.hpp"
#include "mu_test.h"
#include <climits>
#include<iostream>
#include<iomanip>
using namespace advcpp;
using namespace experis;

template<typename T>
class waitableQueueEnque {
public:
    waitableQueueEnque(WaitableQueue<T>& a_waQueue, size_t a_size)
    : m_waQueue(a_waQueue)
    , m_size(a_size)
    , m_value()
    {}

    void operator()() {
        for(size_t i = 0 ; i < m_size ; ++i) {
            m_waQueue.Enque(++m_value);
        }
    }

private:
    WaitableQueue<T>& m_waQueue;
    size_t m_size;
    Atomic<T> m_value;
};

template<typename T>
class waitableQueueDeque {
public:
    waitableQueueDeque(WaitableQueue<T>& a_waQueue, size_t a_size)
    : m_waQueue(a_waQueue)
    , m_size(a_size)
    , m_value()
    , m_result(true)
    {}
    
    void operator()() {
        for(size_t i = 0 ; i < m_size ; ++i) {
            T val;
            m_waQueue.Deque(val);
            m_result &= (++m_value == val);
        }
    }

    bool IsAllGood() const { return m_result; }

private:
    WaitableQueue<T>& m_waQueue;
    size_t m_size;
    Atomic<T> m_value;
    bool m_result;
};

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
    const size_t DQ = 1;

    shared_ptr<waitableQueueEnque<int> > shrPtrEnque(new waitableQueueEnque<int>(waQueue, 6));
    Thread<waitableQueueEnque<int> > threadEnque(shrPtrEnque);

    shared_ptr<waitableQueueDeque<int> > shrPtrDeque(new waitableQueueDeque<int>(waQueue, 1));
    Thread<waitableQueueDeque<int> > threadDeque(shrPtrDeque);

    threadEnque.Join();
    threadDeque.Join();
    ASSERT_EQUAL(EQ - DQ, waQueue.Size());
    ASSERT_THAT(shrPtrDeque->IsAllGood());
END_TEST

BEGIN_TEST(test_multi_threads_two_enque_one_deque)
    WaitableQueue<int> waQueue(5);
    const size_t EQ = 5;
    const size_t DQ = 6;

    shared_ptr<waitableQueueEnque<int> > shrPtrEnque(new waitableQueueEnque<int>(waQueue, 5));
    Thread<waitableQueueEnque<int> > threadEnqueFirst(shrPtrEnque);
    Thread<waitableQueueEnque<int> > threadEnqueSecond(shrPtrEnque);

    shared_ptr<waitableQueueDeque<int> > shrPtrDeque(new waitableQueueDeque<int>(waQueue, 6));
    Thread<waitableQueueDeque<int> > threadDeque(shrPtrDeque);

    threadEnqueFirst.Join();
    threadEnqueSecond.Join();
    threadDeque.Join();
    ASSERT_EQUAL((EQ * 2) - DQ, waQueue.Size());
    ASSERT_THAT(shrPtrDeque->IsAllGood());
END_TEST

BEGIN_TEST(test_multi_threads_one_enque_two_deque)
    WaitableQueue<int> waQueue(5);
    const size_t EQ = 5;
    const size_t DQ = 2;

    shared_ptr<waitableQueueDeque<int> > shrPtrDeque(new waitableQueueDeque<int>(waQueue, DQ));
    Thread<waitableQueueDeque<int> > threadDequeFirst(shrPtrDeque);
    Thread<waitableQueueDeque<int> > threadDequeSecond(shrPtrDeque);
    
    shared_ptr<waitableQueueEnque<int> > shrPtrEnque(new waitableQueueEnque<int>(waQueue, EQ));
    Thread<waitableQueueEnque<int> > threadEnque(shrPtrEnque);

    threadDequeFirst.Join();
    threadDequeSecond.Join();
    threadEnque.Join();
    ASSERT_EQUAL(EQ - (DQ * 2), waQueue.Size());
END_TEST

BEGIN_TEST(test_multi_threads_N_enque_M_deque)
    WaitableQueue<int> waQueue(1000);
    const size_t EQ = 1000;
    const size_t DQ = 1000;

    shared_ptr<waitableQueueEnque<int> > shrPtrEnque(new waitableQueueEnque<int>(waQueue, 1000));
    Thread<waitableQueueEnque<int> > threadEnqueFirst(shrPtrEnque);
    Thread<waitableQueueEnque<int> > threadEnqueSecond(shrPtrEnque);
    Thread<waitableQueueEnque<int> > threadEnqueThird(shrPtrEnque);
    Thread<waitableQueueEnque<int> > threadEnqueFourth(shrPtrEnque);
    
    shared_ptr<waitableQueueDeque<int> > shrPtrDeque(new waitableQueueDeque<int>(waQueue, 1000));
    Thread<waitableQueueDeque<int> > threadDequeFirst(shrPtrDeque);
    Thread<waitableQueueDeque<int> > threadDequeSecond(shrPtrDeque);
    Thread<waitableQueueDeque<int> > threadDequeThird(shrPtrDeque);

    threadEnqueFirst.Join();
    threadEnqueSecond.Join();
    threadEnqueThird.Join();
    threadEnqueFourth.Join();

    threadDequeFirst.Join();
    threadDequeSecond.Join();
    threadDequeThird.Join();

    ASSERT_EQUAL((EQ * 4) - (DQ * 3), waQueue.Size());
END_TEST

BEGIN_TEST(test_multi_threads_default_CTOR)
    WaitableQueue<int> waQueue;
    const size_t EQ = 5000000;
    const size_t DQ = 500;

    shared_ptr<waitableQueueEnque<int> > shrPtrEnque(new waitableQueueEnque<int>(waQueue, EQ));
    Thread<waitableQueueEnque<int> > threadEnqueFirst(shrPtrEnque);
    Thread<waitableQueueEnque<int> > threadEnqueSecond(shrPtrEnque);

    shared_ptr<waitableQueueDeque<int> > shrPtrDeque(new waitableQueueDeque<int>(waQueue, DQ));
    Thread<waitableQueueDeque<int> > threadDeque(shrPtrDeque);

    threadEnqueFirst.Join();
    threadEnqueSecond.Join();
    threadDeque.Join();
    ASSERT_EQUAL((EQ * 2) - DQ, waQueue.Size());
    ASSERT_THAT(shrPtrDeque->IsAllGood());
END_TEST

BEGIN_TEST(test_multi_threads_size)
    WaitableQueue<int> waQueue(5);
    const size_t EQ = 10;
    const size_t DQ = 8;

    shared_ptr<waitableQueueEnque<int> > shrPtrEnque(new waitableQueueEnque<int>(waQueue, EQ));
    Thread<waitableQueueEnque<int> > threadEnque(shrPtrEnque);

    shared_ptr<waitableQueueDeque<int> > shrPtrDeque(new waitableQueueDeque<int>(waQueue, DQ));
    Thread<waitableQueueDeque<int> > threadDeque(shrPtrDeque);

    threadEnque.Join();
    threadDeque.Join();
    ASSERT_EQUAL((EQ - DQ), waQueue.Size());
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
    TEST(test_multi_threads_default_CTOR)
    
    TEST(test_multi_threads_size)

    TEST(test_waitable_queue_empty)
    TEST(test_waitable_queue_not_empty)
END_SUITE