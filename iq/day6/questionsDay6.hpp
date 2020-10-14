#ifndef QUESTIONS_DAY_6_HPP
#define QUESTIONS_DAY_6_HPP

#include <iosfwd>

namespace iq {

// Q1:

void Swap(int& a_first, int& a_second);

void SwapBits(int& a_first, int& a_second);

// Q2:

void Abs(int& a_number);

// Q3 (5.a):

size_t NumberOfIdenticalPairs(unsigned long a_number);

// Q4 (5.b):

size_t IndexToFlip(const int* a_bits, size_t a_size);

// Q6:

void FromToChar(const char* a_letters, size_t a_size, char a_find, size_t& a_from, size_t& a_to);

// Q8:

void Product(const int *a_origin, size_t a_size, int *a_result);

} // iq

#endif