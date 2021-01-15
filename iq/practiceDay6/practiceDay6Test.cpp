#include "mu_test.h"

#include "practiceDay6.hpp"
using namespace std;
using namespace iq;

BEGIN_TEST(test_closest_to_zero_negative)
    int numbers[] = { 9, -19, 2, -1, 5, 9 };
    int result;

    ASSERT_EQUAL(ClosestToZero(numbers, sizeof(numbers)/sizeof(numbers[0]), &result), SUCCESS);
    ASSERT_EQUAL(result, -1);
END_TEST

BEGIN_TEST(test_closest_to_zero_positive)
    int numbers[] = { 9, -19, 2, -1, 5, 9, 1 };
    int result;

    ASSERT_EQUAL(ClosestToZero(numbers, sizeof(numbers)/sizeof(numbers[0]), &result), SUCCESS);
    ASSERT_EQUAL(result, 1);
END_TEST

BEGIN_TEST(test_closest_to_zero_zero_answer)
    int numbers[] = { 9, -19, 2, -1, 5, 9, 1, 0 };
    int result;

    ASSERT_EQUAL(ClosestToZero(numbers, sizeof(numbers)/sizeof(numbers[0]), &result), SUCCESS);
    ASSERT_EQUAL(result, 0);
END_TEST

BEGIN_TEST(test_closest_to_zero_null_result)
    int numbers[] = { 9, -19, 2, -1, 5, 9, 1 };

    ASSERT_EQUAL(ClosestToZero(numbers, sizeof(numbers)/sizeof(numbers[0]), 0), FAILED);
END_TEST

BEGIN_TEST(test_closest_to_zero_null_array)
    int numbers[] = { 9, -19, 2, -1, 5, 9, 1 };
    int result;

    ASSERT_EQUAL(ClosestToZero(0, sizeof(numbers)/sizeof(numbers[0]), &result), FAILED);
END_TEST

BEGIN_TEST(test_closest_to_zero_zero_size)
    int numbers[] = { 9, -19, 2, -1, 5, 9, 1 };
    int result;

    ASSERT_EQUAL(ClosestToZero(numbers, 0, &result), FAILED);
END_TEST

// Q1:

BEGIN_TEST(test_count_inverse_triplet_naive)
    int numbers[] = { 5, 7, 1, -5, 3, 8, 2, 6 };
    ASSERT_EQUAL(CountInverseTripletNaive(numbers, sizeof(numbers)/sizeof(numbers[0])), 4);

    int numbers2[] = { 9, 4, 3, 5, -2 };
    ASSERT_EQUAL(CountInverseTripletNaive(numbers2, sizeof(numbers2)/sizeof(numbers2[0])), 5);
END_TEST

BEGIN_TEST(test_count_inverse_triplet_naive_null_array)
    int numbers[] = { 5, 7, 1, -5, 3, 8, 2, 6 };
    ASSERT_EQUAL(CountInverseTripletNaive(0, sizeof(numbers)/sizeof(numbers[0])), 0);
END_TEST

BEGIN_TEST(test_count_inverse_triplet_naive_zero_size)
    int numbers[] = { 5, 7, 1, -5, 3, 8, 2, 6 };
    ASSERT_EQUAL(CountInverseTripletNaive(numbers, 0), 0);
END_TEST

// Q2:

BEGIN_TEST(test_find_min_max_elements)
    int numbers[] = { 5, 7, 1, -5, 3, 8, 2, 6 };
    int min;
    int max;

    ASSERT_THAT(FindMinMaxElements(numbers, sizeof(numbers)/sizeof(numbers[0]), min, max));
    ASSERT_EQUAL(min, -5);
    ASSERT_EQUAL(max, 8);
END_TEST

// Q3:

BEGIN_TEST(test_get_K_closest_elements_to_X)
    int numbers[] = { 9, 5, 8, -1, 7, 2, 4 };

    vector<int> result;
    ASSERT_THAT(GetKClosestElementsToX(numbers, sizeof(numbers)/sizeof(numbers[0]), 3, 6, result));
    
    int wantedResult[] = { 5, 7, 8 };
    size_t i = 0;

    auto itr = result.begin();
    auto end = result.end();
    while(itr != end) {
        ASSERT_EQUAL(wantedResult[i], *itr);
        ++i;
        ++itr;
    }
END_TEST

BEGIN_SUITE(test_practice_day_6)
    TEST(test_closest_to_zero_negative)
    TEST(test_closest_to_zero_positive)
    TEST(test_closest_to_zero_zero_answer)
    TEST(test_closest_to_zero_null_array)
    TEST(test_closest_to_zero_null_result)
    TEST(test_closest_to_zero_zero_size)

    TEST(test_count_inverse_triplet_naive)
    TEST(test_count_inverse_triplet_naive_null_array)
    TEST(test_count_inverse_triplet_naive_zero_size)

    TEST(test_find_min_max_elements)

    TEST(test_get_K_closest_elements_to_X)
END_SUITE