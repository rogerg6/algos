#include "list.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(list_test, list) {
    List<int> l;
    EXPECT_EQ(l.Size(), 0);

    l.Append(1);
    l.Append(2);
    l.Append(3);
    EXPECT_EQ(l.Size(), 3);
    for (int i = 0; i < l.Size(); i++) EXPECT_EQ(l._data[i], i + 1);


    l.Remove(0);
    EXPECT_EQ(l.Size(), 2);
    for (int i = 0; i < l.Size(); i++) EXPECT_EQ(l._data[i], i + 2);
}