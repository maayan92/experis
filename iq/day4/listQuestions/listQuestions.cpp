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

} // iq