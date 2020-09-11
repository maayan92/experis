#include "threadGroup.hpp"
#include "runnable.hpp"
#include "mu_test.h"
#include <iostream>
using namespace std;
using namespace advcpp;
using namespace experis;

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

class AtomicDecrementer : public IRunnable {
public:
    AtomicDecrementer(Atomic<size_t>& a_count)
    : m_count(a_count)
    {}

    void operator()() {
        --m_count;
    }

private:
    Atomic<size_t>& m_count;
};

class SetThreadId : public IRunnable {
public:
    SetThreadId(pthread_t& a_getId)
    : m_getId(a_getId)
    {}

    void operator()() {
        m_getId = pthread_self();
    }

private:
    pthread_t& m_getId;
};

class RemoveThread : public IRunnable {
public:
    RemoveThread(ThreadGroup<IRunnable>& a_threads, pthread_t& a_id)
    : m_threads(a_threads)
    , m_id(a_id)
    {}

    void operator()() {
        try {
            m_threads.RemoveThread(m_id);
        } catch(const exception& exc) {
            cout << exc.what() << '\n';
        }
    }

private:
    ThreadGroup<IRunnable>& m_threads;
    pthread_t& m_id;
};

template<typename T, size_t NUM_OF_THREADS>
class AddThreads : public IRunnable {
public:
    AddThreads(ThreadGroup<IRunnable>& a_threads, Atomic<size_t>& a_count)
    : m_threads(a_threads)
    , m_count(a_count)
    {}

    void operator()() {
        m_threads.AddThreads(shared_ptr<T>(new T(m_count)), NUM_OF_THREADS);
    }

private:
    ThreadGroup<IRunnable>& m_threads;
    Atomic<size_t>& m_count;
};

// **** tests: **** //

BEGIN_TEST(test_thread_group_create)
    const size_t NUM_OF_THREADS = 5;

    Atomic<size_t> count;
    shared_ptr<AtomicIncrementer> ptr(new AtomicIncrementer(count));
    ThreadGroup<IRunnable> threads(ptr, NUM_OF_THREADS);

    threads.JoinAll();

    ASSERT_EQUAL(NUM_OF_THREADS, threads.NumOfThread());
    ASSERT_EQUAL(NUM_OF_THREADS, count);
END_TEST

BEGIN_TEST(test_thread_group_create_default_size)
    Atomic<size_t> count;
    shared_ptr<AtomicIncrementer> ptr(new AtomicIncrementer(count));
    ThreadGroup<IRunnable> threads(ptr);

    threads.JoinAll();

    ASSERT_EQUAL(1, threads.NumOfThread());
    ASSERT_EQUAL(1, count);
END_TEST

BEGIN_TEST(test_thread_group_create_add_threads)
    const size_t NUM_OF_THREADS = 5;
    const size_t NUM_OF_THREADS_TO_ADD = 3;

    Atomic<size_t> count;
    shared_ptr<AtomicIncrementer> ptrIncrement(new AtomicIncrementer(count));
    ThreadGroup<IRunnable> threads(ptrIncrement, NUM_OF_THREADS);

    shared_ptr<AtomicDecrementer> ptrDecrement(new AtomicDecrementer(count));
    threads.AddThreads(ptrDecrement, NUM_OF_THREADS_TO_ADD);
    threads.JoinAll();

    ASSERT_EQUAL(NUM_OF_THREADS + NUM_OF_THREADS_TO_ADD, threads.NumOfThread());
    ASSERT_EQUAL(NUM_OF_THREADS - NUM_OF_THREADS_TO_ADD, count);
END_TEST

BEGIN_TEST(test_thread_group_create_add_threads_default_size)
    const size_t NUM_OF_THREADS = 5;

    Atomic<size_t> count;
    shared_ptr<AtomicIncrementer> ptrIncrement(new AtomicIncrementer(count));
    ThreadGroup<IRunnable> threads(ptrIncrement, NUM_OF_THREADS);

    shared_ptr<AtomicDecrementer> ptrDecrement(new AtomicDecrementer(count));
    threads.AddThreads(ptrDecrement);

    threads.JoinAll();
    ASSERT_EQUAL(NUM_OF_THREADS + 1, threads.NumOfThread());
    ASSERT_EQUAL(NUM_OF_THREADS - 1, count);
END_TEST

BEGIN_TEST(test_thread_group_create_remove_thread)
    const size_t NUM_OF_THREADS = 5;

    Atomic<size_t> count;
    shared_ptr<AtomicIncrementer> ptrIncrement(new AtomicIncrementer(count));
    ThreadGroup<IRunnable> threads(ptrIncrement, NUM_OF_THREADS);

    pthread_t threadId;
    shared_ptr<SetThreadId> ptrThreadId(new SetThreadId(threadId));
    threads.AddThreads(ptrThreadId);

    threads.RemoveThread(threadId);
    threads.JoinAll();

    ASSERT_EQUAL(NUM_OF_THREADS, threads.NumOfThread());
    ASSERT_EQUAL(NUM_OF_THREADS, count);
END_TEST

BEGIN_TEST(test_thread_group_multi_threads_remove_and_add)
    const size_t NUM_OF_THREADS = 5;
    const size_t NUM_OF_THREADS_ADD = 5;
    const size_t NUM_OF_THREADS_TASK_ADD = 3;

    Atomic<size_t> count;
    shared_ptr<AtomicIncrementer> ptrIncrement(new AtomicIncrementer(count));
    ThreadGroup<IRunnable> threads(ptrIncrement, NUM_OF_THREADS);

    pthread_t threadId;
    shared_ptr<SetThreadId> ptrThreadId(new SetThreadId(threadId));
    threads.AddThreads(ptrThreadId);

    shared_ptr<RemoveThread> ptrRemove(new RemoveThread(threads, threadId));
    threads.AddThreads(ptrRemove);

    shared_ptr<AddThreads<AtomicDecrementer, NUM_OF_THREADS_TASK_ADD> > ptrAdd(new AddThreads<AtomicDecrementer, 3>(threads, count));
    threads.AddThreads(ptrAdd, NUM_OF_THREADS_ADD);

    threads.JoinAll();

    size_t threadsAdded = (NUM_OF_THREADS_ADD * NUM_OF_THREADS_TASK_ADD);
    ASSERT_EQUAL(NUM_OF_THREADS + NUM_OF_THREADS_ADD + threadsAdded + 1, threads.NumOfThread());
    ASSERT_EQUAL(NUM_OF_THREADS - threadsAdded, count);
END_TEST

BEGIN_SUITE(test_thread_group)
    TEST(test_thread_group_create)
    TEST(test_thread_group_create_default_size)

    TEST(test_thread_group_create_add_threads)
    TEST(test_thread_group_create_add_threads_default_size)

    TEST(test_thread_group_create_remove_thread)

    TEST(test_thread_group_multi_threads_remove_and_add)
END_SUITE