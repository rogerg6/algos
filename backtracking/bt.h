
#ifndef _BACKTRACKING_H
#define _BACKTRACKING_H

#include <iostream>
#include <unordered_set>
#include <vector>

/**
 * choices: 选择
 * state: 当前状态
 * selected: 选择过的点
 * res: 保存结果
 */
static void btI(const std::vector<int> &choices, std::vector<int> &state,
                std::vector<bool> &selected, std::vector<std::vector<int>> &res) {
    if (state.size() == choices.size()) {
        res.push_back(state);
    }
    for (int i = 0; i < choices.size(); i++) {
        int choice = choices[i];
        if (!selected[i]) {
            state.push_back(choice);
            selected[i] = true;
            btI(choices, state, selected, res);
            selected[i] = false;
            state.pop_back();
        }
    }
}

/**
 * \brief: 全排列. 没有重复元素
 * \retval: 全排列结果
 */
std::vector<std::vector<int>> PermutationI(const std::vector<int> &input) {
    const std::vector<int>       &choices = input;
    std::vector<int>              state;
    std::vector<bool>             selected(input.size(), false);
    std::vector<std::vector<int>> res;
    btI(choices, state, selected, res);

    return res;
}

static void btII(const std::vector<int> &choices, std::vector<int> &state,
                 std::vector<bool> &selected, std::vector<std::vector<int>> &res) {
    if (state.size() == choices.size()) {
        res.push_back(state);
    }

    std::unordered_set<int> duplicated;
    for (int i = 0; i < choices.size(); i++) {
        int choice = choices[i];

        // 索引为i的元素没有被选择过 && 同一个元素的值没有被选择过
        if (!selected[i] && duplicated.find(choice) == duplicated.end()) {
            duplicated.emplace(choice);
            state.push_back(choice);
            selected[i] = true;
            btII(choices, state, selected, res);
            selected[i] = false;
            state.pop_back();
        }
    }
}

/**
 * \brief: 全排列. 有重复元素
 * \retval: 不重复的全排列结果
 */
std::vector<std::vector<int>> PermutationII(const std::vector<int> &input) {
    const std::vector<int>       &choices = input;
    std::vector<int>              state;
    std::vector<bool>             selected(input.size(), false);
    std::vector<std::vector<int>> res;
    btII(choices, state, selected, res);

    return res;
}


#endif