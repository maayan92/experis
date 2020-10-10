#include "mu_test.h"

#include "bitOperations.hpp"
using namespace iq;

BEGIN_TEST(test_bit_operations_reverse_bits)
    int num = 731;
    
    ReverseBits(num);
    ASSERT_EQUAL(877, num);
END_TEST

BEGIN_TEST(test_bit_operations_swap_adjacent_bits)
    long num = 201;
    
    SwapAdjacentBits(num);
    ASSERT_EQUAL(198, num);
END_TEST

BEGIN_SUITE(test_bit_operations)
    TEST(test_bit_operations_reverse_bits)
    TEST(test_bit_operations_swap_adjacent_bits)
END_SUITE
