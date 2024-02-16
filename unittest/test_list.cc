#include "list.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(list_test, list) {
    List l;
    EXPECT_EQ(l.Size(), 0);

    l.Append(1);
    l.Append(2);
    l.Append(3);
    EXPECT_EQ(l.Size(), 3);
    l.print();

    l.Remove(1);
    EXPECT_EQ(l.Size(), 2);
    l.print();
}