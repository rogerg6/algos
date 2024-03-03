
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
    BinaryTree(Node *root)
        : _root(root) {}
    ~BinaryTree() {
        // 遍历释放所有节点的内寸
    }

    std::vector<int> LevelOrderTraverse() {
        std::vector<int> order;

        if (!_root) return order;
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

        return order;
    }

    std::vector<int> PreOrderTraverse() {
        std::vector<int> order;
        DoPreOrder(_root, order);
        return order;
    }
    std::vector<int> InOrderTraverse() {
        std::vector<int> order;
        DoInOrder(_root, order);
        return order;
    }
    std::vector<int> PostOrderTraverse() {
        std::vector<int> order;
        DoPostOrder(_root, order);
        return order;
    }

#ifdef UNIT_TEST
public:
#else
private:
#endif
    void DoPreOrder(Node *root, std::vector<int> &order) {
        if (!root) return;
        order.push_back(root->val);
        DoPreOrder(root->left, order);
        DoPreOrder(root->right, order);
    }
    void DoInOrder(Node *root, std::vector<int> &order) {
        if (!root) return;
        DoInOrder(root->left, order);
        order.push_back(root->val);
        DoInOrder(root->right, order);
    }
    void DoPostOrder(Node *root, std::vector<int> &order) {
        if (!root) return;
        DoPostOrder(root->left, order);
        DoPostOrder(root->right, order);
        order.push_back(root->val);
    }

    Node *_root;
};




#endif