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

static bool HasLoopR(Node<int> *a_fastPtr, Node<int> *a_slowPtr)
{
    if((!a_fastPtr || !a_fastPtr->m_next || !a_slowPtr)) {
        return false;
    }

    return (a_fastPtr == a_slowPtr) || HasLoopR(a_fastPtr->m_next->m_next, a_slowPtr->m_next);
}

bool HasLoop(Node<int>* a_head)
{
    if(!a_head || !a_head->m_next) {
        return false;
    }

    return HasLoopR(a_head->m_next->m_next, a_head->m_next);
}

} // iq