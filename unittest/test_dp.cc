#include "dp.h"
#include "gtest/gtest.h"
#include <iostream>

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(climbing_stairs, path_numbers) {
    EXPECT_EQ(ClimbingStairs(1), 1);
    EXPECT_EQ(ClimbingStairs(2), 2);
    EXPECT_EQ(ClimbingStairs(3), 3);
    EXPECT_EQ(ClimbingStairs(4), 5);
    EXPECT_EQ(ClimbingStairs(5), 8);
    EXPECT_EQ(ClimbingStairs(6), 13);
}

TEST(climbing_stairs, min_cost) {
    // cost[0]开始所在的台阶
    std::vector<int> cost = {0, 1, 10, 1};
    EXPECT_EQ(ClimbingStairsMinCost(cost), 2);
}

TEST(climbing_stairs, only121_222) {
    // cost[0]开始所在的台阶
    EXPECT_EQ(ClimbingStairsLimit(3), 2);
    EXPECT_EQ(ClimbingStairsLimit(4), 2);
}

TEST(min_path_sum, test) {
    std::vector<std::vector<int>> mat = {{1, 3, 1, 5}, {2, 2, 4, 2}, {5, 3, 2, 1}, {4, 3, 5, 2}};
    EXPECT_EQ(MinPathSum(mat), 13);
}

TEST(knaspack, knaspack_zero_one_pack_Test) {
    std::vector<int> wgt = {10, 20, 30, 40, 50};
    std::vector<int> val = {50, 120, 150, 210, 240};
    EXPECT_EQ(Knaspack(wgt, val, 50), 270);
}

TEST(knaspack, knaspack_unbounded_pack_Test) {
    std::vector<int> wgt = {10, 20, 30, 40, 50};
    std::vector<int> val = {50, 120, 150, 210, 240};
    EXPECT_EQ(UnboundedKnaspack(wgt, val, 50), 290);
}

TEST(change, change_change_min_coins_Test) {
    std::vector<int> coins = {1, 2, 5};
    EXPECT_EQ(CoinChange(coins, 11), 3);
    EXPECT_EQ(CoinChange(coins, 13), 4);
    EXPECT_EQ(CoinChange(coins, 19), 5);
    EXPECT_EQ(CoinChange(coins, 21), 5);

    coins = {3, 5, 7};
    EXPECT_EQ(CoinChange(coins, 4), -1);
}

TEST(edit_distance, test) {
    EXPECT_EQ(MinEditDis("kitten", "sitting"), 3);
    EXPECT_EQ(MinEditDis("hello", "algo"), 3);
}