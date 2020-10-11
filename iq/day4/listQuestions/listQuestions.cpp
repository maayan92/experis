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

} // iq