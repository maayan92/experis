#include "list.hpp"
#include <stack>
using namespace std;

namespace iq {

// Q1:

bool RemoveDuplicates(Node* a_head)
{
    if(!a_head) {
        return false;
    }

    auto ptr = a_head;
    
    while(ptr->m_next) {
        auto search = ptr;
        while(search->m_next) {
            if(search->m_next->m_data == ptr->m_data) {
                search->m_next = search->m_next->m_next;
            }
            else {
                search = search->m_next;
            }
        }

        ptr = ptr->m_next;
    }

    return true;
}

// Q2:

Node* ReturnKthToLast(Node* a_head, size_t a_kFromLast)
{
    if(!a_head || !a_kFromLast) {
        return 0;
    }

    size_t count = 0;
    auto node = a_head;

    while(node) {
        ++count;
        node = node->m_next;
    }

    count -= a_kFromLast;
    auto result = a_head;
    while(count) {
        --count;
        result = result->m_next;
    }

    return result;
}

// Q3:

bool DeleteMiddleNode(Node* a_nodeToRemove)
{
    if(!a_nodeToRemove) {
        return false;
    }

    Node* next = a_nodeToRemove->m_next;
    a_nodeToRemove->m_data = next->m_data;
    a_nodeToRemove->m_next = next->m_next;

    return true;
}

// Q4:

static void FindFirstSmaller(Node* a_head, int a_pivot)
{
    if(a_head->m_data >= a_pivot) {
        return;
    }
    
    while(a_head->m_next && a_head->m_next->m_data < a_pivot) {
        a_head = a_head->m_next;
    }
}

static void MoveSmallersToLeft(Node*& a_right, Node* a_left, int a_pivot)
{
    while(a_right->m_next) {
        if(a_right->m_next->m_data < a_pivot) {
            Node* save = a_left->m_next;
            a_left->m_next = a_right->m_next;
            a_right->m_next = a_right->m_next->m_next;
            a_left->m_next->m_next = save;
        }
        else {
            a_right = a_right->m_next;
        }
    }
}

bool Partition(Node*& a_head, int a_pivot)
{
    if(!a_head) {
        return false;
    }

    Node* left = a_head;
    FindFirstSmaller(left, a_pivot);

    Node* right = left->m_next;
    MoveSmallersToLeft(right, left, a_pivot);

    if(left == a_head && left->m_data >= a_pivot) {
        right->m_next = left;
        a_head = a_head->m_next;
        left->m_next = 0;
    }

    return true;
}

// Q5:

static Node* SetResultToList(size_t a_number)
{
    Node* head = new Node(a_number % 10);
    a_number /= 10;
    Node* last = head;

    while(a_number) {
        Node* node = new Node(a_number % 10);
        last->m_next = node;
        last = last->m_next;
        a_number /= 10;
    }

    return head;
}

static void SetTheRest(Node* a_node, size_t& a_number, size_t a_pivot)
{
    while(a_node) {
        a_number += (a_node->m_data * a_pivot);

        a_pivot *= 10;
        a_node = a_node->m_next;
    }
}

Node* SumLists(Node* a_first, Node* a_second)
{
    if(!a_first || !a_second) {
        return 0;
    }

    size_t numFirst = 0;
    size_t numSecond = 0;
    size_t pivot = 1;

    while(a_first && a_second) {
        numFirst += (a_first->m_data * pivot);
        numSecond += (a_second->m_data * pivot);

        pivot *= 10;
        a_first = a_first->m_next;
        a_second = a_second->m_next;
    }

    if(a_first) {
        SetTheRest(a_first, numFirst, pivot);
    }
    if(a_second) {
        SetTheRest(a_second, numSecond, pivot);
    }

    return SetResultToList(numFirst += numSecond);
}

//

static Node* CreateNewNode(int a_value, int& a_pivot)
{
    Node* node = new Node(a_value + a_pivot);
    if(node->m_data >= 10) {
        node->m_data %= 10;
        a_pivot = 1;
    }
    else {
        a_pivot = 0;
    }

    return node;
}

static Node* SetRestNumbers(Node* a_node, int& a_pivot)
{
    if(!a_node) {
        if(a_pivot){
            return new Node(a_pivot);
        }
        return 0;
    }
    
    Node* node = CreateNewNode(a_node->m_data, a_pivot);
    node->m_next = SetRestNumbers(a_node->m_next, a_pivot);

    return node;
}

static Node* SumListsRecursion(Node* a_first, Node* a_second, int a_pivot)
{
    if(!a_first && !a_second) {
        if(a_pivot){
            return new Node(a_pivot);
        }
        return 0;
    }

    if(!a_first) {
        return SetRestNumbers(a_second, a_pivot);
    }

    if(!a_second) {
        return SetRestNumbers(a_first, a_pivot);
    }

    Node* node = CreateNewNode(a_first->m_data + a_second->m_data, a_pivot);
    node->m_next = SumListsRecursion(a_first->m_next, a_second->m_next, a_pivot);

    return node;
}

Node* SumListsRecursion(Node* a_first, Node* a_second)
{
    if(!a_first || !a_second) {
        return 0;
    }

    return SumListsRecursion(a_first, a_second, 0);
}

// Q6:

static bool CheckValues(Node* a_head, stack<int>& a_values)
{
    while(a_head) {
        if(a_head->m_data != a_values.top()) {
            return false;
        }
        a_values.pop();
        a_head = a_head->m_next;
    }

    return true;
}

bool IsPalindrome(Node* a_head)
{
    if(!a_head) {
        return false;
    }

    stack<int> values;
    Node* node = a_head;
    while(node) {
        values.push(node->m_data);
        node = node->m_next;
    }

    return CheckValues(a_head, values);
}

} // iq