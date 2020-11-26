#ifndef PRACTIC_DAY_3_HPP
#define PRACTIC_DAY_3_HPP

#include <iosfwd>
#include <list>
#include "practicDay2.hpp"

namespace iq {

const size_t COLUMNS = 5;

bool ReverseSpecifiedPortion(Node*& a_head, size_t a_from, size_t a_to);

bool KSmallestValue(const int a_mat[][COLUMNS], size_t a_rows, size_t a_k, int& a_result);

struct BTree {
    BTree(int a_data)
    : m_data(a_data)
    , m_left(0)
    , m_right(0)
    {}

    BTree(int a_data, BTree* a_left, BTree* a_right)
    : m_data(a_data)
    , m_left(a_left)
    , m_right(a_right)
    {}

    int m_data;
    BTree* m_left;
    BTree* m_right;
};

bool ConvertBTtoDLL(const BTree* a_head, std::list<int>& a_result);

int MaxBranchMultiplying(const BTree* a_head);

bool IsBTreeHeapMin(const BTree* a_head);

bool GetValuesInSpecificLevels(const BTree* a_head, size_t a_from, size_t a_to, std::vector<int>& a_result);

int DifferenceSumOddAndEven(const BTree* a_head);

bool DiagonalSums(const BTree* a_head, std::vector<int>& a_result);

} // iq

#endif