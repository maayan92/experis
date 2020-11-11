#include "mu_test.h"

#include "list.hpp"
using namespace iq;

static void FreeList(Node* result)
{
    if(!result) {
        return;
    }

    FreeList(result->m_next);
    delete result;
}

//Q1:

BEGIN_TEST(test_remove_duplicates)
    Node node5(1);
    Node node4(2, &node5);
    Node node3(3, &node4);
    Node node2(7, &node3);
    Node node1(3, &node2);
    Node head(1, &node1);

    ASSERT_THAT(RemoveDuplicates(&head));

    int wantedValues[] = {1, 3, 7, 2};
    Node* check = &head;
    size_t i = 0;

    while(check) {
        ASSERT_EQUAL(wantedValues[i], check->m_data);
        check = check->m_next;
        ++i;
    }

END_TEST

BEGIN_TEST(test_remove_duplicates_no_duplicates)
    Node node5(9);
    Node node4(2, &node5);
    Node node3(4, &node4);
    Node node2(7, &node3);
    Node node1(3, &node2);
    Node head(1, &node1);

    ASSERT_THAT(RemoveDuplicates(&head));

    int wantedValues[] = {1, 3, 7, 4, 2, 9};
    Node* check = &head;
    size_t i = 0;

    while(check) {
        ASSERT_EQUAL(wantedValues[i], check->m_data);
        check = check->m_next;
        ++i;
    }

END_TEST

//Q2:

BEGIN_TEST(test_return_Kth_to_last)
    Node node5(9);
    Node node4(2, &node5);
    Node node3(4, &node4);
    Node node2(7, &node3);
    Node node1(3, &node2);
    Node head(1, &node1);

    Node* result = ReturnKthToLast(&head, 3);
    ASSERT_EQUAL(result, &node3);
    ASSERT_EQUAL(result->m_data, node3.m_data);
END_TEST

BEGIN_TEST(test_return_Kth_to_last_null_list)
    Node* result = ReturnKthToLast(0, 3);
    ASSERT_EQUAL(result, 0);
END_TEST

//Q3:

BEGIN_TEST(test_delete_middle_node)
    Node node5(9);
    Node node4(2, &node5);
    Node node3(4, &node4);
    Node node2(7, &node3);
    Node node1(3, &node2);
    Node head(1, &node1);

    ASSERT_THAT(DeleteMiddleNode(&node2));

    int result[] = {1, 3, 4, 2, 9};
    size_t i = 0;
    Node* node = &head;

    while(node) {
        ASSERT_EQUAL(result[i++], node->m_data);
        node = node->m_next;
    }
END_TEST

BEGIN_TEST(test_delete_middle_node_null_list)
    ASSERT_THAT(!DeleteMiddleNode(0));
END_TEST

//Q4:

BEGIN_TEST(test_partition_first_smaller)
    Node node6(1);
    Node node5(2, &node6);
    Node node4(10, &node5);
    Node node3(5, &node4);
    Node node2(8, &node3);
    Node node1(5, &node2);
    Node head(3, &node1);
    Node* headPtr = &head;

    ASSERT_THAT(Partition(headPtr, 5));
    
    int result[] = {3, 1, 2, 5, 8, 5, 10};
    size_t i = 0;
    Node* node = headPtr;

    while(node) {
        ASSERT_EQUAL(result[i++], node->m_data);
        node = node->m_next;
    }
END_TEST

BEGIN_TEST(test_partition_first_bigger)
    Node node6(1);
    Node node5(2, &node6);
    Node node4(10, &node5);
    Node node3(5, &node4);
    Node node2(8, &node3);
    Node node1(5, &node2);
    Node head(4, &node1);
    Node* headPtr = &head;

    ASSERT_THAT(Partition(headPtr, 5));
    
    int result[] = {4, 1, 2, 5, 8, 5, 10};
    size_t i = 0;
    Node* node = headPtr;

    while(node) {
        ASSERT_EQUAL(result[i++], node->m_data);
        node = node->m_next;
    }
END_TEST

