#include "mu_test.h"

#include "findSpecificElement.hpp"
//#include "firstDuplicateT.hpp"
using namespace iq;

BEGIN_TEST(test_find_specific_element_exist)
    int numbers[] = {1, 3, 4, 2, 7, 4, 9, 3};

    ASSERT_THAT(DoesContainElement(numbers, sizeof(numbers)/sizeof(numbers[0]), 9));
END_TEST

BEGIN_TEST(test_find_specific_element_not_exist)
    int numbers[] = {1, 3, 4, 2, 7, 8, 9, 6};

    ASSERT_THAT(!DoesContainElement(numbers, sizeof(numbers)/sizeof(numbers[0]), 5));
END_TEST

BEGIN_SUITE(test_day2)
    TEST(test_find_specific_element_exist)
    TEST(test_find_specific_element_not_exist)
END_SUITE