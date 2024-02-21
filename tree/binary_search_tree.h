
#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

#include "linked_list_queue.h"
#include <stdexcept>

template<typename T>
struct BSNode {
    T       val;
    BSNode *left;
    BSNode *right;
    BSNode(T v)
        : val(v)
        , left(nullptr)
        , right(nullptr) {}
};

/**
 * \brief: 二叉搜索树的链表实现.
 *
 * 定义:
 * 1. 对于根节点，左子树中所有节点的值 < 根节点的值 < 右子树中所有节点的值。
 * 2. 任意节点的左、右子树也是二叉搜索树，即同样满足条件1
 *
 * 支持泛型.
 * add,remove,find: 时间复杂度=O(log n)
 *
 * 但是在高频的add/remove操作下,可能会退化为链表(O(n))
 **/
template<typename T>
class BinarySearchTree {
public:
    BinarySearchTree()
        : _root(nullptr)
        , _size(0) {}

    ~BinarySearchTree() {
        // while (_root) Remove(_root->val);
        destroy(_root);
        _root = nullptr;
        _size = 0;
    }

    int Size() const { return _size; }

    void Insert(const T val) {
        BSNode<T>  *node = _root;
        BSNode<T> **pre  = &_root;   // node的父节点的left/right的地址
        // find the place to insert
        while (node) {
            if (node->val == val)
                return;
            else if (val < node->val) {
                pre  = &(node->left);
                node = node->left;
            } else {
                pre  = &(node->right);
                node = node->right;
            }
        }
        BSNode<T> *newnode = new BSNode<T>(val);
        if (!newnode) throw std::runtime_error("Failed to new Node.");
        *pre = newnode;
        _size++;
    }

    void Remove(const T val) {
        BSNode<T>  *node  = _root;    // node是待删除的点
        BSNode<T> **child = &_root;   // node的父节点的child成员的地址

        // find
        while (node) {
            if (node->val == val)
                break;
            else if (val < node->val) {
                child = &(node->left);
                node  = node->left;
            } else {
                child = &(node->right);
                node  = node->right;
            }
        }
        if (!node) return;   // not found

        if (node->left == nullptr && node->right == nullptr) {
            // leaf节点
            delete node;
            *child = nullptr;
            _size--;
        } else if (node->left == nullptr && node->right) {
            // 只有right子树. 交换left子树最大的值和node的值, 删除left子树最大值的节点
            BSNode<T> *rn = node->right;
            while (rn->left) {
                rn = rn->left;
            }

            T tmp = rn->val;
            Remove(tmp);
            node->val = tmp;
        } else {
            /*
             * 2case: only left_tree || 有left_tree和right_tree.
             * 2种情况操作一样
             *
             * 度=2. 选取left_tree最大值和right_tree最小值都可以.
             * 这里我们选left_tree.max
             * 交换left子树最大的值和node的值, 删除left子树最大值的节点
             */
            BSNode<T> *ln = node->left;
            while (ln->right) {
                ln = ln->right;
            }

            T tmp = ln->val;
            Remove(tmp);
            node->val = tmp;
        }
    }

    BSNode<T> *Find(const T val) const {
        BSNode<T> *node = _root;
        while (node) {
            if (node->val == val)
                return node;
            else if (val < node->val)
                node = node->left;
            else
                node = node->right;
        }
        return nullptr;
    }

    std::vector<T> LevelOrderTraverse() const {
        std::vector<T> order;
        if (!_root) return std::vector<T>{};
        LinkedListQueue<BSNode<T> *> q;
        q.Push(_root);

        while (!q.Empty()) {
            BSNode<T> *node = q.Pop();
            order.push_back(node->val);

            BSNode<T> *l = node->left;
            if (l) q.Push(l);
            BSNode<T> *r = node->right;
            if (r) q.Push(r);
        }

        return order;
    }
    std::vector<T> PreOrderTraverse() const {
        std::vector<T> ret;
        doPreOrder(_root, ret);
        return ret;
    }
    std::vector<T> InOrderTraverse() const {
        std::vector<T> ret;
        doInOrder(_root, ret);
        return ret;
    }
    std::vector<T> PostOrderTraverse() const {
        std::vector<T> ret;
        doPostOrder(_root, ret);
        return ret;
    }

private:
    void doPreOrder(BSNode<T> *root, std::vector<T> &order) const {
        if (!root) return;
        order.push_back(root->val);
        doPreOrder(root->left, order);
        doPreOrder(root->right, order);
    }
    void doInOrder(BSNode<T> *root, std::vector<T> &order) const {
        if (!root) return;
        doInOrder(root->left, order);
        order.push_back(root->val);
        doInOrder(root->right, order);
    }
    void doPostOrder(BSNode<T> *root, std::vector<T> &order) const {
        if (!root) return;
        doPostOrder(root->left, order);
        doPostOrder(root->right, order);
        order.push_back(root->val);
    }

    // 销毁树
    void destroy(BSNode<T> *root) {
        if (!root) return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }

    BSNode<T> *_root;
    int        _size;
};

#endif