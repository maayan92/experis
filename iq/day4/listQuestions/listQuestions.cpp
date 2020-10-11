#include "listQuestions.hpp"

namespace iq {

Node<int>* Flip(Node<int> *a_head)
{
    if(!a_head) {
        return a_head;
    }

    Node<int>* temp = Flip(a_head->m_next);

    if(!temp) {
        return a_head;
    }

    a_head->m_next->m_next = a_head;
    a_head->m_next = 0;

    return temp;
}

static bool HasLoopR(const Node<int> *a_fastPtr, const Node<int> *a_slowPtr)
{
    if((!a_fastPtr || !a_fastPtr->m_next || !a_slowPtr)) {
        return false;
    }

    return (a_fastPtr == a_slowPtr) || HasLoopR(a_fastPtr->m_next->m_next, a_slowPtr->m_next);
}

bool HasLoop(const Node<int>* a_head)
{
    if(!a_head || !a_head->m_next) {
        return false;
    }

    return HasLoopR(a_head->m_next->m_next, a_head->m_next);
}

static Node<int>* FindLoopPointR(const Node<int>* a_fastPtr, const Node<int>* a_slowPtr)
{
    if(a_fastPtr->m_next == a_slowPtr->m_next && a_fastPtr != a_slowPtr) {
        return a_fastPtr->m_next;
    }

    return FindLoopPointR(a_fastPtr->m_next->m_next, a_slowPtr->m_next);
}

Node<int>* FindLoopPoint(const Node<int>* a_head)
{
    if(!a_head || !a_head->m_next) {
        return 0;
    }

    return FindLoopPointR(a_head->m_next->m_next, a_head->m_next);
}

static size_t CountNodes(const Node<int>* a_head, const Node<int>* a_middle)
{
    Node<int>* goOver = const_cast<Node<int>* >(a_head);

    size_t count = 0;
    while(goOver != a_middle) {
        ++count;
        goOver = goOver->m_next;
    }

    do {
        ++count;
        goOver = goOver->m_next;
    } while(goOver != a_middle); 

    return count;
}

size_t ListWithLoopLength(const Node<int>* a_head)
{
    if(!a_head) {
        return 0;
    }

    if(!a_head->m_next) {
        return 1;
    }

    Node<int>* middle = FindLoopPointR(a_head->m_next->m_next, a_head->m_next);
    return CountNodes(a_head, middle);
}

} // iq