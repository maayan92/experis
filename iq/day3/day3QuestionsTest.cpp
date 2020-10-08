#include "mu_test.h"

#include "day3Questions.hpp"
using namespace iq;
using namespace std;

BEGIN_TEST(test_smallest_positive_not_present_naive)
    int numbers[] = {-7, 8, -2, 0, 8, 3, 9, 2, 1};

    int result;
    ASSERT_THAT(NaiveSmallestPositiveNotPresent(numbers, sizeof(numbers)/sizeof(numbers[0]), result));
    ASSERT_EQUAL(4, result);
END_TEST

BEGIN_TEST(test_smallest_positive_not_present_naive_sequence_array)
    int numbers[] = {7, 6, 4, 0, 8, 3, 5, 2, 1};

    int result;
    ASSERT_THAT(NaiveSmallestPositiveNotPresent(numbers, sizeof(numbers)/sizeof(numbers[0]), result));
    ASSERT_EQUAL(9, result);
END_TEST

BEGIN_TEST(test_smallest_positive_not_present)
    int numbers[] = {-7, 8, -2, 0, 8, 3, 9, 2, 1};

    int result;
    ASSERT_THAT(NaiveSmallestPositiveNotPresent(numbers, sizeof(numbers)/sizeof(numbers[0]), result));
    ASSERT_EQUAL(4, result);
END_TEST

BEGIN_TEST(test_smallest_positive_not_present_sequence_array)
    int numbers[] = {7, 6, 4, 0, 8, 3, 5, 2, 1};

    int result;
    ASSERT_THAT(NaiveSmallestPositiveNotPresent(numbers, sizeof(numbers)/sizeof(numbers[0]), result));
    ASSERT_EQUAL(9, result);
END_TEST

BEGIN_TEST(test_add_two_list_numbers)
    //number = 12345
    list<unsigned char> first{'5', '4', '3', '2', '1'};
    //number = 78592
    list<unsigned char> second{'2', '9', '5', '8', '7'};

    list<unsigned char> result = AddListNumbers(first, second);

    //number = 90937
    list<unsigned char> wantedResult{'7', '3', '9', '0', '9'};
    ASSERT_THAT(result == wantedResult);
END_TEST

BEGIN_TEST(test_add_two_list_numbers_different_size)
    //number = 12345
    list<unsigned char> first{'5', '4', '3', '2', '1'};
    //number = 578592
    list<unsigned char> second{'2', '9', '5', '8', '7', '5'};

    list<unsigned char> result = AddListNumbers(first, second);

    //number = 90937
    list<unsigned char> wantedResult{'7', '3', '9', '0', '9', '5'};
    ASSERT_THAT(result == wantedResult);
END_TEST

BEGIN_TEST(test_add_two_list_numbers_result_with_bigger_size)
    //number = 58745
    list<unsigned char> first{'5', '4', '7', '8', '5'};
    //number = 78592
    list<unsigned char> second{'2', '9', '5', '8', '7'};

    list<unsigned char> result = AddListNumbers(first, second);

    //number = 137337
    list<unsigned char> wantedResult{'7', '3', '3', '7', '3', '1'};
    ASSERT_THAT(result == wantedResult);
END_TEST

BEGIN_TEST(test_add_two_list_numbers_different_size_and_result_bigger)
    //number = 58745
    list<unsigned char> first{'5', '4', '7', '8', '5'};
    //number = 99978592
    list<unsigned char> second{'2', '9', '5', '8', '7', '9', '9', '9'};

    list<unsigned char> result = AddListNumbers(first, second);

    //number = 100037337
    list<unsigned char> wantedResult{'7', '3', '3', '7', '3', '0', '0', '0', '1'};
    ASSERT_THAT(result == wantedResult);
END_TEST

BEGIN_TEST(test_add_two_list_numbers_tail_LSD)
    //number = 12345
    list<unsigned char> first{'1', '2', '3', '4', '5'};
    //number = 78592
    list<unsigned char> second{'7', '8', '5', '9', '2'};

    list<unsigned char> result = AddListNumbersTailLSD(first, second);

    //number = 90937
    list<unsigned char> wantedResult{'9', '0', '9', '3', '7'};
    ASSERT_THAT(result == wantedResult);
END_TEST

BEGIN_TEST(test_add_two_list_numbers_different_size_tail_LSD)
    //number = 12345
    list<unsigned char> first{'1', '2', '3', '4', '5'};
    //number = 578592
    list<unsigned char> second{'5', '7', '8', '5', '9', '2'};

    list<unsigned char> result = AddListNumbersTailLSD(first, second);

    //number = 90937
    list<unsigned char> wantedResult{'5', '9', '0', '9', '3', '7'};
    ASSERT_THAT(result == wantedResult);
