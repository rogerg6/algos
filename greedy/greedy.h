#ifndef __GREEDY_H
#define __GREEDY_H

#include <algorithm>
#include <cmath>
#include <vector>

/**
 * 贪心算法思想
 *
 * 适用场景:
 *   1. 可以保证找到最优解：贪心算法在这种情况下往往是最优选择，因为它往往比回溯、动态规划更高效。
 *   2. 可以找到近似最优解：
 */


/**
 * \brief: 给定n种硬币, 第i种的面值为coins[i-1], 目标金额为amt. 硬币可以
 * 重复选择. 问能凑出目标金额的最少硬币数, 凑不出则返回-1
 *
 * 贪心算法的效率比dp还要高, 但缺点也很明显: 对于某些硬币面值组合，贪心算法并不能找到最优解
 */
int CoinChangeGreedy(std::vector<int> &coins, int amt) {
    // 假设coins是升序的
    int i   = coins.size() - 1;
    int res = 0;

    while (amt > 0) {
        while (i > 0 && coins[i] > amt) i--;
        amt -= coins[i];
        res++;
    }
    return amt == 0 ? res : -1;
}

/**
 * \brief: 分数背包问题
 * 给定n个物品, 第i个物品的重量为wgt[i-1],价值为val[i-1], 和一个容量为cap的包.
 * 每个物品只能选择一次,但可以选择物品的一部分，价值根据选择的重量比例计算
 * 问在不超过容量的情况下选择的物品的最大价值为多少
 *
 */
struct Item {
    int w;
    int v;
};

double FractionalKnaspack(std::vector<int> &wgt, std::vector<int> &val, int cap) {
    int               n = wgt.size();
    std::vector<Item> items;
    for (int i = 0; i < n; i++) items.push_back(Item{wgt[i], val[i]});

    // 降序排列
    std::sort(items.begin(), items.end(), [](Item &a, Item &b) {
        return (double)a.v / a.w > (double)b.v / b.w;
    });

    double res = 0.0;
    for (auto &i : items) {
        if (cap >= i.w) {
            cap -= i.w;
            res += i.v;
        } else {
            res += (double)i.v * cap / i.w;
            break;
        }
    }
    return res;
}

/**
 * \brief: 最大容量问题.
 * 输入一个数组ht,数组中每个元素代表一个隔板的高度, 数组中任意一个隔板和他们之间的
 * 空间可以组成一个容器. 容器的容量=高度x宽度, 高度由最短的板决定,宽度是2个隔板间的
 * 索引之差, 求可以组成的容器的最大容量
 */
int MaxCapcity(std::vector<int> &ht) {
    int i       = 0;
    int j       = ht.size() - 1;
    int max_cap = 0;

    while (i < j) {
        int w = j - i;
        int h;
        if (ht[i] >= ht[j]) {
            h = ht[j];
            j--;
        } else {
            h = ht[i];
            i++;
        }
        int cap = w * h;
        if (cap > max_cap) max_cap = cap;
    }

    return max_cap;
}

/**
 * \brief: 最大切分乘积.
 * 给定一个正整数n, 将其切分为至少2个正整数, 求切分后所有的整数的积最大是多少?
 *
 * 1
 * 2  切<不切
 * 3  切<不切
 * 4  切>不切, 每次切出2
 * 5  切>不切, 切出2,3
 * 6  切>不切, 切出3,3
 *
 * 所以应该每次切3, 则余数有3种情况:
 *  0  正好整除
 *  1  则接一个3, 3+1=4, 应切成2+2
 *  2
 *
 */
int MaxProductCutting(int n) {
    if (n <= 3) return n - 1;

    int n3     = n / 3;
    int remain = n % 3;

    if (remain == 0)
        return std::pow(3, n3);
    else if (remain == 2)
        return std::pow(3, n3) * remain;
    else
        return std::pow(3, n3 - 1) * 4;
}



#endif