#include "arrayQuestions.hpp"
#include<bits/stdc++.h> 

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

// Q3:

void SetMyShadow(int* a_numbers, size_t a_size)
{
    if(!a_numbers || !a_size) {
        return;
    }

    int lastVal = a_numbers[a_size - 1];
    a_numbers[a_size - 1] = INT_MAX;

    for (size_t i = 0; i < a_size - 1; i++) {
        size_t j = i + 1;
        for(; a_numbers[i] >= a_numbers[j]; ++j)
            ;

        if(j < (a_size - 1)) {
            a_numbers[i] = a_numbers[j];
        }
        else if(a_numbers[i] < lastVal) {
            a_numbers[i] = lastVal;
        }
    }
    a_numbers[a_size - 1] = lastVal;
}

} // iq