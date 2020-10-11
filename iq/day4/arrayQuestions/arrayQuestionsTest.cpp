#include "mu_test.h"

#include "arrayQuestions.hpp"
using namespace iq;

BEGIN_TEST(test_array_questions_set_important_values)
    int first[] = {-10, -2, 5, 11, 12, 13, 14};
    int second[] = {3, 9, 20};
    
    SetImportantValues(first, sizeof(first)/sizeof(first[0]), second, sizeof(second)/sizeof(second[0]));

    int wantedResult[] = {-10, -2, 5, 11, 3, 9, 20};
    ASSERT_EQUAL(wantedResult[0], first[0]);
    ASSERT_EQUAL(wantedResult[1], first[1]);
    ASSERT_EQUAL(wantedResult[2], first[2]);
    ASSERT_EQUAL(wantedResult[3], first[3]);
    ASSERT_EQUAL(wantedResult[4], first[4]);
    ASSERT_EQUAL(wantedResult[5], first[5]);
    ASSERT_EQUAL(wantedResult[6], first[6]);
END_TEST

BEGIN_TEST(test_array_questions_set_important_values_sorted)
    int first[] = {-10, -2, 5, 11, 12, 13, 14};
    int second[] = {3, 9, 20};
    
    SetImportantValuesSorted(first, sizeof(first)/sizeof(first[0]), second, sizeof(second)/sizeof(second[0]));

    int wantedResult[] = {-10, -2, 3, 5, 9, 11, 20};
    ASSERT_EQUAL(wantedResult[0], first[0]);
    ASSERT_EQUAL(wantedResult[1], first[1]);
    ASSERT_EQUAL(wantedResult[2], first[2]);
    ASSERT_EQUAL(wantedResult[3], first[3]);
    ASSERT_EQUAL(wantedResult[4], first[4]);
    ASSERT_EQUAL(wantedResult[5], first[5]);
    ASSERT_EQUAL(wantedResult[6], first[6]);
END_TEST

BEGIN_TEST(test_array_questions_set_important_values_sorted_second_small_values)
    int first[] = {3, 5, 11, 12, 13, 14, 17};
    int second[] = {-5, -1, 2};
    
    SetImportantValuesSorted(first, sizeof(first)/sizeof(first[0]), second, sizeof(second)/sizeof(second[0]));

    int wantedResult[] = {-5, -1, 2, 3, 5, 11, 12};
    ASSERT_EQUAL(wantedResult[6], first[6]);
    ASSERT_EQUAL(wantedResult[5], first[5]);
    ASSERT_EQUAL(wantedResult[4], first[4]);
    ASSERT_EQUAL(wantedResult[3], first[3]);
    ASSERT_EQUAL(wantedResult[2], first[2]);
    ASSERT_EQUAL(wantedResult[1], first[1]);
    ASSERT_EQUAL(wantedResult[0], first[0]);
END_TEST

BEGIN_TEST(test_array_questions_set_my_shadow)
    int numbers[] = {2, 3, 7, 1, 5, 6, 9, 2, 5, 3, 1};

    int wantedResult[] = {3, 7, 9, 5, 6, 9, 9, 5, 5, 3, 1};
    
    SetMyShadow(numbers, sizeof(numbers)/sizeof(numbers[0]));

    for(size_t i = 0; i < 11; ++i) {
        ASSERT_EQUAL(wantedResult[i], numbers[i]);
    }
END_TEST

BEGIN_SUITE(test_array_questions)
    TEST(test_array_questions_set_important_values)

    TEST(test_array_questions_set_important_values_sorted)
    TEST(test_array_questions_set_important_values_sorted_second_small_values)

    TEST(test_array_questions_set_my_shadow)
END_SUITE