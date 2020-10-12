#include "mu_test.h"

#include "questionsDay5.hpp"
using namespace iq;

BEGIN_TEST(test_add_two_numbers)
    unsigned int first = 3;
    unsigned int second = 5;

    unsigned int  result = AddTwoNumbers(first, second);
    ASSERT_EQUAL(8, result);
END_TEST

BEGIN_TEST(test_add_two_numbers_big_numbers)
    unsigned int first = 4564545;
    unsigned int second = 7483758;

    unsigned int  result = AddTwoNumbers(first, second);
    ASSERT_EQUAL(first + second, result);
END_TEST

BEGIN_SUITE(test_day_5)
    TEST(test_add_two_numbers)
    TEST(test_add_two_numbers_big_numbers)
END_SUITE