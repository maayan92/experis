#include "day3Questions.hpp"

namespace iq {

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

} // iq