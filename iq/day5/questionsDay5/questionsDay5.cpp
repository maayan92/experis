#include "questionsDay5.hpp"
#include <cstring>
#include <vector>

namespace iq {

// Q1:

unsigned int AddTwoNumbers(unsigned int a_firstNum, unsigned int a_secondNum)
{
    if(!a_firstNum) {
        return a_secondNum;
    }
    if(!a_secondNum) {
        return a_firstNum;
    }

    unsigned int carry = 0;
    unsigned int result = 0;
    unsigned int bigger = (a_firstNum > a_secondNum) ? a_firstNum : a_secondNum;

    size_t i = 0;
    for(; bigger >> i ; ++i ) {
        unsigned int firstBit = (1 << i) & a_firstNum;
        unsigned int secondBit = (1 << i) & a_secondNum;

        result |= (firstBit ^ secondBit) ^ (carry << i);
        carry = ((firstBit & secondBit) >> i) | ((firstBit >> i) & carry) | ((secondBit >> i) & carry);
    }

    result |= carry << i;

    return result;
}

// Q5:

size_t NumberOfIdenticalPairs(const int* a_bits, size_t a_size)
{
    if(!a_bits || !a_size) {
        return 0;
    }

    size_t numOfPair = 0;

    for(size_t i = 0; i < a_size - 1; ++i) {
        numOfPair += !(a_bits[i] ^ a_bits[i + 1]);
    }

    return numOfPair;
}

// Q7:

size_t Counter(const char* a_first, const char* a_second)
{
    if(!a_first || !a_second) {
        return 0;
    }

    size_t firstSize = strlen(a_first);
    size_t secondSize = strlen(a_second);
    size_t countResult = 0;

    std::vector<size_t> counter(58, 0);

    for(size_t i = 0; i < firstSize; ++i) {
        ++counter[a_first[i] - 'A'];
    }

    for(size_t i = 0; i < secondSize; ++i) {
        countResult += counter[a_second[i] - 'A'];
        counter[a_second[i] - 'A'] = 0;
    }

    return countResult;
}

} // iq