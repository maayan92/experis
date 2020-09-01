#include "thread.hpp"
#include "testClasses.hpp"
#include "mu_test.h"
#include <climits>
#include<iostream>
#include<iomanip>
using namespace advcpp;
using namespace std;

// **** tests **** //

BEGIN_TEST(test_create_thread)
    shared_ptr<Pow> sharedPtr(new Pow(2));
    try {
        Thread<Pow> thread(sharedPtr);
        thread.Join();
    } catch(const exception& exc) {
        cout << exc.what() << '\n';
    }
    ASSERT_EQUAL(16, sharedPtr->GetValue());
END_TEST

BEGIN_TEST(test_create_thread_derived_to_base)
    shared_ptr<Number> sharedPtr(new Pow(2));
    ASSERT_EQUAL(4, sharedPtr->GetValue());
    try {
        Thread<Number> thread(sharedPtr);
        thread.Join();
    } catch(const exception& exc) {
        cout << exc.what() << '\n';
    }

    ASSERT_EQUAL(16, sharedPtr->GetValue());
END_TEST

BEGIN_TEST(test_create_two_threads_same_shared_ptr)
    shared_ptr<Number> sharedPtr(new Pow(2));
    ASSERT_EQUAL(4, sharedPtr->GetValue());
    try {
        Thread<Number> threadFirst(sharedPtr);
        Thread<Number> threadSecond(sharedPtr);
        threadFirst.Join();
        threadSecond.Join();
    }catch(const exception& exc) {
        cout << exc.what() << '\n';
    }

    ASSERT_EQUAL(256, sharedPtr->GetValue());
END_TEST

BEGIN_TEST(test_thread_double_join)
    shared_ptr<Pow> sharedPtr(new Pow(2));
    try {
        Thread<Pow> thread(sharedPtr);
        thread.Join();
        thread.Join();
    } catch(const exception& exc) {
        cout << exc.what() << '\n';
    }

    ASSERT_EQUAL(16, sharedPtr->GetValue());
END_TEST

BEGIN_TEST(test_thread_try_join)
    shared_ptr<Pow> sharedPtr(new Pow(2));
    try {
        Thread<Pow> thread(sharedPtr);
        try {
            thread.TryJoin();
        } catch(const std::exception& exc) {
            thread.Join();
        }

    } catch(const std::exception& exc) {
        cout << exc.what() << '\n';
    }
    
    ASSERT_EQUAL(16, sharedPtr->GetValue());
END_TEST

BEGIN_TEST(test_thread_yeild)
    shared_ptr<Pow> sharedPtr(new Pow(2));
    try {
        Thread<Pow> threadFirst(sharedPtr);
        Thread<Pow> threadSecond(sharedPtr);
        threadFirst.Yeild();
        threadSecond.Join();
        threadFirst.Join();
    } catch(const exception& exc) {
        cout << exc.what() << '\n';
    }

    ASSERT_EQUAL(256, sharedPtr->GetValue());
END_TEST

BEGIN_SUITE(test)
    TEST(test_create_thread)
    TEST(test_create_thread_derived_to_base)
    TEST(test_create_two_threads_same_shared_ptr)

    TEST(test_thread_double_join)

    TEST(test_thread_try_join)

    TEST(test_thread_yeild)
END_SUITE