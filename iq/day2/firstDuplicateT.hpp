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
bool FindDuplicateElement(const Container& a_container, typename Container::value_type& a_result)
{
    typedef std::tr1::unordered_set<typename Container::value_type, HashFunc, Equal> Seen;
    typedef typename Seen::iterator SeenItr;
    typedef typename Container::const_reverse_iterator CItr;

    Seen hasSeen;
    SeenItr seenEnd = hasSeen.end();
    CItr ritr = a_container.rbegin();
    CItr rend = a_container.rend();

    CItr where = rend;
    while(ritr != rend) {
        SeenItr found = hasSeen.find(*ritr);
        if(found != seenEnd) {
            where = ritr;
        }
        else {
            hasSeen.insert(*ritr); 
        }
        ++ritr;
    }

    if(where == rend) {
        return false;
    }

    a_result = *where;
    return true;
}

} // iq

#endif