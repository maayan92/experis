#include "practicDay.hpp"
#include <vector>
#include <stdlib.h>
using namespace std;

namespace iq {

// Q1:

static void Count(vector<int>& a_count, const int* a_domino, size_t a_size)
{
    for(size_t i = 0; i < a_size; ++i) {
        ++a_count[a_domino[i]];
    }
}

bool HasPyramid(const int* a_domino, size_t a_size)
{
    if(!a_domino || !a_size) {
        return false;
    }

    vector<int> count(9, 0);
    Count(count, a_domino, a_size);

    for(size_t i = 0; i < a_size - 1; i+=2 ) {
        if(count[a_domino[i]] == count[a_domino[i + 1]]) {
            if(3 != count[a_domino[i]]) {
                return false;
            }
        }
        else if(abs(count[a_domino[i]] - count[a_domino[i + 1]]) > 1){
            return false;
        }
    }

    return true;
}

// Q2:

bool HasPairSumNaive(const int * a_numbers, size_t a_size, int a_num)
{
    if(!a_numbers || !a_size || a_size < 2) {
        return false;
    }

    for(size_t i = 0; i < a_size - 1; ++i) {
        for(size_t j = i + 1; j < a_size; ++j) {
            if((a_numbers[i] + a_numbers[j]) == a_num) {
                return true;
            }
        }
    }

    return false;
}

static void FindMinMax(const int* a_numbers, size_t a_size, int& a_min, int& a_max)
{
    a_max = a_numbers[0];
    a_min = a_numbers[0];

    for(size_t i = 1; i < a_size; ++i) {
        if(a_numbers[i] > a_max) {
            a_max = a_numbers[i];
        }
        else if(a_numbers[i] < a_min) {
            a_min = a_numbers[i];
        }
    }
}

bool HasPairSum(const int* a_numbers, size_t a_size, int a_num)
{
    if(!a_numbers || !a_size || a_size < 2) {
        return false;
    }

    int min;
    int max;
    FindMinMax(a_numbers, a_size, min, max);

    int diff = ((max < 0) ? min - max : max - min) + 1;
    vector<bool> rest(diff, false);

    for(size_t i = 0; i < a_size; ++i) {
        if(rest[(a_num - a_numbers[i]) - min]) {
            return true;
        }
        rest[a_numbers[i] - min] = true;
    }

    return false;
}

// Q3:

bool FillMat(size_t a_mat[SIZE][SIZE])
{
    if(!SIZE) {
        return false;
    }

    size_t count = 0;
    size_t maxSize = SIZE*SIZE;

    while(count < maxSize) {
        size_t number = rand() % maxSize + 1;
        size_t i = (number - 1) / SIZE;
        size_t j = (number - 1) % SIZE;

        if(0 == a_mat[i][j]) {
            ++count;
        }

        a_mat[i][j] = number; 
    }

    return true;
}

} // iq