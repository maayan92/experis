#include "practiceDay6.hpp"
#include <map>
#include <limits.h>
using namespace std;

namespace iq {

// Q0:

Error ClosestToZero(const int* a_numbers, size_t a_size, int* a_result)
{
    if(!a_numbers || !a_size || !a_result) {
        return FAILED;
    }
    
    int closest = a_numbers[0];
    int closestDist = abs(a_numbers[0]);
    for(size_t i = 1; i < a_size; ++i) {
        int dist = abs(a_numbers[i]);

        if(dist < closestDist || (dist == closestDist && a_numbers[i] > 0)) {
            closest = a_numbers[i];
            closestDist = dist;
        }
    }
    
    *a_result = closest;
    return SUCCESS;
}

// Q1:

size_t CountAllJOptions(const int* a_numbers, size_t a_from, size_t a_to)
{
    size_t j = a_from + 1;
    size_t count = 0;

    while(j < a_to) {
        if(a_numbers[j] > a_numbers[a_to] && a_numbers[j] < a_numbers[a_from]) {
            ++count;
        }

        ++j;
    }

    return count;
}

size_t CountInverseTripletNaive(const int* a_numbers, size_t a_size)
{
    if(!a_numbers || !a_size) {
        return 0;
    }

    size_t countTriplets = 0;
    for(size_t i = 0; i < a_size - 2; ++i) {
        for(size_t k = a_size - 1; k > (i + 1); --k) {
            if(a_numbers[k] < a_numbers[i]) {
                countTriplets += CountAllJOptions(a_numbers, i, k);
            }
        }
    }

    return countTriplets;
}

// Q2:

bool FindMinMaxElements(const int* a_numbers, size_t a_size, int& a_min, int& a_max)
{
    if(!a_numbers || !a_size) {
        return false;
    }

    a_max = a_numbers[0];
    a_min = a_numbers[0];
    for(size_t i = 1; i < a_size; ++i) {
        a_max = a_max - ((a_max - a_numbers[i]) & ((a_max - a_numbers[i]) >> (sizeof(int) * CHAR_BIT - 1)));
        a_min = a_numbers[i] + ((a_min - a_numbers[i]) & ((a_min - a_numbers[i]) >> (sizeof(int) * CHAR_BIT - 1)));
    }

    return true;
}

// Q3:

static void CopyResultToVector(const int* a_numbers, multimap<int, size_t>& a_dist, vector<int>& a_result, size_t a_k)
{
    a_result.clear();
    a_result.reserve(a_k);

    auto itr = a_dist.begin();
    for(size_t i = 0; i < a_k; ++i, ++itr) {
        a_result[i] = a_numbers[itr->second];
    }
}

bool GetKClosestElementsToX(const int* a_numbers, size_t a_size, size_t a_k, int a_x, vector<int>& a_result)
{
    if(!a_numbers || !a_size || a_k > a_size) {
        return false;
    }

    multimap<int, size_t> dist;

    size_t i = 0;
    for(; i < a_k; ++i) {
        dist.insert(make_pair(abs(a_numbers[i] - a_x), i));
    }

    for(; i < a_size; ++i) {
        int newDist = abs(a_numbers[i] - a_x);
        if(newDist < dist.rbegin()->first) {
            dist.erase(--dist.end());
            dist.insert(make_pair(newDist, i));
        }
    }

    CopyResultToVector(a_numbers, dist, a_result, a_k);
    
    return true;
}

} // iq
