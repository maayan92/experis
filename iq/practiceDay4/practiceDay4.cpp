#include "practiceDay4.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <map>
using namespace std;

namespace iq {

// 

size_t MinimumNumOfNegativeToMove(const int* arr, size_t size)
{
    int sum = 0;
    int counter = 0;
    int min = arr[0];
    size_t minIndx = 0;

    for(size_t i = 0; i < size; ++i) {
        sum += arr[i];
        
        if(arr[i] < min) {
            min = arr[i];
            minIndx = i;
        }

        if(sum < 0) {
            sum -= arr[minIndx];
            ++counter;

            ++minIndx;
            min = arr[minIndx];
        }
    }

    return counter;  
}

// Q1:

bool MaxSumRange(const int* a_numbers, size_t a_size, pair<size_t, size_t>& a_range)
{
    if(!a_numbers || !a_size) {
        return false;
    }

    int max = a_numbers[0];
    int sum = a_numbers[0];
    size_t saveIndx = 0;
    a_range.first = 0;
    a_range.second = 0;

    for(size_t i = 1; i < a_size; ++i) {
        sum += a_numbers[i];
        if(sum > max) {
            max = sum;
            a_range.first = saveIndx;
            a_range.second = i;
        }
        if(sum < 0) {
            sum = 0;
            saveIndx = i + 1;
        }
    }
}

// Q4:

static void SetValue(int mat[SIZE][SIZE], int& a_valSave, size_t& a_row, size_t& a_column)
{
    int valSet = a_valSave;
    a_valSave = mat[a_row][a_column];
    mat[a_row][a_column] = valSet;

    size_t prevRow = a_row;
    a_row = a_column;
    a_column = SIZE - prevRow - 1;
}

static void MoveValues(int mat[SIZE][SIZE], size_t a_row, size_t a_column)
{
    size_t nextColumn = SIZE - 1 - a_row;
    int valSave = mat[a_row][a_column];
    
    SetValue(mat, valSave, a_column, nextColumn);
    SetValue(mat, valSave, a_column, nextColumn);
    SetValue(mat, valSave, a_column, nextColumn);
    SetValue(mat, valSave, a_column, nextColumn);
}

bool RotateMatrix(int mat[SIZE][SIZE])
{
    if(!mat || !SIZE) {
        return false;
    }

    size_t border = SIZE / 2;
    size_t i = 0;

    for(; i < border; ++i) {
        for(size_t j = i; j < (SIZE - i - 1); ++j) {
            MoveValues(mat, i, j);
        }
    }

    return true;
}

// Q6:

static void PostOrderFillContainerRec(BTree* a_head, size_t a_level, stack<int>& a_values)
{
    if(!a_head) {
        return;
    }

    PostOrderFillContainerRec(a_head->m_left, a_level + 1, a_values);
    PostOrderFillContainerRec(a_head->m_right, a_level + 1, a_values);

    if(a_level%2 == 0) {
        a_values.push(a_head->m_data);
    }
}

static void PreOrderSetNewValuesRec(BTree* a_head, size_t a_level, stack<int>& a_values)
{
    if(!a_head) {
        return;
    }

    if(a_level%2 == 0) {
        a_head->m_data = a_values.top();
        a_values.pop();
    }

    PreOrderSetNewValuesRec(a_head->m_left, a_level + 1, a_values);
    PreOrderSetNewValuesRec(a_head->m_right, a_level + 1, a_values);
}

bool ReverseEvenLevelsOrder(BTree* a_head)
{
    if(!a_head) {
        return false;
    }

    stack<int> values;
    PostOrderFillContainerRec(a_head, 1, values);
    PreOrderSetNewValuesRec(a_head, 1, values);

    return true;
}

// Q7:

Array::Array(int* a_arr, size_t a_size)
try : m_size(a_size)
, m_arr(new int[m_size])
, m_version(new size_t[m_size])
, m_reset()
{
    if(a_arr) {
        for(size_t i = 0; i< m_size; ++i) {
            m_arr[i] = a_arr[i];
        }
    }

} catch(...) {
    throw;
}

int Array::Get(size_t a_indx) const
{
    if(a_indx > (m_size - 1)) {
        a_indx = m_size - 1;
    }

    return (m_version[a_indx] > m_reset.first) ? m_arr[a_indx] : m_reset.second;
}

void Array::Set(size_t a_indx, int a_value)
{
    if(a_indx < m_size) {
        m_arr[a_indx] = a_value;
        m_version[a_indx] = m_reset.first + 1;
    }
}

void Array::Reset(int a_value)
{
    m_reset.first++;
    m_reset.second = a_value;
}

// Q8:

// O(n*log(n)) + space
typedef multimap<double, double>::iterator Itr;

static size_t MoreWorkerNeeded(multimap<double, double>& a_times, Itr& a_itr, size_t a_workers)
{
    auto compare = a_itr;
    compare--;

    while(a_workers > 0) {
        if(a_itr->first >= compare->second) {
            return 0;
        }
        --a_workers;
    }

    return 1;
}

static size_t CountWorkers(multimap<double, double>& a_times)
{
    size_t countWorkers = 1;
    
    auto end = a_times.end();
    for(auto itr = a_times.begin()++; itr != end; ++itr) {
        countWorkers += MoreWorkerNeeded(a_times, itr, countWorkers);
    }

    return countWorkers;
}

size_t NumOfMinimumWorkers(const double* a_missions, size_t a_size)
{
    if(!a_missions || !a_size || (a_size % 2) != 0) {
        return 0;
    }

    multimap<double, double> times;

    for(size_t i = 0; i < a_size - 1; i += 2) {
        times.insert(make_pair(a_missions[i], a_missions[i]));
    }

    return CountWorkers(times);
}

// O(n)

size_t NumOfMinimumWorkersImprove(const size_t* a_missions, size_t a_size)
{
    if(!a_missions || !a_size || (a_size % 2) != 0) {
        return 0;
    }

    const size_t HOURS = 24;
    vector<size_t> count(HOURS);

    for(size_t i = 0; i < a_size - 1; i += 2) {
        size_t hour = a_missions[i];
        while(hour <= a_missions[i + 1]) {
            ++count[hour];
            ++hour;
        }
    }

    size_t max = count[0];
    for(size_t i = 1; i < HOURS; ++i) {
        if(count[i] > max) {
            max = count[i];
        }
    }

    return max;
}

// Q9:

static void SetNumOfSteps(multimap<char, size_t>& a_stepsByPos, vector<int>& a_steps, size_t a_size)
{
    auto itr = a_stepsByPos.begin();
    auto pair = itr;
    auto end = a_stepsByPos.end();
    size_t middle = a_size/2;

    while (pair != end && pair->first == itr->first) {
        ++pair;
    }
    --pair;

    if(itr == pair) {
        a_steps[pair->second] = pair->second - middle;
    }

    if(itr->second.first >= middle) {
        itr->second.second = itr->second.first - a_size - 1 - itr->second.first;
    }
    else {
        pair->second.second = pair->second.first - a_size - 1 - itr->second.first;
    }
    ++itr;
    --pair;
    
}

static bool Compare()
{
    return 
}

bool MinimumLinkedSwapToGetPalindrome(const string& a_str, size_t& a_result)
{
    a_result = 0;
    if(a_str.empty()) {
        return false;
    }

    multimap<char, size_t, Compare> positions;
    size_t size = a_str.size();
    vector<int> steps(size);

    for(size_t i = 0; i < size; ++i) {
        positions.insert(make_pair(a_str[i], make_pair(i, 0)));
    }

    SetNumOfSteps(positions, steps, size);
}

} // iq