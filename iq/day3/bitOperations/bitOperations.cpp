#include "bitOperations.hpp"
#include <iosfwd>
#include <iostream>

namespace iq {

static size_t NumberOfBitToReverse(int a_number)
{
    size_t numOfBits = 0;
    int numToCheck = 1;
    while(a_number > numToCheck) {
        numToCheck *= 2;
        ++numOfBits;
    }

    --numOfBits;
}

void ReverseBits(int& a_number)
{
    if(!a_number) {
        return;
    }

    size_t numOfBits = NumberOfBitToReverse(a_number);

    for(size_t i = 0, j = numOfBits; i <= numOfBits/2; ++i, --j) {
        int bitRight = (1 << i) & a_number;
        int bitLeft = (1 << j) & a_number;

        if(bitRight) {
            a_number |= (bitRight << (j - i));
        }
        else {
            a_number &= ~(1 << j);
        }

        if(bitLeft) {
            a_number |= (bitLeft >> (j - i));
        }
        else {
            a_number &= ~(1 << i);
        }
    }
}

} // iq