END_TEST

BEGIN_TEST(test_add_two_list_numbers_result_with_bigger_size_tail_LSD)
    //number = 58745
    list<unsigned char> first{'5', '8', '7', '4', '5'};
    //number = 78592
    list<unsigned char> second{'7', '8', '5', '9', '2'};

    list<unsigned char> result = AddListNumbersTailLSD(first, second);

    //number = 137337
    list<unsigned char> wantedResult{'1', '3', '7', '3', '3', '7'};
    ASSERT_THAT(result == wantedResult);
END_TEST

BEGIN_TEST(test_add_two_list_numbers_different_size_and_result_bigger_tail_LSD)
    //number = 58745
    list<unsigned char> first{'5', '8', '7', '4', '5'};
    //number = 99978592
    list<unsigned char> second{'9', '9', '9', '7', '8', '5', '9', '2'};

    list<unsigned char> result = AddListNumbersTailLSD(first, second);

    //number = 100037337
    list<unsigned char> wantedResult{'1', '0', '0', '0', '3', '7', '3', '3', '7'};
    ASSERT_THAT(result == wantedResult);
END_TEST

BEGIN_TEST(test_add_two_list_numbers_reverse)
    //number = 12345
    list<unsigned char> first{'1', '2', '3', '4', '5'};
    //number = 78592
    list<unsigned char> second{'7', '8', '5', '9', '2'};

    list<unsigned char> result = AddListNumbersReverse(first, second);

    //number = 90937
    list<unsigned char> wantedResult{'9', '0', '9', '3', '7'};
    ASSERT_THAT(result == wantedResult);
END_TEST

BEGIN_TEST(test_add_two_list_numbers_different_size_reverse)
    //number = 12345
    list<unsigned char> first{'1', '2', '3', '4', '5'};
    //number = 578592
    list<unsigned char> second{'5', '7', '8', '5', '9', '2'};

    list<unsigned char> result = AddListNumbersReverse(first, second);

    //number = 90937
    list<unsigned char> wantedResult{'5', '9', '0', '9', '3', '7'};
    ASSERT_THAT(result == wantedResult);
END_TEST

BEGIN_TEST(test_add_two_list_numbers_result_with_bigger_size_reverse)
    //number = 58745
    list<unsigned char> first{'5', '8', '7', '4', '5'};
    //number = 78592
    list<unsigned char> second{'7', '8', '5', '9', '2'};

    list<unsigned char> result = AddListNumbersReverse(first, second);

    //number = 137337
    list<unsigned char> wantedResult{'1', '3', '7', '3', '3', '7'};
    ASSERT_THAT(result == wantedResult);
END_TEST

BEGIN_TEST(test_add_two_list_numbers_different_size_and_result_bigger_reverse)
    //number = 58745
    list<unsigned char> first{'5', '8', '7', '4', '5'};
    //number = 99978592
    list<unsigned char> second{'9', '9', '9', '7', '8', '5', '9', '2'};

    list<unsigned char> result = AddListNumbersReverse(first, second);

    //number = 100037337
    list<unsigned char> wantedResult{'1', '0', '0', '0', '3', '7', '3', '3', '7'};
    ASSERT_THAT(result == wantedResult);
END_TEST

BEGIN_SUITE(test_day_3)
    TEST(test_smallest_positive_not_present_naive)
    TEST(test_smallest_positive_not_present_naive_sequence_array)

    TEST(test_smallest_positive_not_present)
    TEST(test_smallest_positive_not_present_sequence_array)

    TEST(test_add_two_list_numbers)
    TEST(test_add_two_list_numbers_different_size)
    TEST(test_add_two_list_numbers_result_with_bigger_size)
    TEST(test_add_two_list_numbers_different_size_and_result_bigger)

    TEST(test_add_two_list_numbers_tail_LSD)
    TEST(test_add_two_list_numbers_different_size_tail_LSD)
    TEST(test_add_two_list_numbers_result_with_bigger_size_tail_LSD)
    TEST(test_add_two_list_numbers_different_size_and_result_bigger_tail_LSD)
    
    TEST(test_add_two_list_numbers_reverse)
    TEST(test_add_two_list_numbers_different_size_reverse)
    TEST(test_add_two_list_numbers_result_with_bigger_size_reverse)
    TEST(test_add_two_list_numbers_different_size_and_result_bigger_reverse)
END_SUITE
