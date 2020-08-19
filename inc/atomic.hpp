#ifndef ATOMIC_H
#define ATOMIC_H

namespace experis {

template<typename T>
class Atomic {
public:
    Atomic();
    //Atomic(const Atomic& a_atomic) = default;
    //~Atomic() = default;
    Atomic& operator=(const Atomic& a_atomic);

    void operator++();
    void operator--();
    operator T() const;

private:
    T m_element;
};

template<typename T>
Atomic<T>::Atomic()
: m_element()
{
}

template<typename T>
Atomic<T>& Atomic<T>::operator=(const Atomic& a_atomic) {
    __sync_val_compare_and_swap(&m_element, m_element, a_atomic.m_element); /// ???
}

template<typename T>
void Atomic<T>::operator++() {
    __sync_add_and_fetch(&m_element, 1);
}

template<typename T>
void Atomic<T>::operator--() {
    __sync_sub_and_fetch(&m_element, 1);
}

template<typename T>
Atomic<T>::operator T() const {
    return __sync_add_and_fetch(const_cast<T*>(&m_element), 0);
}

} // experis

#endif