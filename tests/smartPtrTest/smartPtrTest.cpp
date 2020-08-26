#include "mu_test.h"
#include "testClasses.hpp"
#include "smartPtr.hpp"
#include <climits>
#include<iostream>
#include<iomanip>
#include <string>
using namespace advcpp;
using namespace std;

BEGIN_TEST(create_smartPtr)
    SmartPtr<int> smartPtr(new int);
    ASSERT_PASS();
END_TEST

BEGIN_TEST(create_smartPtr_inheritance_pow)
    SmartPtr<Number> smartPtr(new Pow(8));
    ASSERT_PASS();
END_TEST

BEGIN_TEST(create_smartPtr_inheritance_double)
    SmartPtr<Number> smartPtr(new Double(8));
    ASSERT_PASS();
END_TEST

BEGIN_TEST(smartPtr_operator_arrow)
    SmartPtr<string> smartPtr(new string);
    ASSERT_THAT(smartPtr->c_str());
END_TEST

BEGIN_TEST(smartPtr_operator_arrow_pow)
    SmartPtr<Number> smartPtr(new Pow(0));
    ASSERT_EQUAL(0, smartPtr->GetValue());
END_TEST

BEGIN_TEST(smartPtr_operator_arrow_double)
    SmartPtr<Number> smartPtr(new Double(0));
    ASSERT_EQUAL(0, smartPtr->GetValue());
END_TEST

BEGIN_TEST(smartPtr_operator_dereference)
    SmartPtr<int> smartPtr(new int);
    int& alias = *smartPtr;
    alias = 5;
    ASSERT_EQUAL(5, *smartPtr);
END_TEST

BEGIN_TEST(smartPtr_operator_dereference_number)
    SmartPtr<Number> smartPtr(new Number(8));
    ASSERT_EQUAL(8, (*smartPtr).GetValue());
END_TEST

BEGIN_TEST(smartPtr_operator_dereference_pow)
    SmartPtr<Number> smartPtr(new Pow(8));
    ASSERT_EQUAL(64, (*smartPtr).GetValue());
END_TEST

BEGIN_TEST(smartPtr_operator_dereference_double)
    SmartPtr<Number> smartPtr(new Double(8));
    ASSERT_EQUAL(16, (*smartPtr).GetValue());
END_TEST

BEGIN_TEST(smartPtr_is_not_null)
    SmartPtr<int> smartPtr(new int);
    ASSERT_THAT(smartPtr);
END_TEST

BEGIN_TEST(smartPtr_is_not_null_pow)
    SmartPtr<Number> smartPtr(new Pow(0));
    ASSERT_THAT(smartPtr);
END_TEST

BEGIN_TEST(smartPtr_is_not_null_double)
    SmartPtr<Number> smartPtr(new Double(0));
    ASSERT_THAT(smartPtr);
END_TEST

BEGIN_TEST(smartPtr_is_null)
    SmartPtr<int> smartPtr;
    ASSERT_THAT(!smartPtr);
END_TEST

BEGIN_TEST(smartPtr_compare_to_zero)
    SmartPtr<int> smartPtr;
    ASSERT_EQUAL(0, smartPtr);
END_TEST

BEGIN_TEST(smartPtr_operator_address_of)
    SmartPtr<int> smartPtr(new int(5));
    int** ptr = &smartPtr;
    ASSERT_EQUAL(5, **ptr);
END_TEST

BEGIN_TEST(smartPtr_operator_equal_pow)
    SmartPtr<Number> smartPtrFirst(new Pow(5));
    SmartPtr<Number> smartPtrSecond(new Pow(5));
    ASSERT_THAT(!(smartPtrFirst == smartPtrSecond));
END_TEST

BEGIN_TEST(smartPtr_operator_equal_pow_double)
    SmartPtr<Number> smartPtrPow(new Pow(5));
    SmartPtr<Number> smartPtrDouble(new Double(5));
    ASSERT_THAT(!(smartPtrPow == smartPtrDouble));
END_TEST

BEGIN_TEST(smartPtr_operator_equal_pow_number)
    SmartPtr<Number> smartPtrPow(new Pow(5));
    SmartPtr<Number> smartPtrNumber(new Number(5));
    ASSERT_THAT(!(smartPtrPow == smartPtrNumber));
END_TEST

BEGIN_TEST(smartPtr_operator_not_equal_pow)
    SmartPtr<Number> smartPtrFirst(new Pow(5));
    SmartPtr<Number> smartPtrSecond(new Pow(5));
    ASSERT_THAT(smartPtrFirst != smartPtrSecond);
END_TEST

BEGIN_TEST(smartPtr_operator_not_equal_pow_double)
    SmartPtr<Number> smartPtrFirst(new Pow(5));
    SmartPtr<Number> smartPtrSecond(new Double(5));
    ASSERT_THAT(smartPtrFirst != smartPtrSecond);
END_TEST

BEGIN_TEST(smartPtr_cast_to_void_pointer)
    SmartPtr<int> smartPtrFirst(new int(5));
    void* ptr = &(*smartPtrFirst);
    ASSERT_THAT(ptr);
    ASSERT_EQUAL(5, *smartPtrFirst);
END_TEST

BEGIN_SUITE(smart_pointer_tests)
    TEST(create_smartPtr)
    TEST(create_smartPtr_inheritance_pow)
    TEST(create_smartPtr_inheritance_double)

    TEST(smartPtr_operator_arrow)
    TEST(smartPtr_operator_arrow_pow)
    TEST(smartPtr_operator_arrow_double)

    TEST(smartPtr_operator_dereference)
    TEST(smartPtr_operator_dereference_number)
    TEST(smartPtr_operator_dereference_pow)
    TEST(smartPtr_operator_dereference_double)

    TEST(smartPtr_is_not_null)
    TEST(smartPtr_is_not_null_pow)
    TEST(smartPtr_is_not_null_double)

    TEST(smartPtr_is_null)
    TEST(smartPtr_compare_to_zero)
    
    TEST(smartPtr_operator_address_of)

    TEST(smartPtr_operator_equal_pow)
    TEST(smartPtr_operator_equal_pow_double)
    TEST(smartPtr_operator_equal_pow_number)

    TEST(smartPtr_operator_not_equal_pow)
    TEST(smartPtr_operator_not_equal_pow_double)

    TEST(smartPtr_cast_to_void_pointer)
END_SUITE