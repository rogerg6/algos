#ifndef __LINKED_LIST_QUEUE_H__
#define __LINKED_LIST_QUEUE_H__

#include <stdexcept>


/**
 * \brief: 链表实现的队列
 */
template<typename T>
class LinkedListQueue {
public:
    LinkedListQueue()
        : _head(nullptr)
        , _tail(nullptr)
        , _size(0) {}
    ~LinkedListQueue() {
        while (_head) {
            Node *tmp = _head;
            _head     = _head->next;
            delete tmp;
        }
    }

    void Push(T value) {
        Node *node = new Node(value);
        if (!node) throw std::runtime_error("new Node failed");

        if (_size == 0) {
            _head = node;
            _tail = node;
        } else {
            _tail->next = node;
            _tail       = node;
        }
        _size++;
    }

    T Pop() {
        T val = Peek();

        Node *p = _head;

        _head = _head->next;
        if (_size == 1) {
            _tail = nullptr;
        }
        _size--;

        delete p;
        return val;
    }

    T Peek() const {
        if (_size <= 0) throw std::runtime_error("Queue is empty");
        return _head->value;
    }

    bool Empty() const { return _size <= 0; }
    int  Size() const { return _size; }

private:
    struct Node {
        T     value;
        Node *next;
        Node(T value)
            : value(value)
            , next(nullptr) {}
        ~Node() {}
    };

    Node *_head;
    Node *_tail;
    int   _size;
};

#endif