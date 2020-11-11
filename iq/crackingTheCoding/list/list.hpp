#ifndef LIST_HPP
#define LIST_HPP

#include <iosfwd>

namespace iq {

struct Node {
    Node(int a_data)
    : m_data(a_data)
    , m_next(0)
    {}
    
    Node(int a_data, Node* a_next)
    : m_data(a_data)
    , m_next(a_next)
    {}

    int m_data;
    Node* m_next;
};

bool RemoveDuplicates(Node* a_head);

Node* ReturnKthToLast(Node* a_head, size_t a_kFromLast);

bool DeleteMiddleNode(Node* a_nodeToRemove);

bool Partition(Node*& a_head, int a_pivot);

Node* SumLists(Node* a_first, Node* a_second);

Node* SumListsRecursion(Node* a_first, Node* a_second);

} // iq

#endif