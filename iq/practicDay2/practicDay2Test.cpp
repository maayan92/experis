#include "mu_test.h"

#include "practicDay2.hpp"
using namespace std;
using namespace iq;

static void FreeNodes(Node* a_head)
{
    if(!a_head) {
        return;
    }

    FreeNodes(a_head->m_next);
    delete a_head;
}

// Q1:

BEGIN_TEST(test_merge_lists_naive)
    Node node1(19);
    Node node2(13, &node1);
    Node node3(10, &node2);
    Node head1(5, &node3);

    Node node4(7);
    Node head2(2, &node4);

    Node node5(16);
    Node node6(9, &node5);
    Node head3(6, &node6);

    Node node7(12);
    Node node8(4, &node7);
    Node head4(3, &node8);
    
    const Node* lists[] = { &head1, &head2, &head3, &head4 };
    
    Node* result = MergeListsNaive(lists, sizeof(lists)/sizeof(lists[0]));
    ASSERT_THAT(result);

    int wantedResult[] = { 2, 3, 4, 5, 6, 7, 9, 10, 12, 13, 16, 19};

    size_t size = sizeof(wantedResult)/sizeof(wantedResult[0]);
    for(size_t i = 0; i < size; ++i) {
        ASSERT_EQUAL(result->m_data, wantedResult[i]);
        result = result->m_next;
    }

    FreeNodes(result);
END_TEST

BEGIN_TEST(test_merge_lists)
    Node node1(19);
    Node node2(13, &node1);
    Node node3(10, &node2);
    Node head1(5, &node3);

    Node node4(7);
    Node head2(2, &node4);

    Node node5(16);
    Node node6(9, &node5);
    Node head3(6, &node6);

    Node node7(12);
    Node node8(4, &node7);
    Node head4(3, &node8);
    
    const Node* lists[] = { &head1, &head2, &head3, &head4 };
    
    Node* result = MergeLists(lists, sizeof(lists)/sizeof(lists[0]));
    ASSERT_THAT(result);

    int wantedResult[] = { 2, 3, 4, 5, 6, 7, 9, 10, 12, 13, 16, 19};

    size_t size = sizeof(wantedResult)/sizeof(wantedResult[0]);
    for(size_t i = 0; i < size; ++i) {
        ASSERT_EQUAL(result->m_data, wantedResult[i]);
        result = result->m_next;
    }

    FreeNodes(result);
END_TEST

BEGIN_TEST(test_merge_lists_null_lists)
    const Node* lists[] = { 0, 0, 0, 0 };

    Node* result = MergeLists(lists, sizeof(lists)/sizeof(lists[0]));
    ASSERT_THAT(!result);
END_TEST

// Q2:

BEGIN_TEST(test_sort_array_012)
    size_t arr012[] = { 2, 0, 1, 1, 0, 2, 0, 0, 2, 2, 1, 2, 0, 2, 2 };

    size_t size = sizeof(arr012)/sizeof(arr012[0]);
    ASSERT_THAT(SortArray012(arr012, size));

    size_t wantedResult[] = { 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2 };
    for(size_t i = 0; i < size; ++i) {
        ASSERT_EQUAL(arr012[i], wantedResult[i]);
    }
END_TEST

BEGIN_TEST(test_sort_array_012_null_array)
    ASSERT_THAT(!SortArray012(0, 5));
END_TEST

// Q3:

BEGIN_TEST(test_best_flip_pos_for_one_seq_two_in_a_row)
    size_t arr012[] = { 2, 0, 1, 1, 0, 1, 1, 1, 2, 1, 1, 1, 1, 2, 2 };

    size_t size = sizeof(arr012)/sizeof(arr012[0]);
    size_t pos;
    ASSERT_THAT(BestFlipPosForOneSeq(arr012, size, pos));

    ASSERT_EQUAL(8, pos);
END_TEST

BEGIN_TEST(test_best_flip_pos_for_one_seq)
    size_t arr012[] = { 2, 0, 1, 1, 0, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2 };

    size_t size = sizeof(arr012)/sizeof(arr012[0]);
    size_t pos;
    ASSERT_THAT(BestFlipPosForOneSeq(arr012, size, pos));

    ASSERT_EQUAL(4, pos);
END_TEST

