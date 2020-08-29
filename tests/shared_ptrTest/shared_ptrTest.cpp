#include "shared_ptr.hpp"
#include "mu_test.h"
#include "testClasses.hpp"
#include <climits>
#include<iostream>
#include<iomanip>
using namespace advcpp;

BEGIN_TEST(create_shared_ptr)
    shared_ptr<int> shared_ptr(new int);
    ASSERT_PASS();
END_TEST

BEGIN_TEST(create_shared_ptr_inheritance_pow)
    shared_ptr<Number> shared_ptr(new Pow(8));
    ASSERT_PASS();
END_TEST

BEGIN_TEST(create_shared_ptr_inheritance_double)
    shared_ptr<Number> shared_ptr(new Double(8));
    ASSERT_PASS();
END_TEST

BEGIN_TEST(shared_ptr_operator_assignment_base)
    shared_ptr<Number> sharedPtrNum(new Number(5));
    shared_ptr<Number> sharedPtrPow;
    sharedPtrPow = sharedPtrNum;
    ASSERT_THAT(sharedPtrNum == sharedPtrPow);
END_TEST

BEGIN_TEST(shared_ptr_operator_assignment_inheritance)
    shared_ptr<Number> sharedPtrDouble(new Double(5));
    shared_ptr<Number> sharedPtrNum;
    sharedPtrNum = sharedPtrDouble;
    ASSERT_THAT(sharedPtrNum == sharedPtrDouble);
END_TEST
/*
BEGIN_TEST(shared_ptr_operator_assignment_base_from_derived)
    shared_ptr<Double> sharedPtrDouble(new Double(5));
    shared_ptr<Number> sharedPtrNum(new Number());
    sharedPtrNum = sharedPtrDouble;
    ASSERT_THAT(sharedPtrNum == sharedPtrDouble);
END_TEST
*/
BEGIN_TEST(shared_ptr_operator_copy_constructor_base)
    shared_ptr<Number> sharedPtrNum(new Number(5));
    shared_ptr<Number> sharedPtrPow(sharedPtrNum);
    ASSERT_THAT(sharedPtrNum == sharedPtrPow);
END_TEST

BEGIN_TEST(shared_ptr_operator_copy_constructor_inheritance)
    shared_ptr<Number> sharedPtrNum(new Pow(5));
    shared_ptr<Number> sharedPtrPow(sharedPtrNum);
    ASSERT_THAT(sharedPtrNum == sharedPtrPow);
END_TEST

BEGIN_TEST(shared_ptr_operator_arrow_derived)
    shared_ptr<Pow> sharedPtrNum(new Pow(5));
    ASSERT_EQUAL(25, sharedPtrNum->GetValue());
END_TEST

BEGIN_TEST(shared_ptr_operator_arrow_inheritance)
    shared_ptr<Number> sharedPtrNum(new Pow(5));
    ASSERT_EQUAL(25, sharedPtrNum->GetValue());
END_TEST

BEGIN_TEST(shared_ptr_operator_dereference_inheritance)
    shared_ptr<Number> sharedPtrNum(new Pow(5));
    ASSERT_EQUAL(25, (*sharedPtrNum).GetValue());
END_TEST

BEGIN_TEST(shared_ptr_operator_dereference_derived)
    shared_ptr<Pow> sharedPtrNum(new Pow(5));
    ASSERT_EQUAL(25, (*sharedPtrNum).GetValue());
END_TEST

BEGIN_TEST(shared_ptr_operator_equal_base_true)
    shared_ptr<Number> sharedPtrNum(new Number(5));
    shared_ptr<Number> sharedPtrPow(sharedPtrNum);
    ASSERT_THAT(sharedPtrNum == sharedPtrPow);
END_TEST

BEGIN_TEST(shared_ptr_operator_equal_base_derived_false)
    shared_ptr<Number> sharedPtrNum(new Number(5));
    shared_ptr<Number> sharedPtrPow(new Pow(5));
    ASSERT_THAT(!(sharedPtrNum == sharedPtrPow));
END_TEST

BEGIN_TEST(shared_ptr_operator_not_equal_base_derived_true)
    shared_ptr<Number> sharedPtrNum(new Number(5));
    shared_ptr<Number> sharedPtrPow(new Pow(5));
    ASSERT_THAT(sharedPtrNum != sharedPtrPow);
END_TEST

BEGIN_TEST(shared_ptr_reset)
    shared_ptr<Number> sharedPtrNum(new Number(5));
    sharedPtrNum.Reset();
    ASSERT_THAT(!sharedPtrNum);
END_TEST

BEGIN_TEST(shared_ptr_swap)
    shared_ptr<Number> sharedPtrNum(new Number(5));
    shared_ptr<Number> sharedPtrPow(new Pow(8));
    sharedPtrPow.Swap(sharedPtrNum);
    ASSERT_EQUAL(5, sharedPtrPow->GetValue());
    ASSERT_EQUAL(64, sharedPtrNum->GetValue());
END_TEST

BEGIN_TEST(shared_ptr_use_count)
    shared_ptr<Number> sharedPtrPow(new Pow(8));
    shared_ptr<Number> sharedPtrCopy(sharedPtrPow);
    shared_ptr<Number> sharedPtrAssign;
    sharedPtrAssign = sharedPtrCopy;
    ASSERT_EQUAL(3, sharedPtrCopy.UseCount());
END_TEST

BEGIN_SUITE(shared_pointer_tests)
    TEST(create_shared_ptr)
    TEST(create_shared_ptr_inheritance_pow)
    TEST(create_shared_ptr_inheritance_double)

    TEST(shared_ptr_operator_assignment_base)
    TEST(shared_ptr_operator_assignment_inheritance)

    TEST(shared_ptr_operator_copy_constructor_base)
    TEST(shared_ptr_operator_copy_constructor_inheritance)

    TEST(shared_ptr_operator_arrow_derived)
    TEST(shared_ptr_operator_arrow_inheritance)

    TEST(shared_ptr_operator_dereference_derived)
    TEST(shared_ptr_operator_dereference_inheritance)

    TEST(shared_ptr_operator_equal_base_true)
    TEST(shared_ptr_operator_equal_base_derived_false)

    TEST(shared_ptr_operator_not_equal_base_derived_true)

    TEST(shared_ptr_reset)

    TEST(shared_ptr_swap)

    TEST(shared_ptr_use_count)

END_SUITE