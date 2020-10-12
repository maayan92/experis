#include "questionsDay5.hpp"
#include <iosfwd>

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
    unsigned int checkNum = 1;

    size_t i = 0;
    for(; bigger >= checkNum; ++i, checkNum*=2 ) {
        unsigned int firstBit = (1 << i) & a_firstNum;
        unsigned int secondBit = (1 << i) & a_secondNum;

        result |= (firstBit ^ secondBit) ^ (carry << i);

        if(firstBit & secondBit) {
            carry = 1;
        }
        else {
            carry &= ((firstBit >> i) | (secondBit >> i));
        }
    }

    result |= carry << i;

    return result;
}

} // iq