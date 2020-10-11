#include "bitOperations.hpp"
#include <iosfwd>
#include <iostream>

namespace iq {

static const size_t BIT = 8;

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

    size_t numOfBits = (0 < a_number) ? NumberOfBitToReverse(a_number) : sizeof(a_number)*BIT;

    int result = 0;
    for(size_t i = 0, j = numOfBits; i <= numOfBits/2; ++i, --j) {
        int bitRight = (1 << i) & a_number;
        int bitLeft = (1 << j) & a_number;

        result |= (bitRight << (j - i));
        result |= (bitLeft >> (j - i));
    }

    a_number = result;
}

void SwapAdjacentBits(long& a_number)
{
    if(!a_number) {
        return;
    }

    long result = 0;
    for(size_t i = 0; i < sizeof(a_number)*BIT - 1; i+=2) {
        long bitRight = (1L << i) & a_number;
        long bitLeft = (1L << (i + 1)) & a_number;

        result |= (bitRight << 1);
        result |= (bitLeft >> 1);
    }

    a_number = result;
}

bool Majority(int a_number)
{
    size_t countOn = 0;
    size_t maxBits = sizeof(a_number)*BIT;
    for(size_t i = 0; i < maxBits; ++i) {
        countOn += ((a_number >> i) & 1);
    }

    return (countOn > maxBits/2);
}

bool MajorityUsingLut(int a_number)
{
    LutCount& lut = advcpp::Singleton<LutCount>::Instance();
    
    size_t countOn = 0;
    size_t maxBytes = sizeof(a_number);
    for(size_t i = 0; i < maxBytes; ++i) {
        countOn += lut.GetNumberOfOnBits((a_number & 0xff));

        a_number >>= BIT;
    }

    return (countOn > maxBytes*BIT/2);
}

LutCount::LutCount()
: m_lut(CHAR_BITS)
{
    buildLut();
}

static size_t CountBits(unsigned char a_number)
{
    size_t count = 0;

    for(size_t i = 0; i < sizeof(a_number)*BIT; ++i) {
        count += (a_number >> i) & 1;
    }

    return count;
}

void LutCount::buildLut()
{
    for(size_t i = 0; i < CHAR_BITS; ++i) {
        m_lut[i] = CountBits(i);
    }
}

size_t LutCount::GetNumberOfOnBits(unsigned char a_number)
{
    return m_lut[a_number];
}

} // iq