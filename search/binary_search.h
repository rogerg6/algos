
#ifndef _BINARY_SEARCH_H
#define _BINARY_SEARCH_H

#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * \brief: 二分查找
 * \param vec: 有序序列
 * \param target: 查找的目标数
 * \retval: target在vec中的索引, 如果未找到返回-1
 *
 * Time : O(log n)
 * Space: O(1)
 */
template<typename T>
int BinarySearch(const std::vector<T> &vec, T target) {
    int i = 0;
    int j = vec.size() - 1;
    int mid;

    while (i <= j) {
        mid = i + (j - i) / 2;
        if (vec[mid] == target)
            return mid;
        else if (vec[mid] < target)
            i = mid + 1;
        else
            j = mid - 1;
    }
    return -1;
}

/*
给定一个长度为n的有序数组 nums和一个元素target，数组不存在重复元素. 现将target插入到数组
nums中，并保持其有序性。若数组中已存在元素,则插入到连续的target的最左边的target的左方。请返回target插入后target在数组中的索引。
*/
template<typename T>
int BinarySearchFindInsertion(const std::vector<T> &vec, T target) {
    int i = 0;
    int j = vec.size() - 1;
    int mid;

    while (i <= j) {
        mid = i + (j - i) / 2;
        if (vec[mid] == target)
            j = mid - 1;
        else if (vec[mid] < target)
            i = mid + 1;
        else
            j = mid - 1;
    }
    return i;
}

/**
 * \brief: 在vec寻找和为sum的一对数字, 任意一对即可
 * 1. 暴力枚举 Time = O(n^2)
 * 2. 二分查找 Time = O(nlog n)
 * 3. 哈希优化(本函数采用) Time=O(n), Space=O(n). 以空间换时间
 *
 *
 * \retval: 返回2个数的索引
 */
std::vector<int> TwoSum(const std::vector<int> &vec, int sum) {
    std::unordered_map<int, int> hashmap;

    for (int i = 0; i < vec.size(); i++) {
        int n = sum - vec[i];
        if (hashmap.find(n) != hashmap.end()) return {i, hashmap[n]};
        hashmap.emplace(vec[i], i);
    }
    return {-1, -1};
}



#endif