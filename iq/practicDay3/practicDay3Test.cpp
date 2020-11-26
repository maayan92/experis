#include "mu_test.h"

#include "practicDay3.hpp"
using namespace std;
using namespace iq;

// Q3:

/*
BEGIN_TEST(test_reverse_specified_portion)
    forward_list<int> list = { 1, 7, 8, 3, 9, 1, 2 };
    
    ASSERT_THAT(ReverseSpecifiedPortion(list, 2, 5));
    
    int wantedResult[] = { 1, 9, 3, 8, 7, 1, 2 };
    size_t i = 0;
    auto itr = list.begin();
    auto end = list.end();

    for(; itr != end; ++itr) {
        ASSERT_EQUAL(*itr, wantedResult[i]);
        ++i;
    }
END_TEST
*/
BEGIN_TEST(test_reverse_specified_portion)
    Node node6(2);
    Node node5(1, &node6);
    Node node4(9, &node5);
    Node node3(3, &node4);
    Node node2(8, &node3);
    Node node1(7, &node2);
    Node head(1, &node1);
    Node* headCopy = &head;
    
    ASSERT_THAT(ReverseSpecifiedPortion(headCopy, 2, 5));
    
    int wantedResult[] = { 1, 9, 3, 8, 7, 1, 2 };

    size_t i = 0;
    Node* node = &head;
    while(node) {
        ASSERT_EQUAL(node->m_data, wantedResult[i]);
        node = node->m_next;
        ++i;
    }
END_TEST

BEGIN_TEST(test_reverse_specified_portion_one_distance)
    Node node6(2);
    Node node5(1, &node6);
    Node node4(9, &node5);
    Node node3(3, &node4);
    Node node2(8, &node3);
    Node node1(7, &node2);
    Node head(1, &node1);
    Node* headCopy = &head;
    
    ASSERT_THAT(ReverseSpecifiedPortion(headCopy, 3, 4));
    
    int wantedResult[] = { 1, 7, 3, 8, 9, 1, 2 };

    size_t i = 0;
    Node* node = &head;
    while(node) {
        ASSERT_EQUAL(node->m_data, wantedResult[i]);
        node = node->m_next;
        ++i;
    }
END_TEST

BEGIN_TEST(test_reverse_specified_portion_to_after_end)
    Node node6(2);
    Node node5(1, &node6);
    Node node4(9, &node5);
    Node node3(3, &node4);
    Node node2(8, &node3);
    Node node1(7, &node2);
    Node head(1, &node1);
    Node* headCopy = &head;
    
    ASSERT_THAT(ReverseSpecifiedPortion(headCopy, 3, 10));
    
    int wantedResult[] = { 1, 7, 2, 1, 9, 3, 8 };

    size_t i = 0;
    Node* node = &head;
    while(node) {
        ASSERT_EQUAL(node->m_data, wantedResult[i]);
        node = node->m_next;
        ++i;
    }
END_TEST

BEGIN_TEST(test_reverse_specified_portion_from_start)
    Node node6(2);
    Node node5(1, &node6);
    Node node4(9, &node5);
    Node node3(3, &node4);
    Node node2(8, &node3);
    Node node1(7, &node2);
    Node head(1, &node1);
    Node* headCopy = &head;
    
    ASSERT_THAT(ReverseSpecifiedPortion(headCopy, 1, 3));
    
    int wantedResult[] = { 8, 7, 1, 3, 9, 1, 2 };

    size_t i = 0;
    Node* node = headCopy;
    while(node) {
        ASSERT_EQUAL(node->m_data, wantedResult[i]);
        node = node->m_next;
        ++i;
    }
END_TEST

// Q2:

BEGIN_TEST(test_K_smallest_value)
    int mat[][COLUMNS] = { { 1, 3, 5, 8, 10 },
                            { 8, 12, 15, 20, 23 } ,
                            { 2, 9, 11, 15, 17} ,
                            { 1, 7, 8, 11, 20 } };
    int result;
    ASSERT_THAT(KSmallestValue(mat, sizeof(mat)/sizeof(mat[0]), 6, result));
    ASSERT_EQUAL(7, result);
END_TEST

