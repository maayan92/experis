#ifndef FIRST_NOT_UNIQUE_HPP
#define FIRST_NOT_UNIQUE_HPP

#include <iosfwd>

namespace iq {

// find the element in O(n^2)
bool FindElementODoubleN(int* a_arr, size_t a_size, int& a_result);

// find the element in O(n)
bool FindElementOOneN(int* a_arr, size_t a_size, int& a_result);

} // iq

#endif