BEGIN_TEST(test_partition_all_bigger)
    Node node6(7);
    Node node5(2, &node6);
    Node node4(10, &node5);
    Node node3(5, &node4);
    Node node2(8, &node3);
    Node node1(5, &node2);
    Node head(3, &node1);
    Node* headPtr = &head;

    ASSERT_THAT(Partition(headPtr, 1));
    
    int result[] = {5, 8, 5, 10, 2, 7, 3};
    size_t i = 0;
    Node* node = headPtr;

    while(node) {
        ASSERT_EQUAL(result[i++], node->m_data);
        node = node->m_next;
    }
END_TEST

BEGIN_TEST(test_partition_all_smaller)
    Node node6(7);
    Node node5(2, &node6);
    Node node4(10, &node5);
    Node node3(5, &node4);
    Node node2(8, &node3);
    Node node1(5, &node2);
    Node head(3, &node1);
    Node* headPtr = &head;

    ASSERT_THAT(Partition(headPtr, 12));
    
    int result[] = {3, 7, 2, 10, 5, 8, 5};
    size_t i = 0;
    Node* node = headPtr;

    while(node) {
        ASSERT_EQUAL(result[i++], node->m_data);
        node = node->m_next;
    }
END_TEST

BEGIN_TEST(test_partition_null_list)
    Node* head = 0;
    ASSERT_THAT(!Partition(head, 12));
END_TEST

//Q5:

BEGIN_TEST(test_sum_lists)
    Node node2F(9);
    Node node1F(5, &node2F);
    Node headF(1, &node1F);

    Node node3S(7);
    Node node2S(6, &node3S);
    Node node1S(3, &node2S);
    Node headS(2, &node1S);

    Node* result = SumLists(&headF, &headS);
    ASSERT_THAT(result);
    
    int resultArr[] = {3, 8, 5, 8};
    size_t i = 0;

    while(result) {
        ASSERT_EQUAL(resultArr[i++], result->m_data);
        result = result->m_next;
    }

    FreeList(result);
END_TEST

BEGIN_TEST(test_sum_lists_recursion)
    Node node2F(9);
    Node node1F(5, &node2F);
    Node headF(1, &node1F);

    Node node3S(7);
    Node node2S(6, &node3S);
    Node node1S(3, &node2S);
    Node headS(2, &node1S);

    Node* result = SumListsRecursion(&headF, &headS);
    ASSERT_THAT(result);
    
    int resultArr[] = {3, 8, 5, 8};
    size_t i = 0;

    while(result) {
        ASSERT_EQUAL(resultArr[i++], result->m_data);
        result = result->m_next;
    }

    FreeList(result);
END_TEST

BEGIN_TEST(test_sum_lists_recursion_bigger_result)
    Node node2F(9);
    Node node1F(5, &node2F);
    Node headF(1, &node1F);

    Node node3S(9);
    Node node2S(6, &node3S);
    Node node1S(3, &node2S);
    Node headS(2, &node1S);

    Node* result = SumListsRecursion(&headF, &headS);
    ASSERT_THAT(result);
    
    int resultArr[] = {3, 8, 5, 0, 1};
    size_t i = 0;

    while(result) {
        ASSERT_EQUAL(resultArr[i++], result->m_data);
        result = result->m_next;
    }

    FreeList(result);
END_TEST

BEGIN_SUITE(test_list)
    TEST(test_remove_duplicates)
    TEST(test_remove_duplicates_no_duplicates)

    TEST(test_return_Kth_to_last)
    TEST(test_return_Kth_to_last_null_list)

    TEST(test_delete_middle_node)
    TEST(test_delete_middle_node_null_list)

    TEST(test_partition_first_smaller)
    TEST(test_partition_first_bigger)
    TEST(test_partition_all_bigger)
    TEST(test_partition_all_smaller)
    TEST(test_partition_null_list)

    TEST(test_sum_lists)
    TEST(test_sum_lists_recursion)
    TEST(test_sum_lists_recursion_bigger_result)
END_SUITE