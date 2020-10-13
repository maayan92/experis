#include "questionsDay6.hpp"

namespace iq {

// Q1:

void Swap(int& a_first, int& a_second)
{
    a_first += a_second;
    a_second = a_first - a_second;
    a_first -= a_second;
}

void SwapBits(int& a_first, int& a_second)
{
    a_first ^= a_second;
    a_second ^= a_first;
    a_first ^= a_second;
}

// Q2:

void Abs(int& a_number)
{
    --a_number;
    a_number = ~a_number;
}

} // iq