BEGIN_TEST(test_K_smallest_value_fully_sorted)
    int mat[][COLUMNS] = { { 1, 3, 5, 8, 10 },
                            { 11, 12, 15, 20, 23 } ,
                            { 25, 29, 31, 35, 37} ,
                            { 41, 47, 48, 51, 60 } };
    int result;
    ASSERT_THAT(KSmallestValue(mat, sizeof(mat)/sizeof(mat[0]), 15, result));
    ASSERT_EQUAL(37, result);
END_TEST

BEGIN_TEST(test_K_smallest_value_null)
    int result;
    ASSERT_THAT(!KSmallestValue(0, 0, 15, result));
END_TEST

BEGIN_TEST(test_K_smallest_value_K_too_big)
    int mat[][COLUMNS] = { { 1, 3, 5, 8, 10 },
                            { 8, 12, 15, 20, 23 } ,
                            { 2, 9, 11, 15, 17} ,
                            { 1, 7, 8, 11, 20 } };
    int result = 0;
    ASSERT_THAT(!KSmallestValue(mat, sizeof(mat)/sizeof(mat[0]), 26, result));
    ASSERT_EQUAL(0, result);
END_TEST

// Q4:

BEGIN_TEST(test_convert_binary_tree_to_DLL_small_tree)
    BTree node5(7);
    BTree node4(26);
    BTree node3(-4);
    BTree node2(13, &node4, &node5);
    BTree node1(8, &node3, 0);
    BTree head(1, &node1, &node2);

    list<int> result;
    ASSERT_THAT(ConvertBTtoDLL(&head, result));

    int wantedResult[] = { 1, 8, 13, 7, 26, -4 };

    size_t i = 0;
    auto itr = result.begin();
    auto end = result.end();

    while(itr != end) {
        ASSERT_EQUAL(*itr, wantedResult[i]);
        ++itr;
        ++i;
    }
END_TEST

BEGIN_TEST(test_convert_binary_tree_to_DLL_big_tree)
    BTree node13(14);
    BTree node12(13);
    BTree node11(12);
    BTree node10(11);
    BTree node9(10);
    BTree node8(9);
    BTree node7(8);
    BTree node6(7, &node12, &node13);
    BTree node5(6, &node10, &node11);
    BTree node4(5, &node9, 0);
    BTree node3(4, &node7, &node8);
    BTree node2(3, &node5, &node6);
    BTree node1(2, &node3, &node4);
    BTree head(1, &node1, &node2);

    list<int> result;
    ASSERT_THAT(ConvertBTtoDLL(&head, result));

    int wantedResult[] = { 1, 2, 3, 7, 6, 5, 4, 8, 9, 10, 11, 12, 13, 14 };

    size_t i = 0;
    auto itr = result.begin();
    auto end = result.end();

    while(itr != end) {
        ASSERT_EQUAL(*itr, wantedResult[i]);
        ++itr;
        ++i;
    }
END_TEST

BEGIN_TEST(test_convert_binary_tree_to_DLL_null_tree)
    list<int> result;
    ASSERT_THAT(!ConvertBTtoDLL(0, result));
    ASSERT_EQUAL(0, result.size());
END_TEST

// Q5:

BEGIN_TEST(test_max_branch_multiplying_all_positive)
    BTree node7(2);
    BTree node6(1);
    BTree node5(6);
    BTree node4(2, &node6, &node7);
    BTree node3(4);
    BTree node2(3, &node4, &node5);
    BTree node1(8, &node3, 0);
    BTree head(1, &node1, &node2);

    int result = MaxBranchMultiplying(&head);
    ASSERT_EQUAL(32, result);
END_TEST

BEGIN_TEST(test_max_branch_multiplying_with_negative)
    BTree node5(6);
    BTree node4(2);
    BTree node3(-4);
    BTree node2(3, &node4, &node5);
    BTree node1(8, &node3, 0);
    BTree head(1, &node1, &node2);

    int result = MaxBranchMultiplying(&head);
    ASSERT_EQUAL(18, result);
END_TEST

BEGIN_TEST(test_max_branch_multiplying_null_tree)
    int result = MaxBranchMultiplying(0);
    ASSERT_EQUAL(0, result);
END_TEST

// Q6:

