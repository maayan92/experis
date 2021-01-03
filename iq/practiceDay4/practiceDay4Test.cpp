#include "mu_test.h"

#include "practiceDay4.hpp"
using namespace iq;
using namespace std;

static bool CheckBTreeResultRec(BTree* a_head, int* a_result, size_t a_indx)
{
    if(!a_head) {
        return true;
    }

    return (a_head->m_data == a_result[a_indx]) &&
            CheckBTreeResultRec(a_head->m_left, a_result, 2*a_indx + 1) &&
            CheckBTreeResultRec(a_head->m_right, a_result, 2*a_indx + 2);
}

// tests:

// Q4:

BEGIN_TEST(test_rotate_matrix)
    int mat[][SIZE] = {{1 ,2, 3, 4, 5},
                        {6, 7, 8, 9, 10},
                        {11, 12, 13, 14, 15},
                        {16, 17, 18, 19, 20},
                        {21, 22, 23, 24, 25}};

    ASSERT_THAT(RotateMatrix(mat));

    int wantedResult[][SIZE] = {{21 ,16, 11, 6, 1},
                                {22, 17, 12, 7, 2},
                                {23, 18, 13, 8, 3},
                                {24, 19, 14, 9, 4},
                                {25, 20, 15, 10, 5}};

    for(size_t i = 0; i < SIZE; ++i) {
        for(size_t j = 0; j < SIZE; ++j) {
            ASSERT_EQUAL(mat[i][j], wantedResult[i][j]);
        }
    }
END_TEST

BEGIN_TEST(test_rotate_matrix_null_matrix)
    ASSERT_THAT(!RotateMatrix(0));
END_TEST

// Q5:

BEGIN_TEST(test_matrix_sub_sum)
    int mat[][Matrix::COLUMNS] = { { 11, 2, 1, 3, 6 },
                                  { 0, -4, 8, 2, -7 },
                                  { 3, 9, 10, 3, 12 },
                                  { 2, -3, 5, 4, -2 },
                                  { -7, 6, 11, 2, 9 },
                                  { 3, 5, 7, 6, -9 } };

    Matrix matClass(mat, sizeof(mat)/sizeof(mat[0]));
    int result;
    ASSERT_THAT(matClass.SubSum(0, 2, 3, 3, result));
    ASSERT_EQUAL(36, result);
    
    ASSERT_THAT(matClass.SubSum(1, 2, 3, 2, result));
    ASSERT_EQUAL(23, result);
END_TEST

BEGIN_TEST(test_matrix_sub_sum_to_row_at_the_end)
    int mat[][Matrix::COLUMNS] = { { 11, 2, 1, 3, 6 },
                                  { 0, -4, 8, 2, -7 },
                                  { 3, 9, 10, 3, 12 },
                                  { 2, -3, 5, 4, -2 },
                                  { -7, 6, 11, 2, 9 },
                                  { 3, 5, 7, 6, -9 } };

    Matrix matClass(mat, sizeof(mat)/sizeof(mat[0]));
    int result;
    ASSERT_THAT(matClass.SubSum(0, 2, 5, 3, result));
    ASSERT_EQUAL(62, result);
END_TEST

BEGIN_TEST(test_matrix_sub_sum_to_column_at_the_end)
    int mat[][Matrix::COLUMNS] = { { 11, 2, 1, 3, 6 },
                                  { 0, -4, 8, 2, -7 },
                                  { 3, 9, 10, 3, 12 },
                                  { 2, -3, 5, 4, -2 },
                                  { -7, 6, 11, 2, 9 },
                                  { 3, 5, 7, 6, -9 } };

    Matrix matClass(mat, sizeof(mat)/sizeof(mat[0]));
    int result;
    ASSERT_THAT(matClass.SubSum(0, 1, 3, 4, result));
    ASSERT_EQUAL(49, result);
END_TEST

BEGIN_TEST(test_matrix_sub_sum_to_row_and_column_at_the_end)
    int mat[][Matrix::COLUMNS] = { { 11, 2, 1, 3, 6 },
                                  { 0, -4, 8, 2, -7 },
                                  { 3, 9, 10, 3, 12 },
                                  { 2, -3, 5, 4, -2 },
                                  { -7, 6, 11, 2, 9 },
                                  { 3, 5, 7, 6, -9 } };

    Matrix matClass(mat, sizeof(mat)/sizeof(mat[0]));
    int result;
    ASSERT_THAT(matClass.SubSum(0, 1, 5, 4, result));
    ASSERT_EQUAL(86, result);
END_TEST

BEGIN_TEST(test_matrix_sub_sum_to_smaller_that_from)
    int mat[][Matrix::COLUMNS] = { { 11, 2, 1, 3, 6 },
                                  { 0, -4, 8, 2, -7 },
                                  { 3, 9, 10, 3, 12 },
                                  { 2, -3, 5, 4, -2 },
                                  { -7, 6, 11, 2, 9 },
                                  { 3, 5, 7, 6, -9 } };

    Matrix matClass(mat, sizeof(mat)/sizeof(mat[0]));
    int result = 0;
    ASSERT_THAT(!matClass.SubSum(0, 1, 2, 0, result));
    ASSERT_THAT(!matClass.SubSum(2, 1, 1, 3, result));
    ASSERT_EQUAL(0, result);
