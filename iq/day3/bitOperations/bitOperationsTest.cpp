#include "mu_test.h"

#include "bitOperations.hpp"
using namespace iq;

BEGIN_TEST(test_bit_operations_reverse_bits)
    int num = 731;
    
    ReverseBits(num);
    ASSERT_EQUAL(877, num);
END_TEST

BEGIN_SUITE(test_bit_operations)
    TEST(test_bit_operations_reverse_bits)
END_SUITE
