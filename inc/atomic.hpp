#ifndef ATOMIC_H
#define ATOMIC_H

#include <cassert>
#include "uncopyable.hpp"

namespace experis {

class AtomicFlag : private Uncopyable {
public:
    explicit AtomicFlag(bool a_value = false);
    //~AtomicFlag() = default;

    bool CheckAndSet();
    bool GetValue() const;

private:
    mutable char m_value;
};

template<typename T>
class Atomic {
public:
    explicit Atomic(T a_value = T());
    Atomic(const Atomic& a_atomic);
    //~Atomic() = default;
    Atomic& operator=(const Atomic& a_atomic);

    T operator++();
    T operator--();
    operator T() const;

private:
    T m_element;
};

} // experis

#include "inl/atomic.hxx"

#endif