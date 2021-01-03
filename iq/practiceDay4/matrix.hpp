#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <utility>
#include <iosfwd>

namespace iq {

class Matrix {
public:
    static const size_t COLUMNS = 5;
    
    Matrix(int a_mat[][COLUMNS], size_t a_rows);
    ~Matrix();
    
    bool SubSum(size_t a_fromI, size_t a_fromJ, size_t a_toI, size_t a_toJ, int& a_result);
    int operator[](std::pair<size_t, size_t> a_ij) const;

private:
    void allocateNext(size_t a_indx);
    void freeAll(size_t a_to);
    void fillSumMat();

private:
    size_t m_rows;
    int** m_mat;
    int** m_sumMat;
};

} // iq

#endif