BEGIN_TEST(test_is_binary_tree_a_heap_min_true)
    BTree node5(26);
    BTree node4(12);
    BTree node3(14);
    BTree node2(13, &node5, 0);
    BTree node1(8, &node3, &node4);
    BTree head(1, &node1, &node2);

    ASSERT_THAT(IsBTreeHeapMin(&head));
END_TEST

BEGIN_TEST(test_is_binary_tree_a_heap_min_not_complete)
    BTree node5(26);
    BTree node4(17);
    BTree node3(14);
    BTree node2(13, &node4, &node5);
    BTree node1(8, &node3, 0);
    BTree head(1, &node1, &node2);

    ASSERT_THAT(!IsBTreeHeapMin(&head));
END_TEST

BEGIN_TEST(test_is_binary_tree_a_heap_min_not_min)
    BTree node5(6);
    BTree node4(12);
    BTree node3(14);
    BTree node2(13, &node5, 0);
    BTree node1(8, &node3, &node4);
    BTree head(1, &node1, &node2);

    ASSERT_THAT(!IsBTreeHeapMin(&head));
END_TEST

BEGIN_TEST(test_is_binary_tree_a_heap_min_null_tree)
    ASSERT_THAT(!IsBTreeHeapMin(0));
END_TEST

// Q7:

BEGIN_TEST(test_get_values_in_specific_levels)
    BTree node13(24);
    BTree node12(33);
    BTree node11(22);
    BTree node10(19);
    BTree node9(13);
    BTree node8(29);
    BTree node7(18);
    BTree node6(27, &node12, &node13);
    BTree node5(11, &node10, &node11);
    BTree node4(15, &node9, 0);
    BTree node3(4, &node7, &node8);
    BTree node2(23, &node5, &node6);
    BTree node1(12, &node3, &node4);
    BTree head(8, &node1, &node2);

    vector<int> result;
    ASSERT_THAT(GetValuesInSpecificLevels(&head, 2, 3, result));

    int wantedResult[] = { 12, 4, 15, 23, 11, 27 };

    size_t i = 0;
    auto itr = result.begin();
    auto end = result.end();

    while(itr != end) {
        ASSERT_EQUAL(*itr, wantedResult[i]);
        ++itr;
        ++i;
    }
END_TEST

BEGIN_TEST(test_get_values_in_specific_levels_to_too_high)
    BTree node13(24);
    BTree node12(33);
    BTree node11(22);
    BTree node10(19);
    BTree node9(13);
    BTree node8(29);
    BTree node7(18);
    BTree node6(27, &node12, &node13);
    BTree node5(11, &node10, &node11);
    BTree node4(15, &node9, 0);
    BTree node3(4, &node7, &node8);
    BTree node2(23, &node5, &node6);
    BTree node1(12, &node3, &node4);
    BTree head(8, &node1, &node2);

    vector<int> result;
    ASSERT_THAT(GetValuesInSpecificLevels(&head, 2, 10, result));

    int wantedResult[] = { 12, 4, 18, 29, 15, 13, 23, 11, 19, 22, 27, 33, 24 };

    size_t i = 0;
    auto itr = result.begin();
    auto end = result.end();

    while(itr != end) {
        ASSERT_EQUAL(*itr, wantedResult[i]);
        ++itr;
        ++i;
    }
END_TEST

BEGIN_TEST(test_get_values_in_specific_levels_from_too_high)
    BTree node13(24);
    BTree node12(33);
    BTree node11(22);
    BTree node10(19);
    BTree node9(13);
    BTree node8(29);
    BTree node7(18);
    BTree node6(27, &node12, &node13);
    BTree node5(11, &node10, &node11);
    BTree node4(15, &node9, 0);
    BTree node3(4, &node7, &node8);
    BTree node2(23, &node5, &node6);
    BTree node1(12, &node3, &node4);
    BTree head(8, &node1, &node2);

    vector<int> result;
    ASSERT_THAT(!GetValuesInSpecificLevels(&head, 7, 10, result));
    ASSERT_THAT(result.empty());
END_TEST

