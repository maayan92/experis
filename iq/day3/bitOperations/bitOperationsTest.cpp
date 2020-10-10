#include "mu_test.h"

#include "bitOperations.hpp"
using namespace iq;

BEGIN_TEST(test_bit_operations_reverse_bits)
    int num = 731;
    
    ReverseBits(num);
    ASSERT_EQUAL(877, num);
END_TEST

BEGIN_TEST(test_bit_operations_reverse_bits_big_number)
    int num = 254689752;
    
    ReverseBits(num);
    ASSERT_EQUAL(28845903, num);
END_TEST

BEGIN_TEST(test_bit_operations_swap_adjacent_bits)
    long num = 201;
    
    SwapAdjacentBits(num);
    ASSERT_EQUAL(198, num);
END_TEST

BEGIN_TEST(test_bit_operations_swap_adjacent_bits_big_number)
    long num = 254689752;
    
    SwapAdjacentBits(num);
    ASSERT_EQUAL(253592292, num);
END_TEST

BEGIN_TEST(test_majority_of_on_bits_true)
    int num = 310319999;

    ASSERT_THAT(Majority(num));
END_TEST

BEGIN_TEST(test_majority_of_on_bits_false)
    int num = 16;

    ASSERT_THAT(!Majority(num));
END_TEST

BEGIN_TEST(test_majority_of_on_bits_true_negative_number)
    int num = -1;

    ASSERT_THAT(Majority(num));
END_TEST

BEGIN_TEST(test_majority_of_on_bits_false_negative_number)
    int num = -310319999;

    ASSERT_THAT(!Majority(num));
END_TEST

BEGIN_TEST(test_majority_of_on_bits_using_lut_true)
    int num = 310319999;

    ASSERT_THAT(Majority(num));
END_TEST

BEGIN_TEST(test_majority_of_on_bits_using_lut_false)
    int num = 16;

    ASSERT_THAT(!Majority(num));
END_TEST

BEGIN_SUITE(test_bit_operations)
    TEST(test_bit_operations_reverse_bits)
    TEST(test_bit_operations_reverse_bits_big_number)
    
    TEST(test_bit_operations_swap_adjacent_bits)
    TEST(test_bit_operations_swap_adjacent_bits_big_number)

    TEST(test_majority_of_on_bits_true)
    TEST(test_majority_of_on_bits_false)
    TEST(test_majority_of_on_bits_true_negative_number)
    TEST(test_majority_of_on_bits_false_negative_number)

    TEST(test_majority_of_on_bits_using_lut_true)
    TEST(test_majority_of_on_bits_using_lut_false)
END_SUITE
