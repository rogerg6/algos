
#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "linked_list_queue.h"
#include <vector>

struct Node {
    int          val;
    struct Node *left;
    struct Node *right;
    Node(int v)
        : val(v)
        , left(nullptr)
        , right(nullptr) {}
};

/**
 * \brief: 二叉树的链表实现. 只实现了遍历, 因为对于
 *         增删改查和特定的业务逻辑相关, 故无法实现
 */
class BinaryTree {
public:
    BinaryTree()
        : _root(nullptr) {}
    ~BinaryTree() {
        // 遍历释放所有节点的内寸
    }

    void LevelOrderTraverse() {
        if (!_root) return;
        LinkedListQueue<Node *> q;
        q.Push(_root);

        while (!q.Empty()) {
            Node *node = q.Pop();
            order.push_back(node->val);

            Node *l = node->left;
            if (l) q.Push(l);
            Node *r = node->right;
            if (r) q.Push(r);
        }
    }

    void PreOrderTraverse() { DoPreOrder(_root); }
    void InOrderTraverse() { DoInOrder(_root); }
    void PostOrderTraverse() { DoPostOrder(_root); }

public:
    std::vector<int> order;   // 存储遍历的顺序, for debug/test use

#ifdef UNIT_TEST
public:
#else
private:
#endif
    void DoPreOrder(Node *root) {
        if (!root) return;
        order.push_back(root->val);
        DoPreOrder(root->left);
        DoPreOrder(root->right);
    }
    void DoInOrder(Node *root) {
        if (!root) return;
        DoInOrder(root->left);
        order.push_back(root->val);
        DoInOrder(root->right);
    }
    void DoPostOrder(Node *root) {
        if (!root) return;
        DoPostOrder(root->left);
        DoPostOrder(root->right);
        order.push_back(root->val);
    }

    Node *_root;
};




#endif