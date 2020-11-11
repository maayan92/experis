#ifndef QUESTIONS_HPP
#define QUESTIONS_HPP

#include <iosfwd>

namespace iq {

const size_t SIZE = 5;

bool CheckPermutation(const char* a_first, const char* a_second);

bool URLify(char* a_str, size_t a_size);

bool PalindromePermutation(const char* a_first, const char* a_second);

bool OneAway(const char* a_first, const char* a_second);

bool StringCompression(char* a_str);

bool RotateMatrix(int mat[SIZE][SIZE]);

bool ZeroMatrix(int mat[SIZE][SIZE]);

bool StringRotation(const char* a_first, const char* a_second);

} // iq

#endif