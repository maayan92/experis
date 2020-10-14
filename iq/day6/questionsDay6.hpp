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

} // iq

#endif