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

BEGIN_TEST(test_abs_positive)
    int num = 5;

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

BEGIN_TEST(test_index_to_flip_end)
    int bits[] = {1, 0, 0, 1, 1, 0, 0, 1};

    ASSERT_EQUAL(7, IndexToFlip(bits, sizeof(bits)/sizeof(bits[0])));
END_TEST

BEGIN_TEST(test_index_to_flip_middle)
    int bits[] = {0, 1, 0, 1, 1, 0, 0, 1};

    ASSERT_EQUAL(1, IndexToFlip(bits, sizeof(bits)/sizeof(bits[0])));
END_TEST

BEGIN_TEST(test_index_to_flip_begin)
    int bits[] = {1, 0, 0, 1, 1, 1, 0, 0};

    ASSERT_EQUAL(0, IndexToFlip(bits, sizeof(bits)/sizeof(bits[0])));
END_TEST

BEGIN_TEST(test_index_to_flip_no_indx_to_flip)
    int bits[] = {0, 0, 1, 1, 1, 0, 0, 0};

    ASSERT_EQUAL(0, IndexToFlip(bits, sizeof(bits)/sizeof(bits[0])));
END_TEST

BEGIN_TEST(test_from_and_to_of_char)
    char letters[] = "aaabbbbbbccccccdd";

    size_t from;
    size_t to;
    FromToChar(letters, sizeof(letters)/sizeof(letters[0]), 'c', from, to);
    ASSERT_EQUAL(9, from);
    ASSERT_EQUAL(15, to);
END_TEST

BEGIN_TEST(test_from_and_to_of_char_all)
    char letters[] = "cccccccccccc";

    size_t from;
    size_t to;
    FromToChar(letters, sizeof(letters)/sizeof(letters[0]), 'c', from, to);
    ASSERT_EQUAL(0, from);
    ASSERT_EQUAL(12, to);
END_TEST

BEGIN_TEST(test_from_and_to_of_char_nothing)
    char letters[] = "aaabbbbbbdd";

    size_t from;
    size_t to;
    FromToChar(letters, sizeof(letters)/sizeof(letters[0]), 'c', from, to);
    ASSERT_EQUAL(0, from);
    ASSERT_EQUAL(0, to);
END_TEST

BEGIN_SUITE(test_day_6)
    TEST(test_swap_by_arithmetic_op)
    TEST(test_swap_by_bits)

    TEST(test_abs)
    TEST(test_abs_positive)
    TEST(test_abs_big_num)

    TEST(test_number_of_identical_pairs)
    TEST(test_number_of_identical_pairs_big_number)

    TEST(test_index_to_flip_end)
    TEST(test_index_to_flip_middle)
    TEST(test_index_to_flip_begin)
    TEST(test_index_to_flip_no_indx_to_flip)

    TEST(test_from_and_to_of_char)
    TEST(test_from_and_to_of_char_all)
    TEST(test_from_and_to_of_char_nothing)
END_SUITE