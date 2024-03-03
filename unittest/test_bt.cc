// test backtracking

#include "bt.h"
#include "gtest/gtest.h"
#include <iostream>

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(permutationI, permutationI_no_repeated_elemen_Test) {
    std::vector<int> input = {1, 2, 3, 4};
    auto             res   = PermutationI(input);

    for (auto &r : res) {
        for (auto elem : r) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

TEST(permutationII, permutationI_has_repeated_elemen_Test) {
    std::vector<int> input = {1, 3, 1, 2};
    auto             res   = PermutationII(input);

    for (auto &r : res) {
        for (auto elem : r) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}