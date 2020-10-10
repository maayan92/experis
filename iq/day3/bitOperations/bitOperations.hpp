#ifndef BIT_OPERATIONS_HPP
#define BIT_OPERATIONS_HPP

#include <vector>
#include "singleton.hpp"

namespace iq {

void ReverseBits(int& a_number);

void SwapAdjacentBits(long& a_number);

bool Majority(int a_number);

bool MajorityUsingLut(int a_number);

class LutCount : private experis::Uncopyable {
    friend advcpp::Singleton<LutCount>;
public:
    //~LutCount() = default;
    
    size_t GetNumberOfOnBits(unsigned char a_number);

private:
    LutCount();

    void buildLut();

private:
    static const size_t CHAR_BITS = 256;

    std::vector<unsigned char> m_lut;
};

} // iq

#endif