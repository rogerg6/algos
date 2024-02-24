
#include "linked_list_stack.h"
#include "list_stack.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(linked_list_stack, function_test) {
    LinkedListStack<int> l;
    EXPECT_TRUE(l.Empty());

    l.Push(1);
    l.Push(2);
    l.Push(3);
    EXPECT_EQ(l.Size(), 3);
    EXPECT_FALSE(l.Empty());
    EXPECT_EQ(l.Peek(), 3);

    EXPECT_EQ(l.Pop(), 3);
    EXPECT_EQ(l.Size(), 2);
    EXPECT_EQ(l.Pop(), 2);
    EXPECT_EQ(l.Size(), 1);
    EXPECT_EQ(l.Pop(), 1);
    EXPECT_EQ(l.Size(), 0);
    EXPECT_TRUE(l.Empty());
}

TEST(list_stack, function_test) {
    ListStack<int> l;
    EXPECT_TRUE(l.Empty());

    l.Push(1);
    l.Push(2);
    l.Push(3);
    EXPECT_EQ(l.Size(), 3);
    EXPECT_FALSE(l.Empty());
    EXPECT_EQ(l.Peek(), 3);

    EXPECT_EQ(l.Pop(), 3);
    EXPECT_EQ(l.Size(), 2);
    EXPECT_EQ(l.Pop(), 2);
    EXPECT_EQ(l.Size(), 1);
    EXPECT_EQ(l.Pop(), 1);
    EXPECT_EQ(l.Size(), 0);
    EXPECT_TRUE(l.Empty());
}