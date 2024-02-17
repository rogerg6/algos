
#ifndef __HASH_MAP_OPENADDR_H__
#define __HASH_MAP_OPENADDR_H__

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "pair.h"

/**
 * \brief: 开放寻址哈希表, 键不重复.
 *         当发生哈希冲突时, 采用线性遍历解决冲突. 使用步长(1)向后线性遍历
 */
template<typename K, typename V>
class HashMapOpenAddressing {
    using PairPtr = Pair<K, V> *;

public:
    HashMapOpenAddressing(int cap = 1000, double load_thres = 0.75, int extend_ratio = 2)
        : _size(0)
        , _capacity(cap)
        , _removed(nullptr)
        , _load_thres(load_thres)
        , _extend_ratio(extend_ratio) {
        _buckets = std::vector<PairPtr>(cap, nullptr);
        _removed = new Pair<K, V>();
    }
    ~HashMapOpenAddressing() {
        for (int i = 0; i < _capacity; ++i) {
            if (_buckets[i] != nullptr && _buckets[i] != _removed) {
                delete _buckets[i];
            }
        }
        delete _removed;
    }

    int    Size() const { return _size; }
    double LoadThres() const { return (double)_size / _capacity; }

    void Put(K key, V val) {
        if (LoadThres() > _load_thres) {
            Extend();
        }

        int idx = HashFn(key);
        int j;
        for (int i = 0; i < _capacity; ++i) {
            j         = (idx + i) % _capacity;
            PairPtr p = _buckets[j];
            if (p == nullptr || p == _removed) {
                _buckets[j] = new Pair<K, V>(key, val);
                _size++;
                break;
            } else if (p->key == key) {
                p->val = val;
                break;
            }
        }
    }

    void Remove(K key) {
        int idx = HashFn(key);
        int j;

        for (int i = 0; i < _capacity; ++i) {
            j         = (idx + i) % _capacity;
            PairPtr p = _buckets[j];
            if (p == nullptr)
                return;
            else if (p != _removed && p->key == key) {
                delete p;
                _buckets[j] = _removed;
                _size--;
                return;
            }
        }
    }

    const PairPtr Get(K key) const {
        int idx = HashFn(key);
        int j;

        for (int i = 0; i < _capacity; ++i) {
            j         = (idx + i) % _capacity;
            PairPtr p = _buckets[j];
            if (p == nullptr) {
                return nullptr;
            } else if (p != _removed && p->key == key) {
                return p;
            }
        }
        return nullptr;
    }

    void Print() const {
        for (int i = 0; i < _buckets.size(); i++) {
            PairPtr p = _buckets[i];
            std::cout << i << ": ";
            if (p == nullptr)
                std::cout << "null" << std::endl;
            else if (p == _removed)
                std::cout << "rm" << std::endl;
            else {
                std::cout << p->key << ":" << p->val << std::endl;
            }
        }
        std::cout << "size: " << _size << "\ncapcity = " << _capacity
                  << "\nload_thres: " << LoadThres()

                  << std::endl;
    }

private:
    int HashFn(K key) const { return _hash_fn(key) % _capacity; }

    void Extend() {
        std::vector<PairPtr> tmp_buckets = _buckets;
        _size                            = 0;
        _capacity *= _extend_ratio;
        _buckets = std::vector<PairPtr>(_capacity, nullptr);

        // TODO: 可以用移动语义
        for (PairPtr p : tmp_buckets) {
            if (p != nullptr && p != _removed) {
                Put(p->key, p->val);
                delete p;
            }
        }
    }


#ifdef UNIT_TEST
public:
#else
private:
#endif

    int                  _size;       // 表中键值对的个数
    int                  _capacity;   // 表的容量
    std::vector<PairPtr> _buckets;    //桶, 存放pairs
    PairPtr              _removed;    // 删除标记
    double _load_thres;   // 触发扩容的负载因子=_size/_capacity, 一般大于0.75便开始扩容
    int          _extend_ratio;   // 扩容倍数
    std::hash<K> _hash_fn;        // 哈希函数
};


#endif