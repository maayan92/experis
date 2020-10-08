#include "mu_test.h"

#include "day3Questions.hpp"
using namespace iq;

BEGIN_TEST(test_smallest_positive_not_present_naive)
    int numbers[] = {-7, 8, -2, 0, 8, 3, 9, 2, 1};

    ASSERT_EQUAL(4, NaiveSmallestPositiveNotPresent(numbers, sizeof(numbers)/sizeof(numbers[0])));
END_TEST

BEGIN_TEST(test_smallest_positive_not_present_naive_sequence_array)
    int numbers[] = {7, 6, 4, 0, 8, 3, 5, 2, 1};

    ASSERT_EQUAL(9, NaiveSmallestPositiveNotPresent(numbers, sizeof(numbers)/sizeof(numbers[0])));
END_TEST

BEGIN_SUITE(test_day_3)
    TEST(test_smallest_positive_not_present_naive)
    TEST(test_smallest_positive_not_present_naive_sequence_array)
END_SUITE
