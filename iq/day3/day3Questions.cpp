#include "day3Questions.hpp"

namespace iq {

int NaiveSmallestPositiveNotPresent(const int* a_numbers, size_t a_size)
{
    int smallest = 0;
    bool newSmallFound = true;

    for (size_t i = 0; i < a_size && newSmallFound; ++i) {
        
        newSmallFound = false;
        for (size_t i = 0; i < a_size; ++i) {
            if(a_numbers[i] == smallest) {
                ++smallest;
                newSmallFound = true;
            }
        }
    }

    return smallest;
}

} // iq