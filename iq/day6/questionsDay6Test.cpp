#include "mu_test.h"

#include "questionsDay6.hpp"
using namespace iq;

BEGIN_TEST(test_swap_by_arithmetic_op)
    int first = 5;
    int second = 3;

    Swap(first, second);
    ASSERT_EQUAL(3, first);
    ASSERT_EQUAL(5, second);
END_TEST

BEGIN_TEST(test_swap_by_bits)
    int first = 5;
    int second = 3;

    SwapBits(first, second);
    ASSERT_EQUAL(3, first);
    ASSERT_EQUAL(5, second);
END_TEST

BEGIN_TEST(test_abs)
    int num = -5;

    Abs(num);
    ASSERT_EQUAL(5, num);
END_TEST

BEGIN_TEST(test_abs_big_num)
    int num = -356456456;

    Abs(num);
    ASSERT_EQUAL(356456456, num);
END_TEST

BEGIN_TEST(test_number_of_identical_pairs)
    unsigned long num = 16;
    
    ASSERT_EQUAL(58, NumberOfIdenticalPairs(num));
END_TEST

BEGIN_TEST(test_number_of_identical_pairs_big_number)
    unsigned long num = 547657756765;
    
    ASSERT_EQUAL(24, NumberOfIdenticalPairs(num));
END_TEST

BEGIN_SUITE(test_day_6)
    TEST(test_swap_by_arithmetic_op)
    TEST(test_swap_by_bits)

    TEST(test_abs)
    TEST(test_abs_big_num)

    TEST(test_number_of_identical_pairs)
    TEST(test_number_of_identical_pairs_big_number)
END_SUITE