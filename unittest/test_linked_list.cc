#include "linked_list.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(linked_list_test, linked_list) {
    LinkedList l;
    EXPECT_EQ(l.Size(), 0);
}