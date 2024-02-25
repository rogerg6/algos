#ifndef _SORT_H
#define _SORT_H

#include <vector>

template<typename T>
void Swap(T &m, T &n) {
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
        if (min != i) Swap(vec[i], vec[min]);
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
                Swap(vec[j], vec[j + 1]);
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

#endif