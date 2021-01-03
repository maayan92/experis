#include "practiceDay5.hpp"
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

} // iq