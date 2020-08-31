namespace experis {

template<typename T>
Atomic<T>::Atomic(T a_value)
: m_element(a_value)
{
        assert((sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8) && \
                "T must be char, int, short, long");
}

template<typename T>
Atomic<T>::Atomic(const Atomic& a_atomic)
{
    m_element = (T)a_atomic;
}

template<typename T>
Atomic<T>& Atomic<T>::operator=(const Atomic& a_atomic) {
    __sync_val_compare_and_swap(&m_element, m_element, a_atomic.m_element);
}

template<typename T>
T Atomic<T>::operator++() {
    return __sync_add_and_fetch(&m_element, 1);
}

template<typename T>
T Atomic<T>::operator--() {
    return __sync_sub_and_fetch(&m_element, 1);
}

template<typename T>
Atomic<T>::operator T() const {
    return __sync_add_and_fetch(const_cast<T*>(&m_element), 0);
}

} // experis