#include "mu_test.h"

#include "firstNotUnique.hpp"
using namespace iq;

BEGIN_TEST(test_first_not_unique_O_n_n)
    int arr[] = {1, 3, 4, 2, 7, 4, 9, 3};

    int result;
    ASSERT_THAT(FindElementODoubleN(arr, sizeof(arr)/sizeof(arr[0]), result));
    ASSERT_EQUAL(3, result);
END_TEST

BEGIN_TEST(test_first_not_unique_null_arr_O_n_n)
    int result = 0;
    ASSERT_THAT(!FindElementODoubleN(0, 5, result));
    ASSERT_EQUAL(0, result);
END_TEST

BEGIN_TEST(test_first_not_unique_all_unique_O_n_n)
    int arr[] = {1, 3, 4, 2, 7, 5, 9, 11};

    int result = 0;
    ASSERT_THAT(!FindElementODoubleN(arr, sizeof(arr)/sizeof(arr[0]), result));
    ASSERT_EQUAL(0, result);
END_TEST

BEGIN_TEST(test_first_not_unique_only_positive_values_O_n)
    int arr[] = {1, 3, 4, 2, 7, 4, 9, 3};

    int result;
    ASSERT_THAT(FindElementOOneN(arr, sizeof(arr)/sizeof(arr[0]), result));
    ASSERT_EQUAL(3, result);
END_TEST

BEGIN_TEST(test_first_not_unique_only_negative_values_O_n)
    int arr[] = {-3, -4, -2, -1, -5, -7, -9, -1, -7};

    int result;
    ASSERT_THAT(FindElementOOneN(arr, sizeof(arr)/sizeof(arr[0]), result));
    ASSERT_EQUAL(-1, result);
END_TEST

BEGIN_TEST(test_first_not_unique_negative_and_positive_values_O_n)
    int arr[] = {-3, 4, 2, 1, 4, 1, 7, 9, 4};

    int result;
    ASSERT_THAT(FindElementOOneN(arr, sizeof(arr)/sizeof(arr[0]), result));
    ASSERT_EQUAL(4, result);
END_TEST

BEGIN_SUITE(test_first_not_unique)
    TEST(test_first_not_unique_O_n_n)
    TEST(test_first_not_unique_null_arr_O_n_n)
    TEST(test_first_not_unique_all_unique_O_n_n)

    TEST(test_first_not_unique_only_positive_values_O_n)
    TEST(test_first_not_unique_only_negative_values_O_n)
    TEST(test_first_not_unique_negative_and_positive_values_O_n)
END_SUITE
