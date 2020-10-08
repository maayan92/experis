#include  "firstDuplicateT.hpp"
using namespace std;
using namespace tr1;

namespace iq {

template<typename Container, typename HashFunc, typename Equal>
bool FindDuplicateElement(const Container& a_container, typename Container::value_type& a_result)
{
    typedef unordered_set<typename Container::value_type, HashFunc, Equal> Seen;
    typedef typename Seen::iterator SeenItr;
    typedef typename Container::const_iterator CItr;

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