BEGIN_TEST(test_best_flip_pos_for_one_seq_all_ones)
    size_t arr012[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    size_t size = sizeof(arr012)/sizeof(arr012[0]);
    size_t pos = 50;
    ASSERT_THAT(!BestFlipPosForOneSeq(arr012, size, pos));
END_TEST

BEGIN_TEST(test_best_flip_pos_for_one_seq_non_ones)
    size_t arr012[] = { 2, 0, 0, 2, 2, 0, 0, 0, 2, 0, 2 };

    size_t size = sizeof(arr012)/sizeof(arr012[0]);
    size_t pos = 50;
    ASSERT_THAT(BestFlipPosForOneSeq(arr012, size, pos));

    ASSERT_EQUAL(0, pos);
END_TEST

BEGIN_TEST(test_best_flip_pos_for_one_seq_null_array)
    size_t pos = 50;
    ASSERT_THAT(!BestFlipPosForOneSeq(0, 5, pos));

    ASSERT_EQUAL(50, pos);
END_TEST

// Q4:

BEGIN_TEST(test_count_one_pairs_unsigned_long)
    unsigned long number = 26787754;

    size_t count;
    ASSERT_THAT(CountOnePairs(number, count));

    ASSERT_EQUAL(8, count);
END_TEST

BEGIN_TEST(test_count_one_pairs_array)
    size_t bits[] = { 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 };

    size_t size = sizeof(bits)/sizeof(bits[0]);
    size_t count;
    ASSERT_THAT(CountOnePairs(bits, size, count));

    ASSERT_EQUAL(5, count);
END_TEST

BEGIN_TEST(test_count_one_pairs_array_no_one_pairs)
    size_t bits[] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1 };

    size_t size = sizeof(bits)/sizeof(bits[0]);
    size_t count;
    ASSERT_THAT(CountOnePairs(bits, size, count));

    ASSERT_EQUAL(0, count);
END_TEST

BEGIN_TEST(test_count_one_pairs_array_all_ones)
    size_t bits[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    size_t size = sizeof(bits)/sizeof(bits[0]);
    size_t count;
    ASSERT_THAT(CountOnePairs(bits, size, count));

    ASSERT_EQUAL(8, count);
END_TEST

BEGIN_TEST(test_count_one_pairs_array_all_zero)
    size_t bits[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

    size_t size = sizeof(bits)/sizeof(bits[0]);
    size_t count;
    ASSERT_THAT(CountOnePairs(bits, size, count));

    ASSERT_EQUAL(0, count);
END_TEST

BEGIN_TEST(test_longest_branch_length)
    Tree tree1(7);
    Tree tree2(4, vector<Tree*>(1, &tree1));
    Tree tree3(9);
    Tree tree4(3);

    Tree* arr[] = { &tree2, &tree3, &tree4 };
    Tree tree5(10, vector<Tree*>(arr, arr + 3));

    Tree tree6(13);
    Tree* arr2[] = { &tree5, &tree6 };
    Tree tree7(5, vector<Tree*>(arr2, arr2 + 2));

    Tree tree8(1);
    Tree tree9(3, vector<Tree*>(1, &tree8));

    Tree tree10(8);
    Tree tree11(7, vector<Tree*>(1, &tree10));

    Tree* arr3[] = { &tree7, &tree9, &tree11 };
    Tree head(8, vector<Tree*>(arr3, arr3 + 3));

    size_t length = 0;
    ASSERT_THAT(LongestBranchLength(&head, length));
    ASSERT_EQUAL(5, length);
END_TEST

BEGIN_TEST(test_longest_branch_length_with_duplicate)
    Tree tree1(8);
    Tree tree2(5, vector<Tree*>(1, &tree1));
    Tree tree3(9);
    Tree tree4(3);

    Tree* arr[] = { &tree2, &tree3, &tree4 };
    Tree tree5(10, vector<Tree*>(arr, arr + 3));

    Tree tree6(13);
    Tree* arr2[] = { &tree5, &tree6 };
    Tree tree7(5, vector<Tree*>(arr2, arr2 + 2));

    Tree tree8(1);
    Tree tree9(3, vector<Tree*>(1, &tree8));

    Tree tree10(8);
    Tree tree11(7, vector<Tree*>(1, &tree10));

    Tree* arr3[] = { &tree7, &tree9, &tree11 };
    Tree head(8, vector<Tree*>(arr3, arr3 + 3));

    size_t length = 0;
    ASSERT_THAT(LongestBranchLength(&head, length));
    ASSERT_EQUAL(4, length);
END_TEST

BEGIN_SUITE(test_practic_day_2)
    TEST(test_merge_lists_naive)
    TEST(test_merge_lists)
    TEST(test_merge_lists_null_lists)

    TEST(test_sort_array_012)
    TEST(test_sort_array_012_null_array)

    TEST(test_best_flip_pos_for_one_seq_two_in_a_row)
    TEST(test_best_flip_pos_for_one_seq)
    TEST(test_best_flip_pos_for_one_seq_all_ones)
    TEST(test_best_flip_pos_for_one_seq_non_ones)
    TEST(test_best_flip_pos_for_one_seq_null_array)

    TEST(test_count_one_pairs_unsigned_long)
    TEST(test_count_one_pairs_array)
    TEST(test_count_one_pairs_array_no_one_pairs)
    TEST(test_count_one_pairs_array_all_ones)
    TEST(test_count_one_pairs_array_all_zero)

    TEST(test_longest_branch_length)
    TEST(test_longest_branch_length_with_duplicate)
END_SUITE