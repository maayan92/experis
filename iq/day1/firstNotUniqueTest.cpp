#include "mu_test.h"

#include "firstNotUnique.hpp"
using namespace iq;

BEGIN_TEST(test_first_not_unique_O_n)
END_TEST

BEGIN_TEST(test_first_not_unique_O_n_n)
    int arr[] = {1, 3, 4, 2, 7, 4, 9, 3};

    int result;
    ASSERT_THAT(FindElementODoubleN(arr, sizeof(arr)/sizeof(arr[0]), result));
    ASSERT_EQUAL(3, result);
END_TEST

BEGIN_SUITE(test_first_not_unique)
    TEST(test_first_not_unique_O_n_n)
END_SUITE
