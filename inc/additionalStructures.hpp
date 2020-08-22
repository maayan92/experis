#ifndef ADDITIONAL_STRUCTURES_H
#define ADDITIONAL_STRUCTURES_H

namespace experis {

template<typename T>
struct Equal {
    bool operator()(const T& a_Left, const T& a_Right) const {
        return a_Left == a_Right;
    }
};

template<typename T>
struct Combine {
    T operator()(T& a_currentVal, const T& a_toAddVal) const {
        return a_currentVal += a_toAddVal;
    }
};

} // experis

#endif