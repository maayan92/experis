#include "arrayAndString.hpp"
#include <climits>
#include <cstring>
#include <sstream>
#include <set>

namespace iq {

// Q2:

static bool CheckResult(const int* a_checkFirst, const int* a_checkSecond, size_t a_size)
{
    for(size_t i = 0; i < a_size; ++i) {
        if(a_checkFirst[i] != a_checkSecond[i]) {
            return false;
        }
    }

    return true;
}

bool CheckPermutation(const char* a_first, const char* a_second)
{
    if((!a_first && a_second) || (a_first && !a_second)) {
        return false;
    }

    int checkFirst[256] = {0};
    int checkSecond[256] = {0};

    int valFirst = *a_first;
    int valSecond = *a_second;
    while(valFirst != '\0' && valSecond != '\0') {
        ++checkFirst[valFirst];
        ++checkSecond[valSecond];

        valFirst = *++a_first;
        valSecond = *++a_second;
    }
    
    if((valFirst == '\0' && valSecond != '\0') || (valFirst != '\0' && valSecond == '\0')) {
        return false;
    }

    return CheckResult(checkFirst, checkSecond, 256);
}

// Q3:

static size_t CountSpaces(char* a_str, size_t a_size)
{
    size_t countSpaces = 0;
    
    size_t i = 0;
    while(i < a_size) {
        if(a_str[i++] == ' ') {
            countSpaces += 2;
        }
    }

    return countSpaces;
}

bool URLify(char* a_str, size_t a_size)
{
    if(!a_str || !a_size) {
        return false;
    }

    size_t spaces = CountSpaces(a_str, a_size);

    size_t i = a_size - 1;
    while(spaces > 0) {
        a_str[i + spaces] = a_str[i];
        if(a_str[i] == ' ') {
            a_str[i + spaces] = '0';
            a_str[i + (--spaces)] = '2';
            a_str[i + (--spaces)] = '%';
        }
        --i;
    }

    return true;
}

// Q4:

static bool SetStrBits(const char* a_first, const char* a_second, long& a_resultFirst, long& a_resultSecond)
{
    size_t i = 0;
    while(a_first[i] != '\0' && a_second[i] != '\0') {
        a_resultFirst ^= (1L << (a_first[i] - 'A'));
        a_resultSecond ^= (1L << (a_second[i] - 'A'));

        ++i;
    }

    if(a_first[i] != '\0' || a_second[i] != '\0') {
        return false;
    }

    return true;
}

bool PalindromePermutation(const char* a_first, const char* a_second)
{
    if(!a_first || !a_second) {
        return false;
    }

    long resultFirst = 0;
    long resultSecond = 0;
    
    return SetStrBits(a_first, a_second, resultFirst, resultSecond) && resultFirst == resultSecond;
}

// Q5:

bool OneAway(const char* a_first, const char* a_second)
{
    if(!a_first || !a_second) {
        return false;
    }

    long resultFirst = 0;
    long resultSecond = 0;

    if(!SetStrBits(a_first, a_second, resultFirst, resultSecond)) {
        size_t sizeFirst = strlen(a_first);
        size_t sizeSecond = strlen(a_second);

        if(sizeFirst > (sizeSecond + 1) || sizeSecond > (sizeFirst + 1)) {
            return false;
        }
    }

    resultFirst ^= resultSecond;
    return (0 == resultFirst) || (0 == (resultFirst & (resultFirst - 1)));
}

// Q6:

static void CopyCountToString(std::string& a_compressed, size_t a_count)
{
    std::stringstream str;
    str << a_count;
    a_compressed += str.str();
}

bool StringCompression(char* a_str)
{
    if(!a_str || a_str[0] == '\0') {
        return false;
    }

    std::string compressed;
    compressed += a_str[0];

    size_t count = 1;
    size_t i = 1;
    for(; a_str[i] != '\0'; ++i) {
        if(a_str[i] != a_str[i - 1]) {
            CopyCountToString(compressed, count);
            compressed += a_str[i];
            count = 1;
        }
        else {
            ++count;
        }
    }
    CopyCountToString(compressed, count);

    if(compressed.size() < i) {
        strcpy(a_str, compressed.c_str());
        return true;
    }

    return false;
}

// Q7:

static void SetValue(int mat[SIZE][SIZE], int& a_valSave, size_t& a_row, size_t& a_column)
{
    int valSet = a_valSave;
    a_valSave = mat[a_row][a_column];
    mat[a_row][a_column] = valSet;

    size_t prevRow = a_row;
    a_row = a_column;
    a_column = SIZE - prevRow - 1;
}

static void MoveValues(int mat[SIZE][SIZE], size_t a_row, size_t a_column)
{
    size_t nextColumn = SIZE - 1 - a_row;
    int valSave = mat[a_row][a_column];
    
    SetValue(mat, valSave, a_column, nextColumn);
    SetValue(mat, valSave, a_column, nextColumn);
    SetValue(mat, valSave, a_column, nextColumn);
    SetValue(mat, valSave, a_column, nextColumn);
}

bool RotateMatrix(int mat[SIZE][SIZE])
{
    if(!SIZE) {
        return false;
    }

    size_t border = SIZE / 2;
    size_t i = 0;

    for(; i < border; ++i) {
        for(size_t j = i; j < (SIZE - i - 1); ++j) {
            MoveValues(mat, i, j);
        }
    }

    return true;
}

// Q8:

static void zeroRow(int mat[SIZE][SIZE], size_t a_row)
{
    for(size_t column = 0; column < SIZE; ++column) {
        mat[a_row][column] = 0;
    }
}

static void zeroColumn(int mat[SIZE][SIZE], size_t a_column)
{
    for(size_t row = 0; row < SIZE; ++row) {
        mat[row][a_column] = 0;
    }
}

bool ZeroMatrix(int mat[SIZE][SIZE])
{
    if(!SIZE) {
        return false;
    }

    std::set<std::pair<size_t, size_t> > positions;
    typedef std::set<std::pair<size_t, size_t> >::iterator Itr;

    for(size_t i = 0; i < SIZE; ++i) {
        for(size_t j = 0; j < SIZE; ++j) {
            if(0 == mat[i][j]) {
                positions.insert(std::make_pair(i, j));
            }
        }
    }

    Itr itr = positions.begin();
    Itr end = positions.end();
    for(; itr != end; ++itr) {
        zeroRow(mat, itr->first);
        zeroColumn(mat, itr->second);
    }

    return true;
}

// Q9:

static bool CheckStrings(const char* a_first, const char* a_second, size_t& a_firstIdx, size_t& a_secondIdx)
{
    while(a_first[a_firstIdx] != '\0' && a_second[a_secondIdx] != '\0') {
        if(a_first[a_firstIdx] != a_second[a_secondIdx]) {
            return false;
        }

        ++a_firstIdx;
        ++a_secondIdx;
    }

    return true;
}

bool StringRotation(const char* a_first, const char* a_second)
{
    if(!a_first || !a_second || '\0' == a_first[0] || '\0' == a_second[0]) {
        return false;
    }

    size_t firstIdx = 0;
    while(a_first[firstIdx] != a_second[0] && a_first[firstIdx] != '\0') {
        ++firstIdx;
    }

    size_t saveFirstIdx = firstIdx;
    size_t secondIdx = 0;
    
    return (a_first[firstIdx] != '\0') &&
            CheckStrings(a_first, a_second, firstIdx, secondIdx) &&
            CheckStrings(a_first, a_second, firstIdx = 0, secondIdx) &&
            (firstIdx == saveFirstIdx);
}

} // iq