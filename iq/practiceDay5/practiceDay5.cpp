#include "practiceDay5.hpp"
#include <vector>
#include <stack>
using namespace std;

namespace iq {

// Q1:

static bool BeforeDot(const char* a_str, double& a_result, size_t& a_indx)
{
    for(; '\0' != a_str[a_indx] && '.' != a_str[a_indx]; ++a_indx) {
        if(a_str[a_indx] < '0' || a_str[a_indx] > '9') {
            return false;
        }
        else {
            a_result *= 10;
            a_result += (a_str[a_indx] - '0');
        }
    }

    return true;
}

static bool AfterDot(const char* a_str, double& a_result, size_t a_indx)
{
    int afterDot = 10;

    for(; '\0' != a_str[a_indx]; ++a_indx) {
        if(a_str[a_indx] < '0' || a_str[a_indx] > '9') {
            return false;
        }
        else {
            a_result += ((double)(a_str[a_indx] - '0')/afterDot);
            afterDot *= 10;
        }
    }

    return true;
}

bool StringToDouble(const char* a_str, double& a_result)
{
    if(!a_str) {
        return false;
    }

    a_result = 0.0;
    size_t i = 0;
    double neg = 1.0;

    if('-' == a_str[i]) {
        neg = -1.0;
        ++i;
    }

    if(!BeforeDot(a_str, a_result, i)) {
        a_result *= neg;
        return false;
    }

    bool noError = true;
    if('.' == a_str[i]) {
        ++i;
        noError = AfterDot(a_str, a_result, i);
    }

    a_result *= neg;

    return noError;
}

// Q2:

static void SetWinners(vector<int>& a_numbers, stack<int>& a_winners)
{
    while(!a_winners.empty()) {
        a_numbers.push_back(a_winners.top());
        a_winners.pop();
    }
}

static bool EatAll(stack<int>& a_values, int a_number)
{
    while(!a_values.empty()) {
        if(abs(a_values.top()) > abs(a_number)) {
            return false;
        }
        if(a_number*(-1) == a_values.top()) {
            return true;
        }
        a_values.pop();
    }

    return true;
}

bool EatTheOtherDirectionValue(vector<int>& a_numbers)
{
    if(a_numbers.empty()) {
        return false;
    }

    stack<int> positive;
    stack<int> negative;

    size_t size = a_numbers.size();
    size_t i = 0;
    while(i < size) {
        if(a_numbers[i] < 0) {
            if(EatAll(positive, a_numbers[i])) {
                negative.push(a_numbers[i]);
            }
        }
        else {
            if(EatAll(negative, a_numbers[i])) {
                positive.push(a_numbers[i]);
            }
        }
        ++i;
    }

    a_numbers.clear();
    SetWinners(a_numbers, positive);
    SetWinners(a_numbers, negative);

    return true;
}

} // iq