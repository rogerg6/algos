
#ifndef _DYNAMIC_PROGRAMMING_H
#define _DYNAMIC_PROGRAMMING_H

#include <string>
#include <unordered_map>
#include <vector>

/**
 * \brief: 爬楼梯问题. 每次只能爬1或2步, 则爬到楼顶有几种走法
 *
 * dp[i]表示上第i个台阶总的走法个数
 * dp[i] = dp[i-1] + dp[i-2]
 */
int ClimbingStairs(int stairs) {
    if (stairs == 1 || stairs == 2) return stairs;

    int s1 = 1;
    int s2 = 2;
    int s3;
    for (int i = 3; i <= stairs; i++) {
        s3 = s1 + s2;
        s1 = s2;
        s2 = s3;
    }
    return s3;
}

/**
 * \brief: 给定一个楼梯，你每步可以上 1 阶或者 2 阶，每一阶楼梯上都贴有一个非负整数，表示你在
 * 该台阶所需要付出的代价。给定一个非负整数数组 𝑐𝑜𝑠𝑡 ，其中 𝑐𝑜𝑠𝑡[𝑖] 表示在第 𝑖 个台阶需
 * 要付出的代价， 𝑐𝑜𝑠𝑡[0] 为地面起始点。请计算最少需要付出多少代价才能到达顶部？
 *
 * dp[i]表示上第i个台阶总的最低的代价
 * dp[i] = min(dp[i-1], dp[i-2]) + cost[i]
 */
int ClimbingStairsMinCost(const std::vector<int> &cost) {
    int stairs = cost.size() - 1;
    if (stairs == 1 || stairs == 2) return cost[stairs];

    int a = cost[0], b = cost[1];
    for (int i = 2; i <= stairs; i++) {
        int c = std::min(a, b) + cost[i];
        a     = b;
        b     = c;
    }
    return b;
}

/**
 * \brief: 给定一个共有 𝑛 阶的楼梯，你每步可以上 1 阶或者 2 阶， 但不能连续两轮跳 1 阶，请问有多
 * 少种方案可以爬到楼顶。
 *
 * dp[i,j]表示上第i个台阶的总的走法个数, j表示上一轮跳的台阶数, 1<=j<=2
 * dp[i,j] = dp[i, 1] + dp[i, 2]
 *   dp[i,1] = dp[i-1,2]
 *   dp[i,2] = dp[i-2,1] + dp[i-2,2]
 */
int ClimbingStairsLimit(int n) {
    if (n == 1 || n == 2) return 1;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(3, 0));
    dp[1][1] = 1;
    dp[1][2] = 0;
    dp[2][1] = 0;
    dp[2][2] = 1;
    for (int i = 3; i <= n; i++) {
        dp[i][1] = dp[i - 1][2];
        dp[i][2] = dp[i - 2][1] + dp[i - 2][2];
    }
    return dp[n][1] + dp[n][2];
}

/**
 * \brief: 最小路径和
 * 给定一个的𝑛×𝑚的二维网格grid。网格中的每个单元格包含一个非负整数，表示该代价.
 * 机器人以左上角单元格为起始点，每次只能向下或者向右移动一步，直至到达右下角，请返回从左上角到右下角的最小路径和
 */
int MinPathSum(std::vector<std::vector<int>> mat) {
    int n = mat.size();      // n_row
    int m = mat[0].size();   // n_cols

    // 1st row
    for (int i = 1; i < m; i++) mat[0][i] += mat[0][i - 1];
    // 1st col
    for (int i = 1; i < n; i++) mat[i][0] += mat[i - 1][0];

    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++) mat[i][j] += std::min(mat[i - 1][j], mat[i][j - 1]);

    return mat[n - 1][m - 1];
}

/**
 * \brief: 01背包问题
 * 给定n个物品, 第i个物品的重量为wgt[i-1],价值为val[i-1], 和一个容量为cap的包.
 * 每个物品只能选择一次, 问在不超过容量的情况下选择的物品的最大价值为多少
 *
 * 定义dp[i, c]为前i个物品在容量为c的背包中的最大价值.则
 * 该问题的解为dp[n,cap]
 * 而每个物品都有2中选择, 选或不选
 *
 * 则可得出状态方程:
 * dp[i,c] = max(dp[i-1,c], dp[i-1, c-wgt[i-1]]+val[i-1])
 */
