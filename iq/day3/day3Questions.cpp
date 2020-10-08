#include "day3Questions.hpp"
#include <vector>
#include <algorithm>
using namespace std;

namespace iq {

bool NaiveSmallestPositiveNotPresent(const int* a_numbers, size_t a_size, int& a_result)
{
    if(!a_numbers || !a_size) {
        return false;
    }
    
    int smallest = 0;
    bool newSmallFound = true;

    while (newSmallFound) {
        
        newSmallFound = false;
        for (size_t i = 0; i < a_size; ++i) {
            if(a_numbers[i] == smallest) {
                ++smallest;
                newSmallFound = true;
            }
        }
    }

    a_result = smallest;
    return true;;
}

static int FindBigest(const int* a_numbers, size_t a_size)
{
    int max = a_numbers[0];

    for(size_t i = 1; i < a_size; ++i) {
        if(a_numbers[i] > max) {
            max = a_numbers[i];
        }
    }
    
    return max;
}

static int FindResult(vector<int>& a_isExist)
{
    for(size_t i = 0; i < a_isExist.size(); ++i) {
        if(0 == a_isExist[i]) {
            return i;
        }
    }

    return a_isExist.size();
} 

bool SmallestPositiveNotPresent(const int* a_numbers, size_t a_size, int& a_result)
{
    if(!a_numbers || !a_size) {
        return false;
    }

    int max = FindBigest(a_numbers, a_size);
    vector<int> isExist(max, 0);

    for(size_t i = 0; i < a_size; ++i) {
        if(a_numbers[i] >= 0) {
            isExist[a_numbers[i]] = 1;
        }
    }

    a_result = FindResult(isExist);
    return true;
}

} // iq