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

BEGIN_SUITE(test_list_questions)
    TEST(test_list_questions_flip)
END_SUITE

