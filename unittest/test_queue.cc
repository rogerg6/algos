
#include "array_deque.h"
#include "array_queue.h"
#include "linked_list_deque.h"
#include "linked_list_queue.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(linked_list_queue, function_test) {
    LinkedListQueue<int> q;
    EXPECT_TRUE(q.Empty());

    q.Push(1);
    q.Push(2);
    q.Push(3);
    EXPECT_EQ(q.Size(), 3);
    EXPECT_FALSE(q.Empty());
    EXPECT_EQ(q.Peek(), 1);

    EXPECT_EQ(q.Pop(), 1);
    EXPECT_EQ(q.Size(), 2);
    EXPECT_EQ(q.Pop(), 2);
    EXPECT_EQ(q.Size(), 1);
    EXPECT_EQ(q.Pop(), 3);
    EXPECT_EQ(q.Size(), 0);
    EXPECT_TRUE(q.Empty());
}

TEST(array_queue, function_test) {
    ArrayQueue q(5);
    EXPECT_TRUE(q.Empty());
    // empty
    try {
        q.Pop();
    } catch (std::runtime_error e) {
        std::cout << "Catch a exception: " << e.what() << std::endl;
    }

    q.Push(1);
    q.Push(2);
    q.Push(3);
    EXPECT_EQ(q.Size(), 3);
    EXPECT_FALSE(q.Empty());
    EXPECT_EQ(q.Peek(), 1);

    q.Push(4);
    q.Push(5);
    EXPECT_EQ(q.Size(), 5);

    // full
    try {
        q.Push(6);
    } catch (std::runtime_error e) {
        std::cout << "Catch a exception: " << e.what() << std::endl;
    }

    EXPECT_EQ(q.Pop(), 1);
    EXPECT_EQ(q.Size(), 4);
    EXPECT_EQ(q.Pop(), 2);
    EXPECT_EQ(q.Size(), 3);
    EXPECT_EQ(q.Pop(), 3);
    EXPECT_EQ(q.Size(), 2);

    q.Push(6);
    q.Push(7);
    q.Push(8);
    std::vector<int> vi = {4, 5, 6, 7, 8};
    for (int i = 0; i < vi.size(); i++) {
        EXPECT_EQ(q.Pop(), vi[i]);
        EXPECT_EQ(q.Size(), vi.size() - i - 1);
    }
    EXPECT_TRUE(q.Empty());
}

TEST(linked_list_deque, function_test) {
    LinkedListDeque q;
    EXPECT_TRUE(q.Empty());

    // 循环测试n次
    for (int i = 0; i < 5; i++) {
        // 6 4 2 1 3 5
        std::vector<int> a = {1, 2, 3, 4, 5, 6};
        for (int i = 0; i < 6; i++) {
            if (i % 2 == 0)
                q.PushTail(a[i]);
            else
                q.PushHead(a[i]);
        }
        EXPECT_FALSE(q.Empty());
        EXPECT_EQ(q.Size(), 6);

        std::vector<int> b = {5, 6, 3, 4, 1, 2};
        for (int i = 0; i < 6; i++) {
            if (i % 2 == 0) {
                EXPECT_EQ(q.PopTail(), b[i]);

            } else
                EXPECT_EQ(q.PopHead(), b[i]);

            EXPECT_EQ(q.Size(), 6 - i - 1);
        }
        EXPECT_TRUE(q.Empty());
    }
    EXPECT_TRUE(q.Empty());
}

TEST(array_deque, function_test) {
    ArrayDeque q(6);
    EXPECT_TRUE(q.Empty());
    try {
        q.PopHead();
        q.PopTail();
    } catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
    }

    // 循环测试n次
    for (int i = 0; i < 5; i++) {
        // 6 4 2 1 3 5
        std::vector<int> a = {1, 2, 3, 4, 5, 6};
        for (int i = 0; i < 6; i++) q.PushTail(a[i]);
        EXPECT_FALSE(q.Empty());
        EXPECT_EQ(q.Size(), 6);

        try {
            q.PushHead(-1);
            q.PushTail(7);
        } catch (std::runtime_error e) {
            std::cout << e.what() << std::endl;
        }

        if (i % 2 == 0) {
            EXPECT_EQ(q.PopTail(), 6);
            EXPECT_EQ(q.PopTail(), 5);
            EXPECT_EQ(q.Size(), 4);
            q.PushHead(0);
            q.PushHead(-1);
            // -1 0 1 2 3 4
            for (int i = -1; i < 5; i++) {
                EXPECT_EQ(q.PopHead(), i);
                EXPECT_EQ(q.Size(), 6 - i - 2);
            }
        } else {
            EXPECT_EQ(q.PopHead(), 1);
            EXPECT_EQ(q.PopHead(), 2);
            EXPECT_EQ(q.Size(), 4);
            q.PushTail(7);
            q.PushTail(8);
            // 3 4 5 6 7 8
            for (int i = 8; i > 2; i--) {
                EXPECT_EQ(q.PopTail(), i);
                EXPECT_EQ(q.Size(), i - 3);
            }
        }
        EXPECT_TRUE(q.Empty());
    }
    EXPECT_TRUE(q.Empty());
}