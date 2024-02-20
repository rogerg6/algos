
#ifndef _ARRAY_BINARY_TREE_H
#define _ARRAY_BINARY_TREE_H


#include <vector>

/**
 * \brief: 用数组来存放二叉树.
 *         如果是完全二叉树, 则数组是连续的
 *         否则, 数组是断断续续的, 其中空的值用__INT_MAX__表示
 *
 * 二叉树的数组表示主要有以下优点。
 *      数组存储在连续的内存空间中，对缓存友好，访问与遍历速度较快。
 *      不需要存储指针，比较节省空间。
 *      允许随机访问节点。
 * 然而，数组表示也存在一些局限性。
 *      数组存储需要连续内存空间，因此不适合存储数据量过大的树。
 *      增删节点需要通过数组插入与删除操作实现，效率较低。
 *      当二叉树中存在大量 None 时，数组中包含的节点数据比重较低，空间利用率较低
 */
class ArrayBinaryTree {
public:
    ArrayBinaryTree(const std::vector<int> &v) { _tree = v; }
    ~ArrayBinaryTree() {}

    std::size_t Size() const { return _tree.size(); }

    // 返回索引为i的节点的值
    int Val(int i) const {
        if (i < 0 || i >= _tree.size()) return __INT_MAX__;
        return _tree[i];
    }

    // 返回索引为i的节点的左子节点的索引
    inline int Left(int i) const { return 2 * i + 1; }
    // 返回索引为i的节点的右子节点的索引
    inline int Right(int i) const { return 2 * i + 2; }

    void LevelOrderTraverse() {
        for (auto i = 0; i < _tree.size(); i++) {
            if (_tree[i] != __INT_MAX__) order.push_back(_tree[i]);
        }
    }

    void PreOrderTraverse() { dfs(0, ORDER::PRE_ORDER); }
    void InOrderTraverse() { dfs(0, ORDER::IN_ORDER); }
    void PostOrderTraverse() { dfs(0, ORDER::POST_ORDER); }

#ifdef UNIT_TEST
public:
#else
private:
#endif
    enum ORDER { LEVEL_ORDER, PRE_ORDER, IN_ORDER, POST_ORDER };

    void dfs(int i, ORDER odr) {
        int val = Val(i);
        if (val == __INT_MAX__) return;

        if (odr == ORDER::PRE_ORDER) order.push_back(val);
        dfs(Left(i), odr);
        if (odr == ORDER::IN_ORDER) order.push_back(val);
        dfs(Right(i), odr);
        if (odr == ORDER::POST_ORDER) order.push_back(val);
    }

    std::vector<int> order;   // 存储遍历的顺序, for debug/test use
    std::vector<int> _tree;
};


#endif