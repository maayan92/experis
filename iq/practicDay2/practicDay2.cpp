#include "practicDay2.hpp"
#include <climits>
#include <map>
#include <set>
using namespace std;


#include <iostream>

namespace iq {

// Q1:

static size_t FindFirstNotNull(const Node** a_lists, size_t a_size)
{
    size_t i = 0;
    for(; i < a_size; ++i) {
        if(a_lists[i]) {
            return i;
        }
    }

    return i;
}

static Node* CopyFirst(const Node* a_head)
{
    Node* result = new Node(a_head->m_data);
    Node* copy = result;

    a_head = a_head->m_next;
    while(a_head) {
        copy->m_next = new Node(a_head->m_data);
        copy = copy->m_next;
        a_head = a_head->m_next;
    }

    return result;
}

static void FillAtTheEnd(const Node* a_node, Node* a_result)
{
    while(a_node) {
        a_result->m_next = new Node(a_node->m_data);
        a_result = a_result->m_next;
        a_node = a_node->m_next;
    }
}

static void Merge(const Node* a_head, Node*& a_result)
{
    if(a_head->m_data < a_result->m_data) {
        Node* node = new Node(a_head->m_data, a_result);
        a_result = node;
        a_head = a_head->m_next;
    }
    
    Node* resultPtr = a_result;

    while(resultPtr->m_next && a_head) {
        if(resultPtr->m_next->m_data < a_head->m_data) {
            resultPtr = resultPtr->m_next;
        }
        else {
            Node* node = new Node(a_head->m_data, resultPtr->m_next);
            resultPtr->m_next = node;
            a_head = a_head->m_next;
        }
    }

    FillAtTheEnd(a_head, resultPtr);
}

Node* MergeListsNaive(const Node** a_lists, size_t a_size)
{
    if(!a_lists || !a_size) {
        return 0;
    }

    size_t indx = FindFirstNotNull(a_lists, a_size);
    if(a_size == indx) {
        return 0;
    }

    Node* result = CopyFirst(a_lists[indx]);

    ++indx;
    for(; indx < a_size; ++indx) {
        if(a_lists[indx]) {
            Merge(a_lists[indx], result);
        }
    }

    return result;
}

//

static Node* FillByOrder(const map<int, Node*>& a_ordered)
{
    auto itr = a_ordered.begin();
    auto end = a_ordered.end();

    if(itr == end) {
        return 0;
    }

    Node* result = itr->second;
    Node* node = result;

    ++itr;
    for(; itr != end; ++itr) {
        node->m_next = itr->second;
        node = node->m_next;
    }

    return result;
}

Node* MergeLists(const Node** a_lists, size_t a_size)
{
    if(!a_lists || !a_size) {
        return 0;
    }

    map<int, Node*> ordered;

    for(size_t i = 0; i < a_size; ++i) {
        while(a_lists[i]) {
            ordered[a_lists[i]->m_data] = new Node(a_lists[i]->m_data);
            a_lists[i] = a_lists[i]->m_next;
        }
    }

    Node* result = FillByOrder(ordered);

    return result;
}

// Q2:

bool SortArray012(size_t* a_012, size_t a_size)
{
    if(!a_012 || !a_size) {
        return false;
    }

    size_t const SIZE = 3;
    vector<size_t> count(SIZE, 0);
    for(size_t i = 0; i < a_size; ++i) {
        ++count[a_012[i]];
    }

    size_t i = 0;
    for(size_t j = 0; j < SIZE; ++j) {
        while(count[j]--) {
            a_012[i++] = j;
        }
    }

    return true;
}

// Q3:

static void SetValues(size_t a_count, size_t& a_lastCount, size_t& a_tmpBest, size_t& a_bestPos)
{
    if(a_count > a_lastCount) {
        a_bestPos = a_tmpBest;
        a_lastCount = a_count;
    }
}

static size_t CountOnes(const size_t* a_012, size_t a_size, size_t& a_indx)
{
    size_t count = 0;
    while(a_indx < a_size && 1 == a_012[a_indx]) {
        ++count;
        ++a_indx;
    }

    return count;
}

bool BestFlipPosForOneSeq(const size_t* a_012, size_t a_size, size_t& a_bestPos)
{
    if(!a_012 || !a_size) {
        return false;
    }

    size_t countP2 = 0;
    size_t lastCount = 0;
    size_t tmpBest = 0;
    a_bestPos = 0;
    
    size_t indx = 0;
    size_t countP1 = CountOnes(a_012, a_size, indx);
    if(a_size == indx) {
        return false;
    }

    while(indx < a_size) {
        tmpBest = indx++;
        countP2 = CountOnes(a_012, a_size, indx);

        SetValues(countP1 + countP2, lastCount, tmpBest, a_bestPos);
        countP1 = countP2;
    }

    SetValues(countP1 + countP2, lastCount, tmpBest, a_bestPos);

    return true;
}

// Q4:

bool CountOnePairs(size_t* a_bits, size_t a_size, size_t& a_count)
{
    if(!a_bits || !a_size) {
        return false;
    }

    a_count = 0;
    for(size_t i = 0; i < a_size - 1; ++i) {
        a_count += (a_bits[i] & a_bits[i + 1]);
    }

    return true;
}

bool CountOnePairs(unsigned long a_number, size_t& a_count)
{
    size_t size = sizeof(unsigned long)*CHAR_BIT;
    a_count = 0;

    for(size_t i = 0; i < size - 1; ++i) {
        a_count += ((a_number >> i) & (a_number >> (i + 1)) & 1);
    }

    return true;
}

// Q5:

static size_t LongestBranchLengthRec(const Tree* a_head, set<int>& a_values);

static size_t LongestBranchFromChilds(const Tree* a_head, set<int>& a_values)
{
    size_t max = 0;
    
    auto itr = a_head->m_children.begin();
    auto end = a_head->m_children.end();

    for(; itr != end; ++itr) {
        size_t count = LongestBranchLengthRec(*itr, a_values);
        if(count > max) {
            max = count;
        }
    }

    return max;
}

static size_t LongestBranchLengthRec(const Tree* a_head, set<int>& a_values)
{
    if (a_values.insert(a_head->m_data).second) {  // O(log(n))

        size_t max = LongestBranchFromChilds(a_head, a_values);
        
        a_values.erase(a_head->m_data); // O(log(n))
        return max + 1;
    }

    return LongestBranchFromChilds(a_head, a_values);
}

bool LongestBranchLength(const Tree* a_head, size_t& a_length)
{
    if(!a_head) {
        return false;
    }

    set<int> values;
    a_length = LongestBranchLengthRec(a_head, values);

    return true;
}

// Q6:

bool IsPowerOf8(int a_number)
{
    return (a_number && !(a_number & (a_number - 1)) && !(a_number & 0xB6DB6DB6));
}

} // iq