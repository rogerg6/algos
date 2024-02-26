
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

TEST(quick_sort, function_test) {
    std::vector<int> vi = {4, 3, 1, 3, 4, 5, 6};

    QuickSort(vi, 0, vi.size() - 1);
    EXPECT_EQ(vi, std::vector<int>({1, 3, 3, 4, 4, 5, 6}));

    vi = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    QuickSort_v2(vi, 0, vi.size() - 1);
    EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
    vi = {5, 2, 1, 4, 3, 10, 7, 6, 9, 8};
    QuickSort_v2(vi, 0, vi.size() - 1);
    EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
}

TEST(merge_sort, function_test) {
    std::vector<int> vi = {4, 3, 1, 3, 4, 7, 6};

    MergeSort(vi, 0, vi.size() - 1);
    EXPECT_EQ(vi, std::vector<int>({1, 3, 3, 4, 4, 6, 7}));
}

TEST(heap_sort, function_test) {
    std::vector<int> vi = {4, 3, 1, 3, 4, 7, 6};

    HeapSort(vi, 0, vi.size() - 1);
    EXPECT_EQ(vi, std::vector<int>({1, 3, 3, 4, 4, 6, 7}));
}

TEST(bucket_sort, function_test) {
    std::vector<float> vf = {0.49, 0.96, 0.82, 0.09, 0.57, 0.43, 0.91, 0.75, 0.15, 0.37};
    BucketSort(vf);
    EXPECT_EQ(vf, std::vector<float>({0.09, 0.15, 0.37, 0.43, 0.49, 0.57, 0.75, 0.82, 0.91, 0.96}));
}

TEST(counting_sort, function_test) {
    std::vector<int> vi = {4, 3, 1, 3, 4, 7, 6};

    CountingSort(vi);
    EXPECT_EQ(vi, std::vector<int>({1, 3, 3, 4, 4, 6, 7}));
}

TEST(radix_sort, function_test) {
    std::vector<int> vi = {10546151,
                           35663510,
                           42865989,
                           34862445,
                           81883077,
                           88906420,
                           72429244,
                           30524779,
                           82060337,
                           63832996};

    RadixSort(vi);
    EXPECT_EQ(vi,
              std::vector<int>({10546151,
                                30524779,
                                34862445,
                                35663510,
                                42865989,
                                63832996,
                                72429244,
                                81883077,
                                82060337,
                                88906420}));
}