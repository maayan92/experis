#include "firstNotUnique.hpp"
#include <vector>
using namespace std;

namespace iq {

bool FindElementODoubleN(int* a_arr, size_t a_size, int& a_result)
{
    if(!a_arr) {
        return false;
    }

    for(size_t i = 0; i < a_size - 1; ++i) {
        for(size_t j = i + 1; j < a_size; ++j) {
            if(a_arr[i] == a_arr[j]) {
                a_result = a_arr[i];
                return true;
            }
        }
    }
  
    return false;
}

static void FindRange(int* a_arr, size_t a_size, int& a_max, int& a_min)
{
    int max = a_arr[0];
    int min = a_arr[0];

    for(size_t i = 1; i < a_size; ++i) {
        if(a_arr[i] > max) {
            max = a_arr[i];
        }
        else if(a_arr[i] < min) {
            min = a_arr[i];
        }
    }

    a_max = max;
    a_min = min;
}

static void CountArrValues(int *a_arr, size_t a_size, vector<int> a_count, int a_min)
{
    for(size_t i = 0; i < a_size; ++i) {
        ++a_count[a_arr[i] - a_min];
    }
}

bool FindElementOOneN(int* a_arr, size_t a_size, int& a_result)
{
    if(!a_arr) {
        return false;
    }

    int max, min;
    FindRange(a_arr, a_size, max, min);
    vector<int> count(max - min);
    CountArrValues(a_arr, a_size, count, min);

    for(size_t i = 0; i < a_size - 1; ++i) {
        if(count[i] > 1) {
            a_result = i + min;
            return true;
        }
    }
  
    return false;
}

} // iq