
#ifndef _PAIR_H
#define _PAIR_H


template<typename K, typename V>
struct Pair {
    K key;
    V val;
    Pair() = default;
    Pair(K k, V v)
        : key(k)
        , val(v) {}
};

#endif