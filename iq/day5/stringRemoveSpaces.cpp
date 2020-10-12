#include "stringRemoveSpaces.hpp"
#include <iosfwd>
#include <cstring>

namespace iq {

static void FindNextSpacePosition(char* a_str, size_t& a_indx, size_t a_size)
{
  while(' ' != a_str[a_indx] && a_indx < a_size) {
    ++a_indx;
  }
  ++a_indx;
}

static void CountNumOfSpaces(char* a_str, size_t a_indx, size_t& a_numOfSpaces, size_t a_size)
{
  while(' ' == a_str[a_indx + a_numOfSpaces] && (a_indx + a_numOfSpaces) < a_size) {
    ++a_numOfSpaces;
  }
}

static void ResetValues(char* a_str, size_t& a_indx, size_t& a_numOfSpaces, size_t a_size)
{
    while(' ' != a_str[a_indx + a_numOfSpaces] && (a_indx + a_numOfSpaces) < a_size) {
      a_str[a_indx] = a_str[a_indx + a_numOfSpaces];
      a_str[a_indx + a_numOfSpaces] = ' ';
      ++a_indx;
    }
}

char* RemoveDuplicateSpaces(char* a_str)
{
  if(!a_str) {
    return a_str;
  }
  
  size_t size = strlen(a_str);
  size_t numOfSpaces = 0;
  size_t indxFrom = 0;
  
  FindNextSpacePosition(a_str, indxFrom, size);
  
  while((indxFrom + numOfSpaces) < size) {
    
    CountNumOfSpaces(a_str, indxFrom, numOfSpaces, size);
    ResetValues(a_str, indxFrom, numOfSpaces, size);
    
    ++indxFrom;
  }

  return a_str;
}

} // iq