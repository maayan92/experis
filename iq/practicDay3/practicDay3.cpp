#include "practicDay3.hpp"
#include <climits>
#include <map>
using namespace std;

namespace iq {

// Q3:

static void FindNode(Node*& a_node, size_t& a_indx, size_t a_to)
{
    while(a_indx < a_to && a_node) {
        a_node = a_node->m_next;
        ++a_indx;
    }
}

static Node* Flip(Node* a_head, Node* a_to)
{
    if(!a_head || a_head == a_to) {
        return 0;
    }

    Node* tmp = Flip(a_head->m_next, a_to);
    if(!tmp) {
        return a_head;
    }

    a_head->m_next->m_next = a_head;
    a_head->m_next = a_to;

    return tmp;
}

bool ReverseSpecifiedPortion(Node*& a_head, size_t a_from, size_t a_to)
{
    if(!a_head || a_from >= a_to) {
        return false;
    }

    auto firstNode = a_head;
    size_t indx = 1;
    FindNode(firstNode, indx, a_from - 1);
    
    auto lastNode = firstNode;
    FindNode(lastNode, indx, a_to + 1);

    if(1 == a_from) {
        a_head = Flip(firstNode, lastNode);
    }

    firstNode->m_next = Flip(firstNode->m_next, lastNode);

    return true;
}

// Q2:

// O(rows) + O(K * log(rows)) + space O(rows)
bool KSmallestValue(const int a_mat[][COLUMNS], size_t a_rows, size_t a_k, int& a_result)
{
    if(!a_mat || !a_rows || !a_k || (a_k > COLUMNS*a_rows)) {
        return false;
    }

    multimap<int, pair<size_t, size_t> > values;

    for(size_t i = 0; i < a_rows; ++i) {
        values.insert(make_pair(a_mat[i][0], make_pair(i, 0)));
    }

    for(size_t i = 1; i < a_k; ++i) {
        auto val = values.begin();

        auto row = val->second.first;
        auto col = val->second.second + 1;

        values.erase(val);
        if(col < COLUMNS) {
            values.insert(make_pair(a_mat[row][col], make_pair(row, col)));
        }
    }

    a_result = values.begin()->first;
    return true;
}

// Q4:

static void FillList(multimap<size_t, int>& a_values, list<int>& a_result)
{
    while(!a_values.empty()) {
        auto itr = a_values.begin();
        a_result.push_back(itr->second);
        a_values.erase(itr);
    }
}

typedef multimap<size_t, int>::iterator MapItr;

static void SetValuesToMapByLevelRec(const BTree* a_head, size_t a_level, multimap<size_t, int>& a_values, MapItr a_parent)
{
    if(!a_head) {
        return;
    }

    a_parent = (0 == (a_level % 2)) ? a_values.insert(a_parent, make_pair(a_level, a_head->m_data))
                                    : a_values.insert(make_pair(a_level, a_head->m_data));

    ++a_level;
    SetValuesToMapByLevelRec(a_head->m_left, a_level, a_values, a_parent);
    SetValuesToMapByLevelRec(a_head->m_right, a_level, a_values, a_parent);
}

bool ConvertBTtoDLL(const BTree* a_head, list<int>& a_result)
{
    if(!a_head) {
        return false;
    }

    multimap<size_t, int> values;
    auto parent = values.insert(make_pair(0, a_head->m_data));
    SetValuesToMapByLevelRec(a_head->m_left, 1, values, parent);
    SetValuesToMapByLevelRec(a_head->m_right, 1, values, parent);

    a_result.clear();
    FillList(values, a_result);
    return true;
}

// Q5:

int MaxBranchMultiplyingRec(const BTree* a_head, int a_val)
{
    if(!a_head) {
        return a_val;
    }

    a_val *= a_head->m_data;

    int resultLeft = MaxBranchMultiplyingRec(a_head->m_left, a_val);
    int resultRight = MaxBranchMultiplyingRec(a_head->m_right, a_val);

    return ((resultLeft > resultRight && a_head->m_left) || !a_head->m_right) ? resultLeft : resultRight;
}

int MaxBranchMultiplying(const BTree* a_head)
{
    if(!a_head) {
        return 0;
    }

    return MaxBranchMultiplyingRec(a_head, 1);
}

// Q6:

static size_t CountNodes(const BTree* a_head)
{
    if(!a_head) {
        return 0;
    }

    return CountNodes(a_head->m_left) + CountNodes(a_head->m_right) + 1;
}

static bool IsBTreeHeapMinRec(const BTree* a_head, int a_parentVal, size_t a_index, size_t a_numOfNodes)
{
    if(!a_head) {
        return true;
    }

    if(a_head->m_data < a_parentVal || a_index >= a_numOfNodes) {
        return false;
    }

    return IsBTreeHeapMinRec(a_head->m_left, a_head->m_data, 2 * a_index + 1, a_numOfNodes) &&
            IsBTreeHeapMinRec(a_head->m_right, a_head->m_data, 2 * a_index + 2, a_numOfNodes);
}

bool IsBTreeHeapMin(const BTree* a_head)
{
    if(!a_head) {
        return false;
    }

    return IsBTreeHeapMinRec(a_head, a_head->m_data, 0, CountNodes(a_head));
}

// Q7:

static void GetValuesInSpecificLevelsRec(const BTree* a_head, size_t a_from, size_t a_to, size_t a_level, vector<int>& a_result)
{
    if(!a_head || a_level > a_to) {
        return;
    }

    if(a_level >= a_from) {
        a_result.push_back(a_head->m_data);
    }

    ++a_level;
    GetValuesInSpecificLevelsRec(a_head->m_left, a_from, a_to, a_level, a_result);
    GetValuesInSpecificLevelsRec(a_head->m_right, a_from, a_to, a_level, a_result);
}

bool GetValuesInSpecificLevels(const BTree* a_head, size_t a_from, size_t a_to, vector<int>& a_result)
{
    if(!a_head || a_from > a_to) {
        return false;
    }

    a_result.clear();
    GetValuesInSpecificLevelsRec(a_head, a_from, a_to, 1, a_result);
    return !a_result.empty();
}

// Q8:

static int DifferenceSumOddAndEvenRec(const BTree* a_head, size_t a_level)
{
    if(!a_head) {
        return 0;
    }

    return DifferenceSumOddAndEvenRec(a_head->m_left, a_level + 1)
            + DifferenceSumOddAndEvenRec(a_head->m_right, a_level + 1)
            + ((0 != (a_level % 2)) ? a_head->m_data : a_head->m_data * (-1));
}

int DifferenceSumOddAndEven(const BTree* a_head)
{
    if(!a_head) {
        return 0;
    }

    return DifferenceSumOddAndEvenRec(a_head, 1);
}

// Q9:

void DiagonalSumsRec(const BTree* a_head, size_t a_diagonal, vector<int>& a_result)
{
    if(!a_head) {
        return;
    }

    if(a_diagonal == a_result.size()) {
        a_result.push_back(a_head->m_data);
    }
    else {
        a_result[a_diagonal] += a_head->m_data;
    }

    DiagonalSumsRec(a_head->m_left, a_diagonal + 1, a_result);
    DiagonalSumsRec(a_head->m_right, a_diagonal, a_result);
}

bool DiagonalSums(const BTree* a_head, vector<int>& a_result)
{
    if(!a_head) {
        return false;
    }

    a_result.clear();
    DiagonalSumsRec(a_head, 0, a_result);
    return true;
}

} // iq