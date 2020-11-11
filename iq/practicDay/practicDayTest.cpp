#include "mu_test.h"

#include "practicDay.hpp"
using namespace iq;

BEGIN_TEST(test_has_pyramid_true)
    int domino[] = {1, 4, 5, 6, 7, 6, 5, 6, 4, 5, 7, 8};
    ASSERT_THAT(HasPyramid(domino, sizeof(domino)/sizeof(domino[0])));
END_TEST

BEGIN_TEST(test_has_pyramid_false)
    int domino[] = {1, 4, 5, 6, 1, 6, 5, 6, 4, 5, 7, 8};
    ASSERT_THAT(!HasPyramid(domino, sizeof(domino)/sizeof(domino[0])));
END_TEST

BEGIN_TEST(test_has_pair_sum_true)
    int numbers[] = {1, 5, -7, 8, 7, 10};
    ASSERT_THAT(HasPairSum(numbers, sizeof(numbers)/sizeof(numbers[0]), 11));
END_TEST

BEGIN_TEST(test_has_pair_sum_false)
    int numbers[] = {1, 5, -7, 8, 7, 11};
    ASSERT_THAT(!HasPairSum(numbers, sizeof(numbers)/sizeof(numbers[0]), 11));
END_TEST

BEGIN_TEST(test_fill_mat)
    size_t mat[SIZE][SIZE] = {0};

    FillMat(mat);
    for(size_t i = 0; i < SIZE; ++i) {
        for(size_t j = 0; j < SIZE; ++j) {
            size_t num = i*10 + j + 1;
            ASSERT_EQUAL(num, mat[i][j]);
        }
    }
END_TEST

BEGIN_SUITE(test_practic_day)
    TEST(test_has_pyramid_true)
    TEST(test_has_pyramid_false)

    TEST(test_has_pair_sum_true)
    TEST(test_has_pair_sum_false)

    TEST(test_fill_mat)
END_SUITE