
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

static void dfs(const std::vector<int> &a, int target, int total, int start,
                std::vector<int> &state, std::vector<std::vector<int>> &res) {
    if (total == target) {
        res.push_back(state);
        return;
    }

    for (int i = start; i < a.size(); i++) {
        if (total + a[i] > target) continue;
        state.push_back(a[i]);
        dfs(a, target, total + a[i], i, state, res);
        state.pop_back();
    }
}

/**
 * \brief: 子集和问题
 *
 * 例如，输入集合 {3,4, 5} 和目标整数 9 ，解为 {3,3, 3}, {4,5} 。
 * 输入集合是不重复的, 元素可以无限次被选取; {4,5}{5,4}是一样的
 */
std::vector<std::vector<int>> SubsetSum(const std::vector<int> &input, int target) {
    std::vector<std::vector<int>> res;
    int                           total = 0;
    int                           start = 0;
    std::vector<int>              state;
    dfs(input, target, total, start, state, res);
    return res;
}

static void dfs_duplicate(const std::vector<int> &a, int target, int total, int start,
                          std::vector<int> &state, std::vector<std::vector<int>> &res) {
    if (total == target) {
        res.push_back(state);
        return;
    }

    for (int i = start; i < a.size(); i++) {
        if (total + a[i] > target) continue;
        if (i > start && a[i] == a[i - 1]) continue;

        state.push_back(a[i]);
        dfs(a, target, total + a[i], i + 1, state, res);
        state.pop_back();
    }
}

/**
 * \brief: 子集和问题
 *
 * 例如，输入集合 {4,4, 5} 和目标整数 9 ，解为  {4,5} 。
 * 输入集合是重复的; 每个元素只可以被选取一次; {4,5}{5,4}是一样的
 */
std::vector<std::vector<int>> SubsetSum_duplicate(const std::vector<int> &input, int target) {
    std::vector<std::vector<int>> res;
    int                           total = 0;
    int                           start = 0;
    std::vector<int>              state;
    dfs_duplicate(input, target, total, start, state, res);
    return res;
}

typedef std::vector<std::vector<int>> Mat;

static void printMat(Mat &mat) {
    for (auto &row : mat) {
        for (auto &cell : row)
            if (cell == 1)
                std::cout << "x ";
            else
                std::cout << ". ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


static void dfs_eightqueens(Mat &mat, int row, int n, int &res_num, std::vector<bool> &cols,
                            std::vector<bool> &diags1, std::vector<bool> &diags2) {
    if (row == n) {
        // res.push_back(mat);
        printMat(mat);
        res_num++;
        return;
    }
    for (int col = 0; col < n; col++) {
        int diag1 = row - col + n - 1;
        int diag2 = row + col;
        if (!cols[col] && !diags1[diag1] && !diags2[diag2]) {
            mat[row][col] = 1;
            cols[col] = diags1[diag1] = diags2[diag2] = true;
            dfs_eightqueens(mat, row + 1, n, res_num, cols, diags1, diags2);
            cols[col] = diags1[diag1] = diags2[diag2] = false;
            mat[row][col]                             = 0;
        }
    }
}
/**
 * \brief: 八皇后
 * \param N: 棋盘边长的格子数
 */
void EightQueens(int N) {
    Mat               mat(N, std::vector<int>(N, 0));   //棋盘状态图
    std::vector<bool> cols(N, false);                   // 记录列有无皇后
    std::vector<bool> diags1(2 * N - 1, false);         // 记录主对角线有无皇后
    std::vector<bool> diags2(2 * N - 1, false);         // 记录副对角线有无皇后
    int               res_num = 0;                      // 解的个数
    dfs_eightqueens(mat, 0, N, res_num, cols, diags1, diags2);
    std::cout << "res number: " << res_num << std::endl;
}


#endif