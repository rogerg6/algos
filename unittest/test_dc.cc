
#include "dc.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(binary_search_recur, function_test) {
    std::vector<int> vi = {2, 3, 4, 6, 7, 8, 9, 10};
    EXPECT_EQ(binary_search_dc(vi, 2), 0);
    EXPECT_EQ(binary_search_dc(vi, 10), vi.size() - 1);
    EXPECT_EQ(binary_search_dc(vi, 6), 3);
    EXPECT_EQ(binary_search_dc(vi, 11), -1);
    EXPECT_EQ(binary_search_dc(vi, 0), -1);
    EXPECT_EQ(binary_search_dc(vi, 5), -1);
}

TEST(build_binary_tree_from_pre_inorder, testing) {

    std::vector<int> preorder  = std::vector<int>({3, 9, 2, 1, 7});
    std::vector<int> inorder   = std::vector<int>({9, 3, 1, 2, 7});
    std::vector<int> postorder = std::vector<int>({9, 1, 7, 2, 3});
    Node            *root      = BuildBinaryTree(preorder, inorder);

    BinaryTree btree(root);
    EXPECT_EQ(btree.PreOrderTraverse(), preorder);
    EXPECT_EQ(btree.InOrderTraverse(), inorder);
    EXPECT_EQ(btree.PostOrderTraverse(), postorder);
}

TEST(Hanoi_test, testing) {
    Hanoi(1, 'A', 'B', 'C');
    std::cout << std::endl;
    Hanoi(2, 'A', 'B', 'C');
    std::cout << std::endl;
    Hanoi(3, 'A', 'B', 'C');
    std::cout << std::endl;
    Hanoi(64, 'A', 'B', 'C');
    std::cout << std::endl;
}