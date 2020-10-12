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
/*
BEGIN_TEST(test_multiply_two_numbers)
    unsigned int first = 3;
    unsigned int second = 5;

    unsigned int result = MultiplyTwoNumbers(first, second);
    ASSERT_EQUAL(15, result);
END_TEST

BEGIN_TEST(test_multiply_two_numbers_big_numbers)
    unsigned int first = 7586;
    unsigned int second = 145;

    unsigned int result = MultiplyTwoNumbers(first, second);
    ASSERT_EQUAL(first * second, result);
END_TEST
*/

BEGIN_TEST(test_number_of_identical_pairs)
    int bits[] = {1, 1, 0, 1, 0, 0};

    size_t result = NumberOfIdenticalPairs(bits, 8);
    ASSERT_EQUAL(2, result);
END_TEST

BEGIN_TEST(test_number_of_identical_pairs_adjacent_pair)
    int bits[] = {0, 0, 1, 1, 1, 0, 0, 1};

    size_t result = NumberOfIdenticalPairs(bits, 8);
    ASSERT_EQUAL(4, result);
END_TEST

BEGIN_TEST(test_counter_small_characters)
    size_t result = Counter("abryacaydabra", "bax");

    ASSERT_EQUAL(7, result);
END_TEST

BEGIN_TEST(test_counter_small_and_big_characters)
    size_t result = Counter("aGbryCacGaydGabraA", "baGx");

    ASSERT_EQUAL(10, result);
END_TEST

BEGIN_SUITE(test_day_5)
    TEST(test_add_two_numbers)
    TEST(test_add_two_numbers_big_numbers)

    //TEST(test_multiply_two_numbers)
    //TEST(test_multiply_two_numbers_big_numbers)

    TEST(test_number_of_identical_pairs)
    TEST(test_number_of_identical_pairs_adjacent_pair)

    TEST(test_counter_small_characters)
    TEST(test_counter_small_and_big_characters)
END_SUITE