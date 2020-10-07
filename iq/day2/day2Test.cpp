#include "mu_test.h"
#include <vector>

#include "findSpecificElement.hpp"
#include "firstDuplicateT.hpp"
using namespace iq;
using namespace std;

BEGIN_TEST(test_find_specific_element_exist)
    int numbers[] = {1, 3, 4, 2, 7, 4, 9, 3};

    ASSERT_THAT(DoesContainElement(numbers, sizeof(numbers)/sizeof(numbers[0]), 9));
END_TEST

BEGIN_TEST(test_find_specific_element_not_exist)
    int numbers[] = {1, 3, 4, 2, 7, 8, 9, 6};

    ASSERT_THAT(!DoesContainElement(numbers, sizeof(numbers)/sizeof(numbers[0]), 5));
END_TEST

BEGIN_TEST(test_first_duplicate_T_in_vector)
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(-2);
    vec.push_back(5);
    vec.push_back(8);
    vec.push_back(-2);
    vec.push_back(7);
    vec.push_back(1);
    vec.push_back(8);
    
    int result;

    ASSERT_THAT(FindDuplicateElement<vector<int> >(vec, result));
    ASSERT_EQUAL(1, result);
END_TEST

BEGIN_SUITE(test_day2)
    TEST(test_find_specific_element_exist)
    TEST(test_find_specific_element_not_exist)

    TEST(test_first_duplicate_T_in_vector)
END_SUITE