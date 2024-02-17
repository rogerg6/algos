
#include "hash_map_chaining.h"
#include "hash_map_openaddr.h"
#include "gtest/gtest.h"
#include <cstdlib>
#include <ctime>
#include <map>
#include <type_traits>

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

std::string RandomString(size_t length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    std::string result;
    result.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        result += charset[std::rand() % (sizeof(charset) - 1)];
    }
    return result;
}

// 通用模板
template<typename T>
T genTypeVar(int len) {
    return T();
}

// 模板特化
template<>
int genTypeVar<int>(int len) {
    std::srand(std::time(0));
    return std::rand() % len;
}

// 模板特化
template<>
std::string genTypeVar<std::string>(int len) {
    std::srand(std::time(0));
    return RandomString(std::rand() % len + 1);
}

template<typename K, typename V>
void test() {
    HashMapOpenAddressing<K, V> map(10);
    int                         test_round_cnt = 10000;   // 循环测试次数
    int                         put_cnt, rm_cnt;
    K                           key;
    V                           val;

    std::map<K, V> m;

    EXPECT_EQ(map.Size(), 0);
    EXPECT_EQ(m.size(), 0);
    for (int i = 0; i < test_round_cnt; i++) {
        std::srand(std::time(0));
        put_cnt = std::rand() % 100 + 1;
        rm_cnt  = std::rand() % 100 + 1;

        // put
        for (int j = 0; j < put_cnt; j++) {
            key    = genTypeVar<K>(100);
            val    = genTypeVar<V>(100);
            m[key] = val;
            map.Put(key, val);
            EXPECT_EQ(map.Size(), m.size());
        }

        // get
        for (auto it = m.begin(); it != m.end(); ++it) {
            K    key = it->first;
            V    val = it->second;
            auto pp  = map.Get(key);
            EXPECT_TRUE(pp != nullptr);
            EXPECT_EQ(val, pp->val);
        }

        // rm
        for (int j = 0; j < rm_cnt; j++) {
            key = std::rand() % 100000;
            if (m.find(key) != m.end()) m.erase(key);
            map.Remove(key);
            EXPECT_EQ(map.Size(), m.size());
        }
    }

    for (auto it = m.begin(); it != m.end();) {
        map.Remove(it->first);
        it = m.erase(it);
        EXPECT_EQ(map.Size(), m.size());
    }
    EXPECT_EQ(map.Size(), 0);
    EXPECT_EQ(m.size(), 0);
}

TEST(hash_map_chaining, function_test) {
    test<int, int>();
    test<std::string, int>();
}


TEST(hash_map_open_addressing, function_test) {
    test<int, int>();
    test<std::string, int>();
}
