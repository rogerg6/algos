
#include "array_binary_tree.h"
#include "binary_tree.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
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