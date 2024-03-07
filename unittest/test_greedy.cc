#include "greedy.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(coins_change, greedy_impl) {
    std::vector<int> coins = {1, 5, 10, 20, 50, 100};
    EXPECT_EQ(CoinChangeGreedy(coins, 131), 4);

    coins = {3, 5, 7};
    EXPECT_EQ(CoinChangeGreedy(coins, 4), -1);
}

TEST(fractional_kanspack, testing) {
    std::vector<int> wgt = {10, 20, 30, 40, 50};
    std::vector<int> val = {50, 120, 150, 210, 240};
    EXPECT_EQ(FractionalKnaspack(wgt, val, 50), 277.5);
}

TEST(max_capcity, testing) {
    std::vector<int> ht = {3, 8, 5, 2, 7, 7, 3, 4};
    EXPECT_EQ(MaxCapcity(ht), 28);
}

TEST(max_product_cutting, testing) {
    EXPECT_EQ(MaxProductCutting(2), 1);
    EXPECT_EQ(MaxProductCutting(3), 2);
    EXPECT_EQ(MaxProductCutting(4), 4);
    EXPECT_EQ(MaxProductCutting(5), 6);
    EXPECT_EQ(MaxProductCutting(6), 9);
    EXPECT_EQ(MaxProductCutting(7), 12);
    EXPECT_EQ(MaxProductCutting(8), 18);
}
