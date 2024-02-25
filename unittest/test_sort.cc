
#include "sort.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(selection_sort, function_test) {
    std::vector<int> vi = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    SelectionSort(vi);
    EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
}

TEST(bubble_sort, function_test) {
    std::vector<int> vi = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    BubbleSort(vi);
    EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
    BubbleSort(vi);
    EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
}

TEST(insertion_sort, function_test) {
    std::vector<int> vi = {4, 3, 1, 3, 4, 5, 6};

    InsertionSort(vi);
    EXPECT_EQ(vi, std::vector<int>({1, 3, 3, 4, 4, 5, 6}));
}
