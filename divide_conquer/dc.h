
#ifndef __DC_H
#define __DC_H

#include "binary_tree.h"
#include <iostream>
#include <vector>

static int dfs(std::vector<int> &a, int i, int j, int target) {
    if (i > j) return -1;
    int mid = i + (j - i) / 2;

    if (a[mid] == target)
        return mid;
    else if (target < a[mid])
        return dfs(a, i, mid - 1, target);
    else
        return dfs(a, mid + 1, j, target);
}

/**
 * 使用分治的思路实现二分查找. 递归
 */
int binary_search_dc(std::vector<int> &a, int target) {
    return dfs(a, 0, a.size() - 1, target);
}

/**
 * \brief: 由前序和中序构建二叉树
 */

Node *BuildBinaryTree(std::vector<int> &preorder, std::vector<int> &inorder) {
    if (preorder.size() <= 0 || inorder.size() <= 0) return nullptr;

    int rootval = preorder[0];
    int rootidx = 0;
    for (int i = 0; i < inorder.size(); i++)
        if (inorder[i] == rootval) rootidx = i;

    int lt_size = rootidx;
    int rt_size = inorder.size() - lt_size - 1;

    std::vector<int> left_tree_preorder(preorder.begin() + 1, preorder.begin() + 1 + lt_size);
    std::vector<int> left_tree_inorder(inorder.begin(), inorder.begin() + rootidx);
    std::vector<int> right_tree_preorder(preorder.begin() + 1 + lt_size, preorder.end());
    std::vector<int> right_tree_inorder(inorder.begin() + rootidx + 1, inorder.end());

    Node *node  = new Node(rootval);
    node->left  = BuildBinaryTree(left_tree_preorder, left_tree_inorder);
    node->right = BuildBinaryTree(right_tree_preorder, right_tree_inorder);

    return node;
}

/**
 * \brief: 汉诺塔问题
 */
void Hanoi(int n, char from, char via, char to) {
    if (n <= 1) {
        std::cout << n << ": " << from << " -> " << to << std::endl;
        return;
    }

    Hanoi(n - 1, from, to, via);
    std::cout << n << ": " << from << " -> " << to << std::endl;
    Hanoi(n - 1, via, from, to);
}


#endif