BEGIN_TEST(test_get_values_in_specific_levels_from_bigger_then_to)
    BTree node13(24);
    BTree node12(33);
    BTree node11(22);
    BTree node10(19);
    BTree node9(13);
    BTree node8(29);
    BTree node7(18);
    BTree node6(27, &node12, &node13);
    BTree node5(11, &node10, &node11);
    BTree node4(15, &node9, 0);
    BTree node3(4, &node7, &node8);
    BTree node2(23, &node5, &node6);
    BTree node1(12, &node3, &node4);
    BTree head(8, &node1, &node2);

    vector<int> result;
    ASSERT_THAT(!GetValuesInSpecificLevels(&head, 4, 3, result));
    ASSERT_THAT(result.empty());
END_TEST

BEGIN_TEST(test_get_values_in_specific_levels_null_tree)
    vector<int> result;
    ASSERT_THAT(!GetValuesInSpecificLevels(0, 1, 3, result));
    ASSERT_THAT(result.empty());
END_TEST

// Q8:

BEGIN_TEST(test_difference_sum_odd_and_even)
    BTree node9(12);
    BTree node8(11);
    BTree node7(10);
    BTree node6(7);
    BTree node5(6, &node8, &node9);
    BTree node4(5, &node7, 0);
    BTree node3(4);
    BTree node2(3, &node5, &node6);
    BTree node1(2, &node3, &node4);
    BTree head(1, &node1, &node2);

    int result = DifferenceSumOddAndEven(&head);
    ASSERT_EQUAL(-15, result);
END_TEST

BEGIN_TEST(test_difference_sum_odd_and_even_null_tree)
    int result = DifferenceSumOddAndEven(0);
    ASSERT_EQUAL(0, result);
END_TEST

// Q9:

BEGIN_TEST(test_diagonal_sums)
    BTree node9(12);
    BTree node8(13);
    BTree node7(10);
    BTree node6(7);
    BTree node5(6, &node8, &node9);
    BTree node4(5, &node7, 0);
    BTree node3(4);
    BTree node2(3, &node5, &node6);
    BTree node1(2, &node3, &node4);
    BTree head(1, &node1, &node2);

    vector<int> result;
    ASSERT_THAT(DiagonalSums(&head, result));

    int wantedResult[] = { 11, 25, 27 };
    size_t size = result.size();
    for(size_t i = 0; i < size; ++i) {
        ASSERT_EQUAL(result[i], wantedResult[i]);
    }
END_TEST

BEGIN_TEST(test_diagonal_sums_null_tree)
    vector<int> result;
    ASSERT_THAT(!DiagonalSums(0, result));
    ASSERT_THAT(result.empty());
END_TEST

BEGIN_SUITE(test_practic_day_3)
    TEST(test_reverse_specified_portion)
    TEST(test_reverse_specified_portion_one_distance)
    TEST(test_reverse_specified_portion_to_after_end)
    TEST(test_reverse_specified_portion_from_start)

    TEST(test_K_smallest_value)
    TEST(test_K_smallest_value_fully_sorted)
    TEST(test_K_smallest_value_null)
    TEST(test_K_smallest_value_K_too_big)

    TEST(test_convert_binary_tree_to_DLL_small_tree)
    TEST(test_convert_binary_tree_to_DLL_big_tree)
    TEST(test_convert_binary_tree_to_DLL_null_tree)

    TEST(test_max_branch_multiplying_all_positive)
    TEST(test_max_branch_multiplying_with_negative)
    TEST(test_max_branch_multiplying_null_tree)

    TEST(test_is_binary_tree_a_heap_min_true)
    TEST(test_is_binary_tree_a_heap_min_not_complete)
    TEST(test_is_binary_tree_a_heap_min_not_min)
    TEST(test_is_binary_tree_a_heap_min_null_tree)

    TEST(test_get_values_in_specific_levels)
    TEST(test_get_values_in_specific_levels_to_too_high)
    TEST(test_get_values_in_specific_levels_from_too_high)
    TEST(test_get_values_in_specific_levels_from_bigger_then_to)
    TEST(test_get_values_in_specific_levels_null_tree)

    TEST(test_difference_sum_odd_and_even)
    TEST(test_difference_sum_odd_and_even_null_tree)

    TEST(test_diagonal_sums)
    TEST(test_diagonal_sums_null_tree)
END_SUITE