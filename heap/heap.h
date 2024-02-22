/**
 * \date: 2024-02-22
 *
 * 堆是一种特殊的完全二叉树,所以用树组存储很适合
 * 堆通常用作实现优先队列，大顶堆相当于元素按从大到小顺序出队的优先队列。
 *
 * 时间复杂度:
 *     元素入堆 𝑂(log 𝑛)
 *     堆顶元素出堆 𝑂(log 𝑛)
 *     访问堆顶 元素 𝑂(1) 等
 *     建堆: 输入𝑛个元素并建堆的时间复杂度可以优化至 𝑂(𝑛)
 */

#ifndef __MAX_HEAP_H
#define __MAX_HEAP_H

#include <stdexcept>
#include <vector>

/**
 * \brief: 大根堆, 树组实现
 *
 */
template<typename T>
class MaxHeap {
public:
    MaxHeap() {}

    // O(n)
    MaxHeap(const std::vector<T> &list)
        : _data(list) {
        for (int i = parent(Size() - 1); i >= 0; --i) siftDown(i);
    }
    ~MaxHeap() {}

    int  Size() const { return _data.size(); }
    bool Empty() const { return _data.size() == 0; }

    // 查看堆顶元素
    T Peek() const {
        if (Empty()) throw std::runtime_error("Heap is empty.");
        return _data[0];
    }

    // 把val添加到堆中
    void Push(T val) {
        _data.push_back(val);
        siftUp(_data.size() - 1);
    }

    /* 把堆顶元素弹出
     * 交换堆顶和堆底的元素, 从底部弹出元素, 从顶部往下堆化
     */
    T Pop() {
        if (Empty()) throw std::runtime_error("Heap is empty.");
        swap(_data[0], _data[Size() - 1]);
        T ret = _data.back();
        _data.pop_back();
        siftDown(0);
        return ret;
    }

#ifdef UNIT_TEST
public:
#else
private:
#endif
    void swap(T &m, T &n) {
        T tmp = m;
        m     = n;
        n     = tmp;
    }

    // 自下往上堆化, 使堆满足条件
    void siftUp(int i) {
        while (i > 0) {
            int p = parent(i);
            if (p < 0 || _data[p] >= _data[i]) break;
            swap(_data[p], _data[i]);
            i = p;
        }
    }

    // 自上往下堆化
    void siftDown(int i) {
        while (i < Size()) {
            int l  = left(i);
            int r  = right(i);
            int ma = i;
            if (l < Size() && _data[ma] < _data[l]) ma = l;
            if (r < Size() && _data[ma] < _data[r]) ma = r;

            // 无需再堆化
            if (i == ma) break;
            swap(_data[i], _data[ma]);
            i = ma;
        }
    }

    int left(int i) {
        return 2 * i + 1;
    }
    int right(int i) {
        return 2 * i + 2;
    }
    int parent(int i) {
        return (i - 1) / 2;
    }

    std::vector<T> _data;
};


template<typename T>
class MinHeap {
public:
    MinHeap() {}
    MinHeap(const std::vector<T> &list)
        : _data(list) {
        for (int i = parent(Size() - 1); i >= 0; --i) siftDown(i);
    }
    ~MinHeap() {}

    int  Size() const { return _data.size(); }
    bool Empty() const { return _data.size() == 0; }

    // 查看堆顶元素
    T Peek() const {
        if (Empty()) throw std::runtime_error("Heap is empty.");
        return _data[0];
    }

    // 把val添加到堆中
    void Push(T val) {
        _data.push_back(val);
        siftUp(_data.size() - 1);
    }

    /* 把堆顶元素弹出
     * 交换堆顶和堆底的元素, 从底部弹出元素, 从顶部往下堆化
     */
    T Pop() {
        if (Empty()) throw std::runtime_error("Heap is empty.");
        swap(_data[0], _data[Size() - 1]);
        T ret = _data.back();
        _data.pop_back();
        siftDown(0);
        return ret;
    }

#ifdef UNIT_TEST
public:
#else
private:
#endif
    void swap(T &m, T &n) {
        T tmp = m;
        m     = n;
        n     = tmp;
    }

    // 自下往上堆化, 使堆满足条件
    void siftUp(int i) {
        while (i > 0) {
            int p = parent(i);
            if (p < 0 || _data[p] <= _data[i]) break;
            swap(_data[p], _data[i]);
            i = p;
        }
    }

    // 自上往下堆化
    void siftDown(int i) {
        while (i < Size()) {
            int l  = left(i);
            int r  = right(i);
            int ma = i;
            if (l < Size() && _data[ma] > _data[l]) ma = l;
            if (r < Size() && _data[ma] > _data[r]) ma = r;

            // 无需再堆化
            if (i == ma) break;
            swap(_data[i], _data[ma]);
            i = ma;
        }
    }

    int left(int i) {
        return 2 * i + 1;
    }
    int right(int i) {
        return 2 * i + 2;
    }
    int parent(int i) {
        return (i - 1) / 2;
    }

    std::vector<T> _data;
};

#endif