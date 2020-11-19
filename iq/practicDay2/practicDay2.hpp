#ifndef PRACTIC_DAY_2_HPP
#define PRACTIC_DAY_2_HPP

#include <iosfwd>
#include <vector>

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

    bool operator<(Node* a_node)
    {
        return m_data < a_node->m_data;
    }

    int m_data;
    Node* m_next;
};

Node* MergeListsNaive(const Node** a_list, size_t a_size);

Node* MergeLists(const Node** a_lists, size_t a_size);

bool SortArray012(size_t* a_012, size_t a_size);

bool BestFlipPosForOneSeq(const size_t* a_012, size_t a_size, size_t& a_bestPos);

bool CountOnePairs(size_t* a_bits, size_t a_size, size_t& a_count);

bool CountOnePairs(unsigned long a_number, size_t& a_count);

struct Tree {
    Tree(int a_data)
    : m_data(a_data)
    , m_children()
    {}
    
    Tree(int a_data, std::vector<Tree*> a_children)
    : m_data(a_data)
    , m_children(a_children)
    {}

    int m_data;
    std::vector<Tree*> m_children;
};

bool LongestBranchLength(const Tree* a_head, size_t& a_length);

bool IsPowerOf8(int a_number);

} // iq

#endif