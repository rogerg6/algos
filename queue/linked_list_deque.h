
#ifndef _LINKED_LIST_DEQUE_H
#define _LINKED_LIST_DEQUE_H

#include <stdexcept>


/**
 * \brief: 双向链表实现的双向队列. 2端都可以入对出对
 */
class LinkedListDeque {
public:
    LinkedListDeque()
        : _head(nullptr)
        , _tail(nullptr)
        , _size(0) {}
    ~LinkedListDeque() {
        while (_head) {
            Node *p = _head;
            _head   = _head->next;
            delete p;
            _size--;
        }
        _head = _tail = nullptr;
    }

    void PushHead(int val) { Push(val, true); }
    void PushTail(int val) { Push(val, false); }
    int  PopHead() { return Pop(true); }
    int  PopTail() { return Pop(false); }

    int PeekHead() const { return Peek(true); }
    int PeekTail() const { return Peek(false); }

    bool Empty() const { return _size <= 0; }
    int  Size() const { return _size; }

private:
    inline void Push(int val, bool is_head) {
        Node *p = new Node(val);
        if (!p) throw std::runtime_error("New Node failed");

        if (_size <= 0) {
            _head = _tail = p;
        } else if (is_head) {
            p->next     = _head;
            _head->prev = p;
            _head       = p;
        } else {
            _tail->next = p;
            p->prev     = _tail;
            _tail       = p;
        }
        _size++;
    }

    inline int Pop(bool is_head) {
        int val = Peek(is_head);

        Node *p;
        if (is_head) {
            p     = _head;
            _head = p->next;
            if (_head) _head->prev = nullptr;
        } else {
            p     = _tail;
            _tail = p->prev;
            if (_tail) _tail->next = nullptr;
        }

        delete p;
        _size--;

        return val;
    }

    inline int Peek(bool is_head) const {
        if (_size <= 0) throw std::runtime_error("Deque is empty");
        if (is_head)
            return _head->val;
        else
            return _tail->val;
    }

private:
    struct Node {
        int          val;
        struct Node *prev;
        struct Node *next;
        Node(int v)
            : val(v)
            , prev(nullptr)
            , next(nullptr) {}
    };

    Node *_head, *_tail;
    int   _size;
};


#endif