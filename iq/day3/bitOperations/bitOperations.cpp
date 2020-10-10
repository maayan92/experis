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

    return numOfBits;
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

void SwapAdjacentBits(long& a_number)
{
    if(!a_number) {
        return;
    }

    size_t numOfBits = NumberOfBitToReverse(a_number); ///// problem

    for(size_t i = 0; i < numOfBits; i+=2) {
        long bitRight = (1 << i) & a_number;
        long bitLeft = (1 << (i + 1)) & a_number;

        if(bitRight) {
            a_number |= (bitRight << 1);
        }
        else {
            a_number &= ~(1 << (i + 1));
        }

        if(bitLeft) {
            a_number |= (bitLeft >> 1);
        }
        else {
            a_number &= ~(1 << i);
        }
    }
}

static const size_t BIT = 8;

bool Majority(int a_number)
{
    size_t countOn = 0;
    size_t maxBits = sizeof(a_number)*BIT;
    for(size_t i = 0; i < maxBits; ++i) {
        countOn += ((a_number >> i) & 1);
    }

    return (countOn > maxBits/2);
}

} // iq