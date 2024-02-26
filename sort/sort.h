#ifndef _SORT_H
#define _SORT_H

#include "timer.h"
#include <algorithm>
#include <heap.h>
#include <iostream>
#include <vector>

template<typename T>
static void swap(T &m, T &n) {
    T tmp = m;
    m     = n;
    n     = tmp;
}

/**
 * \brief: 选择排序. 升序
 * Time = O(n^2)
 * Space = O(1)
 * 原地排序, 非稳定排序
 */
template<typename T>
void SelectionSort(std::vector<T> &vec) {
    int size = vec.size();
    for (int i = 0; i < size - 1; i++) {
        int min = i;
        for (int j = i + 1; j < size; j++) {
            if (vec[j] < vec[i]) min = j;
        }
        if (min != i) swap(vec[i], vec[min]);
    }
}

/**
 * \brief: 冒泡排序. 升序
 * Time = O(n^2), 加入flag优化后最佳为O(n)
 * Space = O(1)
 * 自适应性排序
 * 原地排序
 * 稳定排序(相等的元素不交换位置)
 */
template<typename T>
void BubbleSort(std::vector<T> &vec) {
    int size = vec.size();
    for (int i = size - 1; i > 0; i--) {
        bool flag = false;
        for (int j = 0; j < i; j++) {
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
                flag = true;
            }
        }
        // 如果没有交换,则说明vec有序
        if (!flag) break;
    }
}

/**
 * \brief: 插入排序. 升序
 * Time = O(n^2), 输入有序时为最佳O(n)
 * Space = O(1)
 * 自适应性排序
 * 原地排序
 * 稳定排序
 *
 * 输入规模小的时候, 插排应用的比较多
 */
template<typename T>
void InsertionSort(std::vector<T> &vec) {
    int size = vec.size();
    int i, j;
    T   base;

    for (i = 1; i < size; i++) {
        base = vec[i];
        for (j = i - 1; j >= 0 && vec[j] > base; j--) {
            vec[j + 1] = vec[j];
        }
        vec[j + 1] = base;
    }
}


/**
 * \brief: for quick sort use
 * 返回a[left], a[mid], a[right]这三个数中的中位数在a中的索引
 */
template<typename T>
static int mediaThree(std::vector<T> &a, int left, int mid, int right) {
    if ((a[left] < a[mid]) ^ (a[left] < a[right]))
        return left;
    else if ((a[mid] < a[left]) ^ (a[mid] < a[right]))
        return mid;
    else
        return right;
}

/* for quick sort use */
template<typename T>
static int partition(std::vector<T> &a, int left, int right) {
    int i = left;
    int j = right;

    // 选取left,mid,right的中位数为基准值
    int k = mediaThree(a, left, left + (right - left) / 2, right);
    swap(a[i], a[k]);
    T base = a[i];

    while (i < j) {
        while (i < j && a[j] >= base) j--;
        while (i < j && a[i] <= base) i++;
        swap(a[i], a[j]);
    }
    swap(a[left], a[i]);
    return i;
}

/********************** 快速排序. 升序 ****************************
 *
 * Time: 平均O(nlog n), 输入有序时为最差O(n^2)
 * Space: 最差 O(n)
 * 自适应性排序
 * 原地排序
 * 非稳定排序
 *
 * 快排的效率和基准值的选择有很大的关系, 如果运气差选的不好, 则partition的时候
 * 其中一个子数组可能为空,这样效率分治策略就失效了
 * 由此可以有2个措施优化:
 *   1. 选取数组的左中右的中位数为基准值
 *   2. 利用尾递归优化, 先堆较小的子数组进行递归, 防止栈帧空间的累积, 可以让排序过程
 *      中最大的栈帧占用变小
 *
 * \param vec: 待排序树组, 堆vec的[left, right]进行排序
 *
 */
template<typename T>
void QuickSort(std::vector<T> &vec, int left, int right) {
    if (left >= right) return;

    int pivot = partition(vec, left, right);
    QuickSort(vec, left, pivot - 1);
    QuickSort(vec, pivot + 1, right);
}

/**
 * \brief: 尾递归优化版本
 */
template<typename T>
void QuickSort_v2(std::vector<T> &vec, int left, int right) {
    while (left < right) {
        int pivot = partition(vec, left, right);
        if (pivot - left < right - pivot) {
            // 递归排序左子数组
            QuickSort_v2(vec, left, pivot - 1);
            left = pivot + 1;
        } else {
            // 递归排序右子数组
            QuickSort_v2(vec, pivot + 1, right);
            right = pivot - 1;
        }
    }
}


/*********************** 归并排序 升序 *************************
 *
 * Time: O(nlog n). 划分步骤递归深度为log n, 合并步骤每次为n
 * Space: O(n), 划分步骤递归深度为O(log n), 合并步骤每次为O(n)的额外空间.
 * 非自适应性排序
 * 非原地排序
 * 稳定排序
 *
 * TODO: 但是对于链表存储的序列, 使用归并排序, 空间复杂度可优化值O(1), 不需要额外的空间存储,
 * 只需改变节点指针即可.
 */
template<typename T>
void MergeSort(std::vector<T> &vec, int left, int right) {
    if (left == right) return;

    int mid = left + (right - left) / 2;

    MergeSort(vec, left, mid);
    MergeSort(vec, mid + 1, right);

    std::vector<T> tmp(vec.begin() + left, vec.begin() + right + 1);
    int            lstart = 0, lend = mid - left;            // left start, left end
    int            rstart = lend + 1, rend = right - left;   // right start, right end
    int            i = left;
    for (; i <= right; i++) {
        if (lstart > lend)
            vec[i] = tmp[rstart++];
        else if (rstart > rend || tmp[lstart] < tmp[rstart])
            vec[i] = tmp[lstart++];
        else
            vec[i] = tmp[rstart++];
    }
}




