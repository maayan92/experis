#include "matrix.hpp"
using namespace std;

namespace iq {

// Q5:

Matrix::Matrix(int a_mat[][COLUMNS], size_t a_rows)
try : m_rows(a_rows)
, m_mat(new int*[m_rows])
, m_sumMat(new int*[m_rows])
{
    for(size_t i = 0; i < m_rows; ++i) {
        allocateNext(i);
        for(size_t j = 0; j < COLUMNS; ++j) {
            m_mat[i][j] = a_mat[i][j];
            m_sumMat[i][j] = a_mat[i][j];
        }

    }

    fillSumMat();
    
} catch(...) {
    throw;
}

Matrix::~Matrix()
{
    freeAll(m_rows);
}

bool Matrix::SubSum(size_t a_fromRow, size_t a_fromCol, size_t a_toRow, size_t a_toCol, int& a_result)
{
    if(a_fromRow > a_toRow || a_fromCol > a_toCol || a_toRow >= m_rows || a_toCol >= COLUMNS) {
        return false;
    }

    if((m_rows - 1) == a_toRow) {
        if((COLUMNS - 1) == a_toCol) {
            a_result = m_sumMat[a_fromRow][a_fromCol];
        }
        else {
            a_result = m_sumMat[a_fromRow][a_fromCol] - m_sumMat[a_fromRow][a_toCol + 1];
        }
    }

    else if((COLUMNS - 1) == a_toCol) {
        a_result = m_sumMat[a_fromRow][a_fromCol] - m_sumMat[a_toRow + 1][a_fromCol];
    }

    else {
        a_result = m_sumMat[a_fromRow][a_fromCol] - m_sumMat[a_toRow + 1][a_fromCol] 
                    - m_sumMat[a_fromRow][a_toCol + 1] + m_sumMat[a_toRow + 1][a_toCol + 1];
    }
    
    return true;
}

int Matrix::operator[](pair<size_t, size_t> a_ij) const
{
    if(a_ij.first >= m_rows) {
        a_ij.first = m_rows - 1;
    }

    if(a_ij.second >= COLUMNS) {
        a_ij.second = COLUMNS - 1;
    }

    return m_mat[a_ij.first][a_ij.second];
}

// private:

void Matrix::allocateNext(size_t a_indx)
{
    try {
        m_mat[a_indx] = new int[COLUMNS];
    } catch(...) {
        freeAll(a_indx);
        throw;
    }

    try {
        m_sumMat[a_indx] = new int[COLUMNS];
    } catch(...) {
        delete m_mat[a_indx];
        freeAll(a_indx);
        throw;
    }
}

void Matrix::freeAll(size_t a_to)
{
    for(size_t i = 0; i < a_to; ++i) {
        delete m_mat[i];
        delete m_sumMat[i];
    }
    delete [] m_mat;
    delete [] m_sumMat;
}

void Matrix::fillSumMat()
{
    for(size_t i = COLUMNS - 1; i > 0; --i) {
        m_sumMat[m_rows - 1][i - 1] += m_sumMat[m_rows - 1][i];
    }
    
    for(size_t i = m_rows - 1; i > 0; --i) {
        m_sumMat[i - 1][COLUMNS - 1] += m_sumMat[i][COLUMNS - 1];
    }

    for(size_t i = m_rows - 1; i > 0; --i) {
        for(size_t j = COLUMNS - 1; j > 0; --j) {
            m_sumMat[i - 1][j - 1] += (m_sumMat[i][j - 1] + m_sumMat[i - 1][j] - m_sumMat[i][j]);
        }
    }
}

} // iq