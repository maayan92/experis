#ifndef PRACTIC_DAY_HPP
#define PRACTIC_DAY_HPP

#include <iosfwd>

namespace iq {

const size_t SIZE = 10;

bool HasPyramid(const int* a_domino, size_t a_size);

bool HasPairSumNaive(const int * a_numbers, size_t a_size, int a_num);

bool HasPairSum(const int * a_numbers, size_t a_size, int a_num);

bool FillMat(size_t a_mat[SIZE][SIZE]);

} // iq

#endif