END_TEST

BEGIN_TEST(test_matrix_sub_sum_to_out_of_range)
    int mat[][Matrix::COLUMNS] = { { 11, 2, 1, 3, 6 },
                                  { 0, -4, 8, 2, -7 },
                                  { 3, 9, 10, 3, 12 },
                                  { 2, -3, 5, 4, -2 },
                                  { -7, 6, 11, 2, 9 },
                                  { 3, 5, 7, 6, -9 } };

    Matrix matClass(mat, sizeof(mat)/sizeof(mat[0]));

    int result = 0;
    ASSERT_THAT(!matClass.SubSum(0, 1, 6, 3, result));
    ASSERT_THAT(!matClass.SubSum(2, 1, 3, 5, result));
    ASSERT_EQUAL(0, result);
END_TEST

BEGIN_TEST(test_matrix_operator_square_brackets)
    int mat[][Matrix::COLUMNS] = { { 11, 2, 1, 3, 6 },
                                  { 0, -4, 8, 2, -7 },
                                  { 3, 9, 10, 3, 12 },
                                  { 2, -3, 5, 4, -2 },
                                  { -7, 6, 11, 2, 9 },
                                  { 3, 5, 7, 6, -9 } };

    Matrix matClass(mat, sizeof(mat)/sizeof(mat[0]));
    ASSERT_EQUAL(1, (matClass[{0, 2}]));
    ASSERT_EQUAL(-3, (matClass[{3, 1}]));
END_TEST

// Q6:

BEGIN_TEST(test_reverse_even_levels_order)
    BTree node14(16);
    BTree node13(15);
    BTree node12(14);
    BTree node11(13);
    BTree node10(12);
    BTree node9(11);
    BTree node8(10);
    BTree node7(9);
    BTree node6(7, &node13, &node14);
    BTree node5(6, &node11, &node12);
    BTree node4(5, &node9, &node10);
    BTree node3(4, &node7, &node8);
    BTree node2(3, &node5, &node6);
    BTree node1(2, &node3, &node4);
    BTree head(1, &node1, &node2);

    ASSERT_THAT(ReverseEvenLevelsOrder(&head));

    int wantedResult[] = { 1, 3, 2, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 9, };
    ASSERT_THAT(CheckBTreeResultRec(&head, wantedResult, 0));
END_TEST

BEGIN_TEST(test_reverse_even_levels_order_odd_levels)
    BTree node6(7);
    BTree node5(6);
    BTree node4(5);
    BTree node3(4);
    BTree node2(3, &node5, &node6);
    BTree node1(2, &node3, &node4);
    BTree head(1, &node1, &node2);

    ASSERT_THAT(ReverseEvenLevelsOrder(&head));

    int wantedResult[] = { 1, 3, 2, 4, 5, 6, 7};
    ASSERT_THAT(CheckBTreeResultRec(&head, wantedResult, 0));
END_TEST

// Q7:

BEGIN_TEST(test_array_class_get)
    int arr[] = { 1, 4, 6, -1, 2, -3, 8 };

    Array arrClass(arr, sizeof(arr)/sizeof(arr[0]));
    ASSERT_EQUAL(arr[3], arrClass.Get(3));
END_TEST

BEGIN_TEST(test_array_class_get_out_of_range)
    int arr[] = { 1, 4, 6, -1, 2, -3, 8 };

    Array arrClass(arr, sizeof(arr)/sizeof(arr[0]));
    ASSERT_EQUAL(arr[6], arrClass.Get(9));
END_TEST

BEGIN_TEST(test_array_class_set)
    int arr[] = { 1, 4, 6, -1, 2, -3, 8 };

    Array arrClass(arr, sizeof(arr)/sizeof(arr[0]));
    ASSERT_EQUAL(arr[3], arrClass.Get(3));
    arrClass.Set(3, 10);
    ASSERT_EQUAL(10, arrClass.Get(3));
END_TEST

BEGIN_TEST(test_array_class_set_out_of_range)
    int arr[] = { 1, 4, 6, -1, 2, -3, 8 };

    Array arrClass(arr, sizeof(arr)/sizeof(arr[0]));
    arrClass.Set(10, 10);
    ASSERT_EQUAL(-1, arrClass.Get(3));
END_TEST

BEGIN_SUITE(test_practice_day_4)
    TEST(test_rotate_matrix)
    TEST(test_rotate_matrix_null_matrix)

    TEST(test_matrix_sub_sum)
    TEST(test_matrix_sub_sum_to_row_at_the_end)
    TEST(test_matrix_sub_sum_to_column_at_the_end)
    TEST(test_matrix_sub_sum_to_row_and_column_at_the_end)
    TEST(test_matrix_sub_sum_to_smaller_that_from)
    TEST(test_matrix_sub_sum_to_out_of_range)
    TEST(test_matrix_operator_square_brackets)

    TEST(test_reverse_even_levels_order)
    TEST(test_reverse_even_levels_order_odd_levels)

    TEST(test_array_class_get)
    TEST(test_array_class_get_out_of_range)
    TEST(test_array_class_set)
    TEST(test_array_class_set_out_of_range)
END_SUITE
