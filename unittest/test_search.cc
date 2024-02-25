
#include "binary_search.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(binary_search, function_test) {
    std::vector<int> vi = {2, 3, 4, 6, 7, 8, 9, 10};
    EXPECT_EQ(BinarySearch(vi, 2), 0);
    EXPECT_EQ(BinarySearch(vi, 10), vi.size() - 1);
    EXPECT_EQ(BinarySearch(vi, 6), 3);
    EXPECT_EQ(BinarySearch(vi, 11), -1);
    EXPECT_EQ(BinarySearch(vi, 0), -1);
    EXPECT_EQ(BinarySearch(vi, 5), -1);
}

TEST(binary_search_find_insertion, function_test) {
    std::vector<int> vi = {1, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 12, 15, 23, 26, 31, 35};
    EXPECT_EQ(BinarySearchFindInsertion(vi, 6), 2);
    vi = {1, 3, 5, 8, 12, 15, 23, 26, 31, 35};
    EXPECT_EQ(BinarySearchFindInsertion(vi, 6), 3);
    vi = {1, 6, 6, 8, 12, 15, 23, 26, 31, 35};
    EXPECT_EQ(BinarySearchFindInsertion(vi, 6), 1);
    vi = {1, 6, 8, 12, 15, 23, 26, 31, 35};
    EXPECT_EQ(BinarySearchFindInsertion(vi, 6), 1);
}

TEST(two_sum, function_test) {
    std::vector<int> vi = {5, 2, 3, 4, 7, 6};
    EXPECT_EQ(TwoSum(vi, 6), std::vector<int>({3, 1}));
    EXPECT_EQ(TwoSum(vi, 20), std::vector<int>({-1, -1}));
    EXPECT_EQ(TwoSum(vi, 0), std::vector<int>({-1, -1}));
}