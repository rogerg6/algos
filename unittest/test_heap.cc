
#include "heap.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

template<typename T>
bool test_heap(const T &hp, bool is_max) {
    auto data = hp._data;
    int  len  = data.size();
    for (int i = 0; i < len; i++) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (is_max) {
            if (l < len && data[i] < data[l]) return false;
            if (r < len && data[i] < data[r]) return false;
        } else {
            if (l < len && data[i] > data[l]) return false;
            if (r < len && data[i] > data[r]) return false;
        }
    }
    return true;
}

TEST(Max_Heap, function_test) {
    MaxHeap<int>     hp;
    std::vector<int> vi;
    EXPECT_TRUE(hp.Empty());

    // push 建堆
    for (int i = 1; i < 21; i++) {
        hp.Push(i);
        EXPECT_EQ(hp.Size(), i);
        EXPECT_EQ(hp.Peek(), i);
        EXPECT_TRUE(test_heap(hp, true));
        vi.push_back(i);
    }
    EXPECT_EQ(hp.Peek(), 20);
    EXPECT_EQ(hp.Size(), 20);

    // 根据输入列表建堆
    MaxHeap<int> hp2(vi);
    EXPECT_TRUE(test_heap(hp2, true));
    EXPECT_EQ(hp2.Peek(), 20);
    EXPECT_EQ(hp2.Size(), 20);
}

TEST(Min_Heap, function_test) {
    MinHeap<int>     hp;
    std::vector<int> vi;
    EXPECT_TRUE(hp.Empty());

    // push 建堆
    for (int i = 20; i >= 1; i--) {
        hp.Push(i);
        EXPECT_EQ(hp.Size(), 21 - i);
        EXPECT_EQ(hp.Peek(), i);
        EXPECT_TRUE(test_heap(hp, false));
        vi.push_back(i);
    }
    EXPECT_EQ(hp.Peek(), 1);
    EXPECT_EQ(hp.Size(), 20);

    // 根据输入列表建堆
    MinHeap<int> hp2(vi);
    EXPECT_TRUE(test_heap(hp2, false));
    EXPECT_EQ(hp2.Peek(), 1);
    EXPECT_EQ(hp2.Size(), 20);
}
template<typename T>
std::vector<T> TopK(int k, const std::vector<T> list) {
    int len = list.size();
    assert(k <= len);

    std::vector<T> ret;
    MinHeap<T>     hp(std::vector<T>(list.begin(), list.begin() + k));
    for (int i = k; i < len; i++) {
        T val = hp.Peek();
        if (list[i] > val) {
            hp.Pop();
            hp.Push(list[i]);
        }
    }
    while (!hp.Empty()) {
        ret.push_back(hp.Pop());
    }
    return ret;
}

TEST(Min_Heap, TopK_test) {
    std::vector<int> vi;
    for (int i = 1; i < 21; i++) vi.push_back(i);

    EXPECT_EQ(TopK<int>(5, vi), std::vector<int>(vi.begin() + 15, vi.end()));
    EXPECT_EQ(TopK<int>(10, vi), std::vector<int>(vi.begin() + 10, vi.end()));
    EXPECT_EQ(TopK<int>(15, vi), std::vector<int>(vi.begin() + 5, vi.end()));
}