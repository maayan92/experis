#include "mu_test.h"

#include "arrayAndString.hpp"
using namespace iq;

//Q2:

BEGIN_TEST(test_check_permutation_true)
    char first[] = "questionsTest";
    char second[] = "Testquestions";

    ASSERT_THAT(CheckPermutation(first, second));
END_TEST

BEGIN_TEST(test_check_permutation_false)
    char first[] = "questionstest";
    char second[] = "Testquestions";

    ASSERT_THAT(!CheckPermutation(first, second));
END_TEST

//Q3:

BEGIN_TEST(test_urlify)
    char str[] = "mr john smith    ";

    ASSERT_THAT(URLify(str, 13));
    ASSERT_EQUAL(0, strcmp("mr%20john%20smith", str));
END_TEST

BEGIN_TEST(test_urlify_null_string)
    ASSERT_THAT(!URLify(0, 13));
END_TEST

//Q4:

BEGIN_TEST(test_palindrome_permutation_true)
    ASSERT_THAT(PalindromePermutation("taco cat", "atco cta"));
END_TEST

BEGIN_TEST(test_palindrome_permutation_false)
    ASSERT_THAT(!PalindromePermutation("taco cat", "atc cta"));
END_TEST

//Q5:

BEGIN_TEST(test_one_away_remove)
    ASSERT_THAT(!PalindromePermutation("pale", "ple"));
END_TEST

BEGIN_TEST(test_one_away_remove_last)
    ASSERT_THAT(!PalindromePermutation("pales", "pale"));
END_TEST

BEGIN_TEST(test_one_away_remove_two)
    ASSERT_THAT(!PalindromePermutation("pales", "pae"));
END_TEST

BEGIN_TEST(test_one_away_add)
    ASSERT_THAT(!PalindromePermutation("pale", "palle"));
END_TEST

BEGIN_TEST(test_one_away_add_to_last)
    ASSERT_THAT(!PalindromePermutation("pale", "pales"));
END_TEST

BEGIN_TEST(test_one_away_add_two)
    ASSERT_THAT(!PalindromePermutation("pale", "palles"));
END_TEST

BEGIN_TEST(test_one_away_replace_one)
    ASSERT_THAT(!PalindromePermutation("pale", "bale"));
END_TEST

BEGIN_TEST(test_one_away_replace_two)
    ASSERT_THAT(!PalindromePermutation("pale", "bake"));
END_TEST

//Q6:

BEGIN_TEST(test_string_compression)
    char str[] = "aabcccccaaa";

    ASSERT_THAT(StringCompression(str));
    ASSERT_EQUAL(0, strcmp("a2b1c5a3", str));
END_TEST

BEGIN_TEST(test_string_compression_longer_compressed)
    char str[] = "aabcaa";

    ASSERT_THAT(!StringCompression(str));
    ASSERT_EQUAL(0, strcmp("aabcaa", str));
END_TEST

//Q7:

BEGIN_TEST(test_rotate_matrix)
    int mat[][SIZE] = {{1 ,2, 3, 4, 5},
                        {6, 7, 8, 9, 10},
                        {11, 12, 13, 14, 15},
                        {16, 17, 18, 19, 20},
                        {21, 22, 23, 24, 25}};

    ASSERT_THAT(RotateMatrix(mat));

    int wantedResult[][SIZE] = {{21 ,16, 11, 6, 1},
                                {22, 17, 12, 7, 2},
                                {23, 18, 13, 8, 3},
                                {24, 19, 14, 9, 4},
                                {25, 20, 15, 10, 5}};

    for(size_t i = 0; i < SIZE; ++i) {
        for(size_t j = 0; j < SIZE; ++j) {
            ASSERT_EQUAL(mat[i][j], wantedResult[i][j]);
        }
    }
END_TEST

//Q8:

BEGIN_TEST(test_zero_matrix)
    int mat[][SIZE] = {{1 ,2, 3, 4, 5},
                        {6, 7, 8, 9, 10},
                        {11, 12, 0, 14, 15},
                        {16, 17, 18, 0, 20},
                        {21, 22, 23, 24, 25}};

    ASSERT_THAT(ZeroMatrix(mat));

    int wantedResult[][SIZE] = {{1 ,2, 0, 0, 5},
                                {6, 7, 0, 0, 10},
                                {0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0},
                                {21, 22, 0, 0, 25}};

    for(size_t i = 0; i < SIZE; ++i) {
        for(size_t j = 0; j < SIZE; ++j) {
            ASSERT_EQUAL(mat[i][j], wantedResult[i][j]);
        }
    }
END_TEST

//Q9:

BEGIN_TEST(test_string_rotation_true)
    char first[] = "waterbottle";
    char second[] = "erbottlewat";

    ASSERT_THAT(StringRotation(first, second));
END_TEST

BEGIN_TEST(test_string_rotation_false)
    char first[] = "waterbottle";
    char second[] = "erbottlewa";

    ASSERT_THAT(!StringRotation(first, second));
END_TEST

BEGIN_SUITE(test_array_and_string)
    TEST(test_check_permutation_true)
    TEST(test_check_permutation_false)

    TEST(test_urlify)
    TEST(test_urlify_null_string)

    TEST(test_palindrome_permutation_true)
    TEST(test_palindrome_permutation_false)

    TEST(test_one_away_remove)
    TEST(test_one_away_remove_last)
    TEST(test_one_away_remove_two)
    TEST(test_one_away_add)
    TEST(test_one_away_add_to_last)
    TEST(test_one_away_add_two)
    TEST(test_one_away_replace_one)
    TEST(test_one_away_replace_two)

    TEST(test_string_compression)
    TEST(test_string_compression_longer_compressed)

    TEST(test_rotate_matrix)

    TEST(test_zero_matrix)

    TEST(test_string_rotation_true)
    TEST(test_string_rotation_false)
END_SUITE