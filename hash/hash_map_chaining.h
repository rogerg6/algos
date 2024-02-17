
#ifndef _HASH_MAP_CHAINING_H_
#define _HASH_MAP_CHAINING_H_

#include "pair.h"
#include <functional>
#include <iostream>
#include <vector>

/**
 * \brief: 链式哈希表, 键不重复.
 *         基于嵌套vector实现, 简化编码
 */
template<typename K, typename V>
class HashMapChaining {
    using PairPtr = Pair<K, V> *;

public:
    HashMapChaining(int cap = 1024, double load_thres = 0.75, int extend_ratio = 2)
        : _capacity(cap)
        , _load_thres(load_thres)
        , _extend_ratio(extend_ratio) {
        _buckets.resize(cap);
        _size = 0;
    }
    ~HashMapChaining() {
        for (auto &bucket : _buckets) {
            for (PairPtr pair : bucket) {
                delete pair;
            }
        }
    }

    int Size() const { return _size; }
    // 返回当前的负载因子
    double LoadThres() const { return (double)_size / _capacity; }

    void Put(K key, V val) {
        if (LoadThres() > _load_thres) {
            Extend();
        }
        int idx = HashFn(key);

        for (PairPtr p : _buckets[idx])
            if (p->key == key) {
                // std::cout << key << std::endl;
                // _cnt++;
                p->val = val;
                return;
            }

        _buckets[idx].push_back(new Pair<K, V>(key, val));
        _size++;
    }

    void Remove(K key) {
        int                   idx    = HashFn(key);
        std::vector<PairPtr> &bucket = _buckets[idx];
        for (auto it = bucket.begin(); it != bucket.end();) {
            if ((*it)->key == key) {
                it = bucket.erase(it);
                _size--;
            } else {
                ++it;
            }
        }
    }

    const PairPtr Get(K key) const {
        int idx = HashFn(key);
        for (PairPtr pair : _buckets[idx]) {
            if (pair->key == key) {
                return pair;
            }
        }
        return nullptr;
    }

    void Print() const {
        for (int i = 0; i < _capacity; ++i) {
            if (_buckets[i].size() <= 0) continue;
            std::cout << i << ": ";
            for (PairPtr p : _buckets[i]) std::cout << p->key << ":" << p->val << ", ";
            std::cout << std::endl;
        }

        std::cout << "size: " << _size << "\ncapcity = " << _capacity
                  << "\nload_thres: " << LoadThres() << "\ncnt: " << _cnt << std::endl;
    }

private:
    int HashFn(K key) const { return _hash_fn(key) % _capacity; }

    void Extend() {
        std::vector<std::vector<PairPtr>> tmp_buckets = _buckets;
        _buckets.clear();
        _size = 0;
        _capacity *= _extend_ratio;
        _buckets.resize(_capacity);

        for (auto &bucket : tmp_buckets) {
            for (PairPtr p : bucket) {
                Put(p->key, p->val);
                delete p;
            }
        }
    }


private:
    int                               _size;       // 表中键值对的个数
    int                               _capacity;   // 表的容量
    std::vector<std::vector<PairPtr>> _buckets;    //桶, 存放pairs
    double _load_thres;   // 触发扩容的负载因子=_size/_capacity, 一般大于0.75便开始扩容
    int          _extend_ratio;   // 扩容倍数
    std::hash<K> _hash_fn;        // 哈希函数

    int _cnt = 0;   // debug
};

#endif