#include "mu_test.h"

#include "practiceDay5.hpp"
using namespace std;
using namespace iq;

BEGIN_TEST(test_string_to_double)
    const char* str = "12.67";

    double result;
    ASSERT_THAT(StringToDouble(str, result));
    ASSERT_EQUAL(12.67, result);
END_TEST

BEGIN_TEST(test_string_to_double_negative)
    const char* str = "-34.1324";

    double result;
    ASSERT_THAT(StringToDouble(str, result));
    ASSERT_EQUAL(-34.1324, result);
END_TEST

BEGIN_TEST(test_string_to_double_with_zeros)
    const char* str = "00034.20000";

    double result;
    ASSERT_THAT(StringToDouble(str, result));
    ASSERT_EQUAL(34.2, result);
END_TEST

BEGIN_TEST(test_string_to_double_with_letters)
    const char* str = "3.2abc2";

    double result;
    ASSERT_THAT(!StringToDouble(str, result));
    ASSERT_EQUAL(3.2, result);
END_TEST

BEGIN_SUITE(test_practice_day_5)
    TEST(test_string_to_double)
    TEST(test_string_to_double_negative)
    TEST(test_string_to_double_with_zeros)
    TEST(test_string_to_double_with_letters)
END_SUITE