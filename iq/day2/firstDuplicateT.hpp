#ifndef FIRST_DUPLICATE_T_HPP
#define FIRST_DUPLICATE_T_HPP
#include <iosfwd>
#include <tr1/unordered_set>

namespace iq {

template<typename Container>
struct Dummy {
    typedef typename std::tr1::unordered_set<typename Container::value_type>::hasher Hasher;
    typedef typename std::tr1::unordered_set<typename Container::value_type>::key_equal Equal;
};

template<typename Container, typename HashFunc = typename Dummy<Container>::Hasher, typename Equal = typename Dummy<Container>::Equal>
bool FindDuplicateElement(const Container& a_container, typename Container::value_type& a_result);

} // iq

#endif