/** for heap sort use
 * 自上往下堆化
 * \param vec: 堆数组
 * \param size: 堆的大小
 * \param i: 从i开始向下堆化
 */
template<typename T>
static void siftDown(std::vector<T> &vec, int size, int i) {
    while (i < size) {
        int l  = 2 * i + 1;
        int r  = 2 * i + 2;
        int ma = i;
        if (l < size && vec[ma] < vec[l]) ma = l;
        if (r < size && vec[ma] < vec[r]) ma = r;

        // 无需再堆化
        if (i == ma) break;
        swap(vec[i], vec[ma]);
        i = ma;
    }
}


/*********************** 堆排序 升序 *************************
 *
 * Time: O(nlog n), 建堆O(n), 每次弹出log n, 执行n次
 * Space: O(1)
 * 非自适应性排序
 * 原地排序
 * 非稳定排序
 *
 */
template<typename T>
void HeapSort(std::vector<T> &vec, int left, int right) {
    // 建立大根堆
    int size = vec.size();
    for (int i = size - 1; i >= 0; i--) siftDown(vec, size, i);

    // 依次弹出堆顶元素即可
    for (int i = size - 1; i >= 0; i--) {
        swap(vec[0], vec[i]);
        siftDown(vec, i, 0);
    }
}

/********************* 桶排序 *************************
 *
 * Time: O(n + k)
 * Space: O(n + k)
 * 自适应性排序
 * 非原地排序
 * 稳定排序性取决于桶内排序算法是否为稳定排序算法
 *
 * 桶排的效率取决于能否把元素均匀份分配到各个桶中.
 * 如果输入数据分布不均匀, 可以把多的桶递归进行桶排; 或者根据输入数据的特点划分桶
 *
 * 步骤:
 *  1. 初始化 𝑘 个桶，将 𝑛 个元素分配到 𝑘 个桶中。
 *  2. 对每个桶分别执行排序
 *  3. 按照桶的从小到大的顺序，合并结果。
 */
void BucketSort(std::vector<float> &vec) {
    int                             k = vec.size() / 2;
    std::vector<std::vector<float>> buckets(k);

    // 把vec中度元素放入相应的桶
    for (float &n : vec) {
        int i = k * n;
        buckets[i].push_back(n);
    }

    // 对每个桶进行排序
    for (auto &b : buckets) std::sort(b.begin(), b.end());

    // 合并
    int i = 0;
    for (auto &b : buckets) {
        for (float &n : b) vec[i++] = n;
    }
}


/********************* 计数排序 *************************
 *
 * 对长度为n, 最大值为m的非负整数数组
 * Time: O(n)
 * Space: O(n + m)
 * 非原地排序
 * 稳定排序
 *
 * 适用非负整数, 数据量大但是数据范围小的情况
 *
 */
void CountingSort(std::vector<int> &vec) {
    // find max
    int max = 0;
    for (int &n : vec)
        if (n > max) max = n;

    std::vector<int> counter(max + 1, 0);   // 存放前缀和
    for (int &n : vec) {
        counter[n]++;
    }
    // 计算前缀和 prefix[i]
    for (int i = 0; i < max; i++) {
        counter[i + 1] += counter[i];
    }

    // 反向遍历vec, 把元素放入res中
    std::vector<int> res(vec.size());
    for (int i = vec.size() - 1; i >= 0; i--) {
        int num = vec[i];
        // 前缀和-1就是num在结果数组res中num最后一个出现的位置
        res[counter[num] - 1] = num;
        counter[num]--;
    }

    // 结果res保存到原数组
    vec = res;
}


/* for radix sort use
 * 求n的log10(exp)+1 位上的数字
 */
static int digit(int n, int exp) {
    return (n / exp) % 10;
}

/* for radix sort use
 * 计数排序（根据 nums 第 k 位排序）
 */
static void countingSort(std::vector<int> &vec, int exp) {
    std::vector<int> counter(10, 0);
    for (auto &n : vec) {
        int i = digit(n, exp);
        counter[i]++;
    }

    // 计算前缀和 prefix[i]
    for (int i = 0; i < 9; i++) {
        counter[i + 1] += counter[i];
    }
    // 反向遍历vec, 把元素放入res中
    std::vector<int> res(vec.size());
    for (int i = vec.size() - 1; i >= 0; i--) {
        int idx = digit(vec[i], exp);
        // 前缀和-1就是num在结果数组res中num最后一个出现的位置
        res[counter[idx] - 1] = vec[i];
        counter[idx]--;
    }

    // 结果res保存到原数组
    for (int i = 0; i < res.size(); i++) vec[i] = res[i];
}

/********************* 基数排序 *************************
 *
 * 对长度为n, 进制为d, 最大位数为k的数组
 * Time: O((n + d)k)
 * Space: O(n + d), 和计数排序类似
 * 非原地排序
 * 稳定排序
 *
 * 前提是数据必须可以表示为固定位数的格式，且位数不能过大
 *
 */
void RadixSort(std::vector<int> &vec) {
    int m = *std::max_element(vec.begin(), vec.end());

    for (int exp = 1; exp <= m; exp *= 10) {
        countingSort(vec, exp);
    }
}


#endif