#include "waitableQueue.hpp"
#include "thread.hpp"
#include "mu_test.h"
#include <climits>
#include<iostream>
#include<iomanip>
using namespace advcpp;

template<typename T>
class waitableQueueEnque {
public:
    waitableQueueEnque(WaitableQueueMT<T>& a_waQueue, size_t a_size)
    : m_waQueue(a_waQueue)
    , m_size(a_size)
    {}

    void operator()() {
        for(size_t i = 0 ; i < m_size ; ++i) {
            m_waQueue.Enque(val++);
        }
    }

private:
    WaitableQueueMT<T>& m_waQueue;
    size_t m_size;
    static size_t val;
};

template<typename T>
size_t waitableQueueEnque<T>::val = 1;

template<typename T>
class waitableQueueDeque {
public:
    waitableQueueDeque(WaitableQueueMT<T>& a_waQueue, size_t a_size)
    : m_waQueue(a_waQueue)
    , m_size(a_size)
    {}
    
    void operator()() {
        for(size_t i = 0 ; i < m_size ; ++i) {
            m_waQueue.Deque();
        }
    }

private:
    WaitableQueueMT<T>& m_waQueue;
    size_t m_size;
};

BEGIN_TEST(test_create_waitable_queue)
    WaitableQueueMT<int> waQueue;
    ASSERT_THAT(waQueue.Empty());
END_TEST

BEGIN_TEST(test_waitable_queue_enque_one)
    WaitableQueueMT<int> waQueue(5);
    waQueue.Enque(5);
    ASSERT_EQUAL(1, waQueue.Size());
END_TEST

BEGIN_TEST(test_waitable_queue_deque_one)
    WaitableQueueMT<int> waQueue(5);
    waQueue.Enque(5);
    waQueue.Enque(8);
    int value = waQueue.Deque();
    ASSERT_EQUAL(1, waQueue.Size());
    ASSERT_EQUAL(5, value);
END_TEST

BEGIN_TEST(test_multi_threads_one_enque_one_deque)
    WaitableQueueMT<int> waQueue(5);
    shared_ptr<waitableQueueEnque<int> > shrPtrEnque(new waitableQueueEnque<int>(waQueue, 6));
    Thread<waitableQueueEnque<int> > threadEnque(shrPtrEnque);

    shared_ptr<waitableQueueDeque<int> > shrPtrDeque(new waitableQueueDeque<int>(waQueue, 1));
    Thread<waitableQueueDeque<int> > threadDeque(shrPtrDeque);

    threadEnque.Join();
    threadDeque.Join();
    ASSERT_EQUAL(5, waQueue.Size());
END_TEST

BEGIN_TEST(test_multi_threads_two_enque)
    WaitableQueueMT<int> waQueue(5);
    shared_ptr<waitableQueueEnque<int> > shrPtrEnque(new waitableQueueEnque<int>(waQueue, 5));
    Thread<waitableQueueEnque<int> > threadEnqueFirst(shrPtrEnque);
    Thread<waitableQueueEnque<int> > threadEnqueSecond(shrPtrEnque);

    shared_ptr<waitableQueueDeque<int> > shrPtrDeque(new waitableQueueDeque<int>(waQueue, 6));
    Thread<waitableQueueDeque<int> > threadDeque(shrPtrDeque);

    threadEnqueFirst.Join();
    threadEnqueSecond.Join();
    threadDeque.Join();
    ASSERT_EQUAL(4, waQueue.Size());
END_TEST

BEGIN_TEST(test_multi_threads_two_deque)
    WaitableQueueMT<int> waQueue(5);
    shared_ptr<waitableQueueDeque<int> > shrPtrDeque(new waitableQueueDeque<int>(waQueue, 2));
    Thread<waitableQueueDeque<int> > threadDequeFirst(shrPtrDeque);
    Thread<waitableQueueDeque<int> > threadDequeSecond(shrPtrDeque);
    
    shared_ptr<waitableQueueEnque<int> > shrPtrEnque(new waitableQueueEnque<int>(waQueue, 5));
    Thread<waitableQueueEnque<int> > threadEnque(shrPtrEnque);


    threadDequeFirst.Join();
    threadDequeSecond.Join();
    threadEnque.Join();
    ASSERT_EQUAL(1, waQueue.Size());
END_TEST

BEGIN_TEST(test_multi_threads_default_CTOR)
    WaitableQueueMT<int> waQueue;
    shared_ptr<waitableQueueEnque<int> > shrPtrEnque(new waitableQueueEnque<int>(waQueue, 5000000));
    Thread<waitableQueueEnque<int> > threadEnqueFirst(shrPtrEnque);
    Thread<waitableQueueEnque<int> > threadEnqueSecond(shrPtrEnque);

    shared_ptr<waitableQueueDeque<int> > shrPtrDeque(new waitableQueueDeque<int>(waQueue, 6));
    Thread<waitableQueueDeque<int> > threadDeque(shrPtrDeque);

    threadEnqueFirst.Join();
    threadEnqueSecond.Join();
    threadDeque.Join();
    ASSERT_EQUAL(9999994, waQueue.Size());
END_TEST

BEGIN_TEST(test_multi_threads_size)
    WaitableQueueMT<int> waQueue(5);
    shared_ptr<waitableQueueEnque<int> > shrPtrEnque(new waitableQueueEnque<int>(waQueue, 10));
    Thread<waitableQueueEnque<int> > threadEnque(shrPtrEnque);

    shared_ptr<waitableQueueDeque<int> > shrPtrDeque(new waitableQueueDeque<int>(waQueue, 8));
    Thread<waitableQueueDeque<int> > threadDeque(shrPtrDeque);

    threadEnque.Join();
    threadDeque.Join();
    ASSERT_EQUAL(2, waQueue.Size());
END_TEST

BEGIN_TEST(test_waitable_queue_empty)
    WaitableQueueMT<int> waQueue(5);
    ASSERT_THAT(waQueue.Empty());
END_TEST

BEGIN_TEST(test_waitable_queue_not_empty)
    WaitableQueueMT<int> waQueue(5);
    waQueue.Enque(1);
    ASSERT_THAT(!waQueue.Empty());
END_TEST

BEGIN_SUITE(test)
    TEST(test_create_waitable_queue)

    TEST(test_waitable_queue_enque_one)
    TEST(test_waitable_queue_deque_one)

    TEST(test_multi_threads_one_enque_one_deque)
    TEST(test_multi_threads_two_enque)
    TEST(test_multi_threads_two_deque)
    TEST(test_multi_threads_default_CTOR)
    
    TEST(test_multi_threads_size)

    TEST(test_waitable_queue_empty)
    TEST(test_waitable_queue_not_empty)
END_SUITE