#ifndef PRACTICE_DAY_6_HPP
#define PRACTICE_DAY_6_HPP

#include <stdlib.h>
#include <vector>

namespace iq {

enum Error { 
    SUCCESS, 
    FAILED 
};

Error ClosestToZero(const int* a_numbers, size_t a_size, int* a_result);

size_t CountInverseTripletNaive(const int* a_numbers, size_t a_size);

bool FindMinMaxElements(const int* a_numbers, size_t a_size, int& a_min, int& a_max);

bool GetKClosestElementsToX(const int* a_numbers, size_t a_size, size_t a_k, int a_x, std::vector<int>& a_result);

} // iq

#endif