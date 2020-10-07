#include "findSpecificElement.hpp"

namespace iq {

bool DoesContainElement(int* a_numbers, size_t a_size, int a_numToFind)
{
    if(a_numbers[a_size - 1] == a_numToFind) {
        return true;
    }

    int lastVal = a_numbers[a_size - 1];
    a_numbers[a_size - 1] = a_numToFind;

    size_t i = 0;
    for(; a_numbers[i] != a_numToFind ; ++i)
        ;

    a_numbers[a_size - 1] = lastVal; 
    if(i == (a_size - 1)) {
        return false;
    }

    return true;
}

} // iq