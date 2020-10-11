#include "arrayQuestions.hpp"

namespace iq {

void SetImportantValues(int* a_someImportant, size_t a_firstSize, int* a_allImportant, size_t a_secondSize)
{
    if(!a_someImportant || !a_allImportant || !a_firstSize || !a_secondSize) {
        return;
    }

    size_t j = 0;
    for(size_t i = a_firstSize - a_secondSize; i < a_firstSize; ++i, ++j) {
        a_someImportant[i] = a_allImportant[j];
    }
}

void SetImportantValuesSorted(int* a_someImportant, int a_firstSize, int* a_allImportant, int a_secondSize)
{
    if(!a_someImportant || !a_allImportant || !a_firstSize || !a_secondSize) {
        return;
    }

    int secondInx = a_secondSize - 1;
    int firstInx = a_firstSize - a_secondSize - 1;
    int i = a_firstSize - 1;

    while(i != firstInx && i != secondInx) {
        if(a_allImportant[secondInx] > a_someImportant[firstInx]) {
            a_someImportant[i] = a_allImportant[secondInx];
            --secondInx;
        }
        else {
            a_someImportant[i] = a_someImportant[firstInx];
            --firstInx;
        }
        --i;
    }

    while(secondInx >= 0) {
        a_someImportant[i--] = a_allImportant[secondInx--];
    }
}

} // iq