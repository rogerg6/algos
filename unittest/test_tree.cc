
#include "array_binary_tree.h"
#include "binary_search_tree.h"
#include "binary_tree.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/**
 * 测试各种二叉树的遍历顺序是否正确
 * TREE遍历接口必须一致, T是TREE中保存的值的类型
 */
template<typename TREE, typename T>
void test_traverse(const TREE &t, const std::vector<T> level_order, const std::vector<T> pre_order,
                   const std::vector<T> in_order, const std::vector<T> post_order) {
    EXPECT_EQ(t.LevelOrderTraverse(), level_order);
    EXPECT_EQ(t.PreOrderTraverse(), pre_order);
    EXPECT_EQ(t.InOrderTraverse(), in_order);
    EXPECT_EQ(t.PostOrderTraverse(), post_order);
}

TEST(binary_tree, traverse) {
    BinaryTree t;
    Node      *n1 = new Node(1);
    Node      *n2 = new Node(2);
    Node      *n3 = new Node(3);
    Node      *n4 = new Node(4);
    Node      *n5 = new Node(5);
    Node      *n6 = new Node(6);
    Node      *n7 = new Node(7);
    n2->left      = n4;
    n2->right     = n5;
    n3->left      = n6;
    n3->right     = n7;
    n1->left      = n2;
    n1->right     = n3;
    t._root       = n1;

    std::vector<int> level_order = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> pre_order   = {1, 2, 4, 5, 3, 6, 7};
    std::vector<int> in_order    = {4, 2, 5, 1, 6, 3, 7};
    std::vector<int> post_order  = {4, 5, 2, 6, 7, 3, 1};

    t.order.clear();
    t.LevelOrderTraverse();
    EXPECT_EQ(t.order, level_order);

    t.order.clear();
    t.PreOrderTraverse();
    EXPECT_EQ(t.order, pre_order);

    t.order.clear();
    t.InOrderTraverse();
    EXPECT_EQ(t.order, in_order);

    t.order.clear();
    t.PostOrderTraverse();
    EXPECT_EQ(t.order, post_order);

    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;
    delete n7;
}

TEST(array_binary_tree, traverse) {
    ArrayBinaryTree t(std::vector<int>{1, 2, 3, 4, 5, 6, 7});

    std::vector<int> level_order = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> pre_order   = {1, 2, 4, 5, 3, 6, 7};
    std::vector<int> in_order    = {4, 2, 5, 1, 6, 3, 7};
    std::vector<int> post_order  = {4, 5, 2, 6, 7, 3, 1};

    EXPECT_EQ(t.Size(), 7);
    for (int i = 0; i < level_order.size(); i++) {
        EXPECT_EQ(level_order[i], t.Val(i));
        EXPECT_EQ(2 * i + 1, t.Left(i));
        EXPECT_EQ(2 * i + 2, t.Right(i));
    }
    EXPECT_EQ(t.Val(-1), __INT_MAX__);
    EXPECT_EQ(t.Val(8), __INT_MAX__);

    t.order.clear();
    t.LevelOrderTraverse();
    EXPECT_EQ(t.order, level_order);

    t.order.clear();
    t.PreOrderTraverse();
    EXPECT_EQ(t.order, pre_order);

    t.order.clear();
    t.InOrderTraverse();
    EXPECT_EQ(t.order, in_order);

    t.order.clear();
    t.PostOrderTraverse();
    EXPECT_EQ(t.order, post_order);
}


TEST(binary_search_tree, function_test) {
    BinarySearchTree<int> t;
    std::vector<int>      nums = {5, 4, 7, 2, 6, 9, 1, 3, 8, 10};
    for (auto n : nums) t.Insert(n);
    for (auto n : nums) EXPECT_TRUE(t.Find(n) != nullptr);
    EXPECT_TRUE(t.Find(11) == nullptr);
    EXPECT_EQ(t.Size(), 10);
    test_traverse<BinarySearchTree<int>, int>(t,
                                              nums,
                                              {5, 4, 2, 1, 3, 7, 6, 9, 8, 10},
                                              {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                              {1, 3, 2, 4, 6, 8, 10, 9, 7, 5});
    t.Remove(6);   // remove leaf node
    EXPECT_EQ(t.Size(), 9);
    test_traverse<BinarySearchTree<int>, int>(t,
                                              {5, 4, 7, 2, 9, 1, 3, 8, 10},
                                              {5, 4, 2, 1, 3, 7, 9, 8, 10},
                                              {1, 2, 3, 4, 5, 7, 8, 9, 10},
                                              {1, 3, 2, 4, 8, 10, 9, 7, 5});
    t.Remove(7);   // remove node has right tree
    EXPECT_EQ(t.Size(), 8);
    test_traverse<BinarySearchTree<int>, int>(t,
                                              {5, 4, 8, 2, 9, 1, 3, 10},
                                              {5, 4, 2, 1, 3, 8, 9, 10},
                                              {1, 2, 3, 4, 5, 8, 9, 10},
                                              {1, 3, 2, 4, 10, 9, 8, 5});
    t.Remove(4);   // remove node has left tree
    EXPECT_EQ(t.Size(), 7);
    test_traverse<BinarySearchTree<int>, int>(t,
                                              {5, 3, 8, 2, 9, 1, 10},
                                              {5, 3, 2, 1, 8, 9, 10},
                                              {1, 2, 3, 5, 8, 9, 10},
                                              {1, 2, 3, 10, 9, 8, 5});
    t.Insert(4);
    EXPECT_EQ(t.Size(), 8);
    t.Remove(5);   // remove node has two child tree
    EXPECT_EQ(t.Size(), 7);
    test_traverse<BinarySearchTree<int>, int>(t,
                                              {4, 3, 8, 2, 9, 1, 10},
                                              {4, 3, 2, 1, 8, 9, 10},
                                              {1, 2, 3, 4, 8, 9, 10},
                                              {1, 2, 3, 10, 9, 8, 4});
}