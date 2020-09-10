#include "singleton.hpp"
#include "threadPool.hpp"
#include "mu_test.h"
#include<iostream>
using namespace std;
using namespace advcpp;
using namespace experis;

class Player : private Uncopyable {
    friend Singleton<Player>;
public:
    static size_t GetNumOfPlayers() { 
        return playersCounter;
    }

    void AddData() { 
        ++m_data;
    }

    size_t GetData() { 
        return m_data;
    }

private:
    Player()
    : m_data(0)
    {
        ++playersCounter;
    }

private:
    static Atomic<size_t> playersCounter;
    Atomic<size_t> m_data;
};

Atomic<size_t> Player::playersCounter(0);

struct Task : public IRunnable {
    void operator()() {
        Singleton<Player>::Instance().AddData();
    }
};

// **** tests **** //

BEGIN_TEST(test_singleton_multi_threads)
    ThreadPool threads(0);
    
    size_t NUM_OF_TASKS = 100000;
    shared_ptr<Task> shrPtr(new Task());
    for(size_t i = 0; i < NUM_OF_TASKS; ++i) {
        threads.Submit(shrPtr);
    }

    Player& player = Singleton<Player>::Instance();
    threads.AddThread(5);
    threads.ShutDown();

    ASSERT_EQUAL(1, Player::GetNumOfPlayers());
    ASSERT_EQUAL(NUM_OF_TASKS, player.GetData());
END_TEST

BEGIN_TEST(test_singleton_one_thread)
    Singleton<Player>::Instance();
    Singleton<Player>::Instance();
    Singleton<Player>::Instance();

    ASSERT_EQUAL(1, Player::GetNumOfPlayers());
END_TEST

BEGIN_SUITE(test_singleton)
    TEST(test_singleton_multi_threads)
    TEST(test_singleton_one_thread)
END_SUITE