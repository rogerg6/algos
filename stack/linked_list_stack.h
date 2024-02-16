

#ifndef LINKED_LIST_STACK_H
#define LINKED_LIST_STACK_H

#include <stdexcept>

/**
 * \brief: 基于链表实现的栈
 */
class LinkedListStack {
public:
    LinkedListStack()
        : _head(nullptr)
        , _size(0) {}

    ~LinkedListStack() {
        while (_head) {
            Node *tmp = _head;
            _head     = _head->next;
            delete tmp;
            _size--;
        }
        _head = nullptr;
    }

    void Push(int val) {
        Node *node = new Node(val);
        if (!node) throw std::runtime_error("alloc Node error");

        node->next = _head;
        _head      = node;
        _size++;
    }

    int Pop() {
        int   val = Peek();
        Node *tmp = _head;
        _head     = tmp->next;
        delete tmp;
        _size--;
        return val;
    }

    int Peek() const {
        if (_size <= 0) throw std::runtime_error("stack is empty");
        return _head->val;
    }

    int  Size() const { return _size; }
    bool Empty() const { return _size <= 0; }

private:
    /* 链表节点类 */
    struct Node {
        int          val;
        struct Node *next;
        Node(int v)
            : val(v)
            , next(nullptr) {}
        ~Node() {}
    };

private:
    Node *_head;
    int   _size;
};


#endif