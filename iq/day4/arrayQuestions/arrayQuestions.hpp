#ifndef ARRAY_QUESTIONS_HPP
#define ARRAY_QUESTIONS_HPP

#include <iosfwd>

namespace iq {

void SetImportantValues(int* a_someImportant, size_t a_firstSize, int* a_allImportant, size_t a_secondSize);

void SetImportantValuesSorted(int* a_someImportant, int a_firstSize, int* a_allImportant, int a_secondSize);

} // iq

#endif