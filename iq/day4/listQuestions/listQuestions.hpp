#ifndef TREE_QUESTIONS_HPP
#define TREE_QUESTIONS_HPP

namespace iq {

template<typename T>
struct Node {

    Node(const T& a_data, Node<T>* a_next)
    : m_data(a_data)
    , m_next(a_next)
    {}
    
    Node(const T& a_data)
    : m_data(a_data)
    , m_next(0)
    {}

    Node()
    : m_data()
    , m_next(0)
    {}

    T m_data;
    Node* m_next;
};

Node<int>* Flip(Node<int> *a_head);

bool HasLoop(Node<int>* a_head);

Node<int>* FindLoopPoint(Node<int>* a_head);

} // iq

#endif