int Knaspack(std::vector<int> &wgt, std::vector<int> &val, int cap) {
    int                           n = wgt.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(cap + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= cap; c++) {
            if (wgt[i - 1] > c)
                // 背包放不下i号物品
                dp[i][c] = dp[i - 1][c];
            else
                dp[i][c] = std::max(dp[i - 1][c], dp[i - 1][c - wgt[i - 1]] + val[i - 1]);
        }
    }
    return dp[n][cap];
}

/**
 * \brief: 完全背包问题
 * 给定n个物品, 第i个物品的重量为wgt[i-1],价值为val[i-1], 和一个容量为cap的包.
 * 每个物品可重复选择, 问在不超过容量的情况下选择的物品的最大价值为多少
 *
 * 定义dp[i, c]为前i个物品在容量为c的背包中的最大价值.则
 * 该问题的解为dp[n,cap]
 * 而每个物品都有2中选择, 选或不选
 *
 * 则可得出状态方程:
 * dp[i,c] = max(dp[i-1,c], dp[i, c-wgt[i-1]]+val[i-1])
 */
int UnboundedKnaspack(std::vector<int> &wgt, std::vector<int> &val, int cap) {
    int                           n = wgt.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(cap + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= cap; c++) {
            if (wgt[i - 1] > c)
                // 背包放不下i号物品
                dp[i][c] = dp[i - 1][c];
            else
                dp[i][c] = std::max(dp[i - 1][c], dp[i][c - wgt[i - 1]] + val[i - 1]);
        }
    }
    return dp[n][cap];
}

/**
 * \brief: 给定n种硬币, 第i种的面值为coins[i-1], 目标金额为amt. 硬币可以
 * 重复选择. 问能凑出目标金额的最少硬币数, 凑不出则返回-1
 *
 * dp[i,m] = min(dp[i-1,m], dp[i,m-coins[i-1]]+1)
 */
int CoinChange(std::vector<int> &coins, int change) {
    int                           n   = coins.size();
    int                           MAX = change + 1;
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(change + 1, 0));

    for (int i = 0; i <= n; i++) dp[i][0] = 0;
    for (int i = 0; i <= change; i++) dp[0][i] = MAX;

    for (int i = 1; i <= n; i++) {
        for (int m = 1; m <= change; m++) {
            if (coins[i - 1] > m)
                dp[i][m] = dp[i - 1][m];
            else
                dp[i][m] = std::min(dp[i - 1][m], dp[i][m - coins[i - 1]] + 1);
        }
    }
    return dp[n][change] == MAX ? -1 : dp[n][change];
}


/**
 * \brief: 最小编辑距离. 把字符串from转换到to需要几步编辑操作
 * 编辑操作主要有3种: 增加, 修改, 删除
 *
 * 定义: dp[i,j]为把长度为i的str转换为长度为j的字符串的最小编辑步骤数
 * 每一个字符有3种选择, 则
 *
 * 对字符串s和t, s.len=m, t.len=n, 解为dp[m,n]
 * 则子问题为对于s的前i个字符, t的前j个字符, 解为d[i][j]
 * 如果s的第i-1个字符和t的第j-1个字符相同则
 *  dp[i,j] = dp[i-1,j-1]
 * 否则需要编辑,则
 *  dp[i,j] = min(dp[i,j-1], dp[i-1,j-1], dp[i-1,j]) + 1
 */
int MinEditDis(std::string from, std::string to) {
    int m = from.size();
    int n = to.size();

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) dp[0][i] = i;
    for (int i = 1; i <= m; i++) dp[i][0] = i;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (from[i - 1] == to[j - 1]) {
                // 2个字符相同
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = std::min(std::min(dp[i][j - 1], dp[i - 1][j - 1]), dp[i - 1][j]) + 1;
            }
        }
    }
    return dp[m][n];
}
#endif