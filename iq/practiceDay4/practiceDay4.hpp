#ifndef PRACTICE_DAY_4_HPP
#define PRACTICE_DAY_4_HPP

#include "practicDay3.hpp"
#include "matrix.hpp"

namespace iq {

static const size_t SIZE = 5;
    
// bool MaxSumRange(const int* a_numbers, size_t a_size, std::pair<size_t, size_t>& a_result);

// size_t NumOfActionsToGetPalindrom(const std::string& a_str);

bool RotateMatrix(int mat[SIZE][SIZE]);

size_t MinimumNumOfNegativeToMove(const int* arr, size_t size);

bool ReverseEvenLevelsOrder(BTree* a_head);

class Array {
public:
    Array(int* a_arr, size_t a_size);
    //~Array() = default;

    int Get(size_t a_indx) const;
    void Set(size_t a_indx, int a_value);
    void Reset(int a_value);

private:
    size_t m_size;
    int* m_arr;
    size_t* m_version;
    std::pair<size_t, int> m_reset;
};

size_t NumOfMinimumWorkers(const double* a_missions, size_t a_size);

} // iq

#endif