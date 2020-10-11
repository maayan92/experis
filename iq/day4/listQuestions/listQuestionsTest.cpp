#include "mu_test.h"

#include "listQuestions.hpp"
using namespace iq;

BEGIN_TEST(test_list_questions_flip)
    Node<int> head(1);
    Node<int> node1(4);
    Node<int> node2(8);
    Node<int> node3(2);
    Node<int> node4(9);
    head.m_next = &node1;
    node1.m_next = &node2;
    node2.m_next = &node3;
    node3.m_next = &node4;
    
    Node<int>* result = Flip(&head);

    ASSERT_EQUAL(9, result->m_data);
    result = result->m_next;
    ASSERT_EQUAL(2, result->m_data);
    result = result->m_next;
    ASSERT_EQUAL(8, result->m_data);
    result = result->m_next;
    ASSERT_EQUAL(4, result->m_data);
    result = result->m_next;
    ASSERT_EQUAL(1, result->m_data);

    ASSERT_THAT(!head.m_next);
END_TEST

BEGIN_TEST(test_list_has_loop_true)
    Node<int> node6(15);
    Node<int> node5(20, &node6);
    Node<int> node4(9, &node5);
    Node<int> node3(2, &node4);
    Node<int> node2(8, &node3);
    Node<int> node1(4, &node2);
    Node<int> head(1, &node1);
    node6.m_next = &node4;

    ASSERT_THAT(HasLoop(&head));
END_TEST

BEGIN_TEST(test_list_has_loop_false)
    Node<int> node6(15);
    Node<int> node5(20, &node6);
    Node<int> node4(9, &node5);
    Node<int> node3(2, &node4);
    Node<int> node2(8, &node3);
    Node<int> node1(4, &node2);
    Node<int> head(1, &node1);

    ASSERT_THAT(!HasLoop(&head));
END_TEST

BEGIN_TEST(test_list_find_loop_point)
    Node<int> node6(15);
    Node<int> node5(20, &node6);
    Node<int> node4(9, &node5);
    Node<int> node3(2, &node4);
    Node<int> node2(8, &node3);
    Node<int> node1(4, &node2);
    Node<int> head(1, &node1);
    node6.m_next = &node4;

    Node<int>* result = FindLoopPoint(&head);
    
    ASSERT_EQUAL(result->m_data, node4.m_data);
    ASSERT_EQUAL(result, &node4);
END_TEST

BEGIN_TEST(test_list_with_loop_length)
    Node<int> node6(15);
    Node<int> node5(20, &node6);
    Node<int> node4(9, &node5);
    Node<int> node3(2, &node4);
    Node<int> node2(8, &node3);
    Node<int> node1(4, &node2);
    Node<int> head(1, &node1);
    node6.m_next = &node4;

    ASSERT_EQUAL(7, ListWithLoopLength(&head));
END_TEST

BEGIN_SUITE(test_list_questions)
    TEST(test_list_questions_flip)

    TEST(test_list_has_loop_true)
    TEST(test_list_has_loop_false)

    TEST(test_list_find_loop_point)

    TEST(test_list_with_loop_length)
END_SUITE

