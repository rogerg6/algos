#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct ListNode {
    int              val;
    struct ListNode *next;

    ListNode(int v)
        : val(v)
        , next(nullptr) {}
};

class LinkedList {
public:
    LinkedList()
        : _head(nullptr)
        , _size(0) {}

    ~LinkedList() {
        while (_head) {
            ListNode *cur = _head;
            _head         = _head->next;
            delete cur;
        }
        _head = nullptr;
        _size = 0;
    }

    /**
     * \brief 查找节点值为val的节点
     * \retval: NULL if not found
     */
    ListNode *Find(int val) {
        for (ListNode *p = _head; p; p = p->next)
            if (p->val == val) return p;
        return nullptr;
    }

    /**
     * \brief: 在n0后插入节点p
     */
    void Insert(ListNode *n0, ListNode *p) {
        p->next  = n0->next;
        n0->next = p;
        _size++;
    }

    /**
     * \brief: 删除节点n0之后的首个节点
     */
    void Remove(ListNode *n0) {
        if (n0->next == nullptr) return;

        ListNode *tmp = n0->next;
        n0->next      = tmp->next;
        delete tmp;
        _size--;
    }

    /**
     * \brief: 返回第index个节点
     */
    ListNode *Access(int index) {
        if (index >= _size) return nullptr;

        ListNode *p = _head;
        for (int i = 0; i < index; ++i) p = p->next;
        return p;
    }

    unsigned int Size() const { return _size; }

private:
    ListNode    *_head;
    unsigned int _size;
};

#endif