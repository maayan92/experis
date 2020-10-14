#include "questionsDay6.hpp"
#include <climits>

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
    const int mask = a_number >> (sizeof(a_number)*CHAR_BIT - 1);
    
    a_number = (a_number + mask) ^ mask;
}

// Q3 (5.a):

size_t NumberOfIdenticalPairs(unsigned long a_number)
{
    if(!a_number) {
        return 0;
    }

    size_t count = 0;
    for(size_t i = 0; i < sizeof(a_number)*CHAR_BIT - 1; ++i) {
        count += !((a_number >> i) ^ (a_number >> (i + 1)));
    }

    return count;
}

// Q4 (5.b):

size_t IndexToFlip(const int* a_bits, size_t a_size)
{
    if(!a_bits || !a_size) {
        return 0;
    }

    size_t indx = 0;
    if(a_bits[0] ^ a_bits[1]) {
        indx = 0;
    }

    for(size_t i = 1; i < a_size - 1; ++i) {
        if((a_bits[i - 1] ^ a_bits[i]) & (a_bits[i] ^ a_bits[i + 1])) {
            return i;
        }
    }

    if(a_bits[a_size - 2] ^ a_bits[a_size - 1]) {
        indx = a_size - 1;
    }

    return indx;
}

} // iq