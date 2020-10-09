#include "day3Questions.hpp"
#include <vector>
#include <algorithm>
using namespace std;

namespace iq {

// first question:

bool NaiveSmallestPositiveNotPresent(const int* a_numbers, size_t a_size, int& a_result)
{
    if(!a_numbers || !a_size) {
        return false;
    }
    
    int smallest = 0;
    bool newSmallFound = true;

    while (newSmallFound) {
        
        newSmallFound = false;
        for (size_t i = 0; i < a_size; ++i) {
            if(a_numbers[i] == smallest) {
                ++smallest;
                newSmallFound = true;
            }
        }
    }

    a_result = smallest;
    return true;;
}

static int FindBigest(const int* a_numbers, size_t a_size)
{
    int max = a_numbers[0];

    for(size_t i = 1; i < a_size; ++i) {
        if(a_numbers[i] > max) {
            max = a_numbers[i];
        }
    }
    
    return max;
}

static int FindResult(vector<int>& a_isExist)
{
    for(size_t i = 0; i < a_isExist.size(); ++i) {
        if(0 == a_isExist[i]) {
            return i;
        }
    }

    return a_isExist.size();
} 

bool SmallestPositiveNotPresent(const int* a_numbers, size_t a_size, int& a_result)
{
    if(!a_numbers || !a_size) {
        return false;
    }

    int max = FindBigest(a_numbers, a_size);
    vector<int> isExist(max, 0);

    for(size_t i = 0; i < a_size; ++i) {
        if(a_numbers[i] >= 0) {
            isExist[a_numbers[i]] = 1;
        }
    }

    a_result = FindResult(isExist);
    return true;
}

// second question:

// least significant digit at the head

typedef list<unsigned char>::iterator Itr;

static void SetValue(int& a_carry, Itr& a_itr, unsigned char a_value)
{
    if(a_value > '9') {
        *a_itr = a_value - 10;
        a_carry = 1; 
    }
    else {
        *a_itr = a_value;
        a_carry = 0;
    }
    ++a_itr;
}

static void SetTheRest(list<unsigned char>& a_number, int a_carry, Itr& a_itr)
{
    auto end = a_number.end();

    while(0 != a_carry && a_itr != end) {
        auto add = *a_itr + a_carry;
        SetValue(a_carry, a_itr, add);
    }

    if(1 == a_carry) {
        a_number.push_back('1');
    }
}

static void AddLists(list<unsigned char>& a_firstNum, const list<unsigned char>& a_secondNum)
{
    auto carry = 0;

    auto itrFirst = a_firstNum.begin();
    auto itrSecond = a_secondNum.begin();

    auto endSecond = a_secondNum.end();
    while(itrSecond != endSecond) {
        auto add = *itrFirst + *itrSecond++ + carry - '0';
        SetValue(carry, itrFirst, add);
    }

    SetTheRest(a_firstNum, carry, itrFirst);
}

list<unsigned char> AddListNumbers(const list<unsigned char>& a_firstNum, const list<unsigned char>& a_secondNum)
{
    list<unsigned char> result;

    if(a_firstNum.size() > a_secondNum.size()) {
        result = a_firstNum;
        AddLists(result, a_secondNum);
    }
    else {
        result = a_secondNum;
        AddLists(result, a_firstNum);
    }

    return result;
}

// least significant digit at the tail, using reverse

std::list<unsigned char> AddListNumbersTailLSD(std::list<unsigned char>& a_firstNum, std::list<unsigned char>& a_secondNum)
{
    a_firstNum.reverse();
    a_secondNum.reverse();

    std::list<unsigned char> result = AddListNumbers(a_firstNum, a_secondNum);

    a_firstNum.reverse();
    a_secondNum.reverse();

    result.reverse();
    return result;
}

// least significant digit at the tail

typedef list<unsigned char>::reverse_iterator RItr;

static void SetValueReverse(int& a_carry, RItr& a_itr, unsigned char a_value)
{
    if(a_value > '9') {
        *a_itr = a_value - 10;
        a_carry = 1; 
    }
    else {
        *a_itr = a_value;
        a_carry = 0;
    }
    ++a_itr;
}

static void SetTheRestReverse(list<unsigned char>& a_number, int a_carry, RItr& a_itr)
{
    auto end = a_number.rend();

    while(0 != a_carry && a_itr != end) {
        auto add = *a_itr + a_carry;
        SetValueReverse(a_carry, a_itr, add);
    }

    if(1 == a_carry) {
        a_number.push_front('1');
    }
}

static void AddListsReverse(list<unsigned char>& a_firstNum, const list<unsigned char>& a_secondNum)
{
    auto carry = 0;

    auto itrFirst = a_firstNum.rbegin();
    auto itrSecond = a_secondNum.rbegin();

    auto endSecond = a_secondNum.rend();
    while(itrSecond != endSecond) {
        auto add = *itrFirst + *itrSecond++ + carry - '0';
        SetValueReverse(carry, itrFirst, add);
    }

    SetTheRestReverse(a_firstNum, carry, itrFirst);
}

list<unsigned char> AddListNumbersReverse(const list<unsigned char>& a_firstNum, const list<unsigned char>& a_secondNum)
{
    list<unsigned char> result;

    if(a_firstNum.size() > a_secondNum.size()) {
        result = a_firstNum;
        AddListsReverse(result, a_secondNum);
    }
    else {
        result = a_secondNum;
        AddListsReverse(result, a_firstNum);
    }

    return result;
}

} // iq