#ifndef DAY_3_QUESTIONS_HPP
#define DAY_3_QUESTIONS_HPP

#include <iosfwd>
#include <list>

namespace iq {

// first question:

bool NaiveSmallestPositiveNotPresent(const int* a_numbers, size_t a_size, int& a_result);

bool SmallestPositiveNotPresent(const int* a_numbers, size_t a_size, int& a_result);

// second question:
std::list<unsigned char> AddListNumbers(const std::list<unsigned char>& a_firstNum, const std::list<unsigned char>& a_secondNum);

std::list<unsigned char> AddListNumbersTailLSD(std::list<unsigned char>& a_firstNum, std::list<unsigned char>& a_secondNum);

std::list<unsigned char> AddListNumbersReverse(const std::list<unsigned char>& a_firstNum, const std::list<unsigned char>& a_secondNum);

} // iq

#endif