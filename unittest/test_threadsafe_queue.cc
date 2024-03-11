#include "threadSafeQueue.h"
#include "gtest/gtest.h"
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/**
 * \brief: 专门用来测试threadsafeQueue的类
 * 当Item被push进queue时, 计算当时的timestamp
 * 当Item被pop时, 就可以得到其timestamp, 由此可以判断是否是FIFO的
 */
class Item {
public:
    Item() {}
    Item(const Item &other) {
        this->tm = other.tm;
        // std::cout << "copy constructor" << std::endl;
    }

    Item &operator=(const Item &other) {
        this->tm = other.tm;
        std::cout << "copy assignment" << std::endl;
        return *this;
    }

    // push进queue时会被调用, 然后计算push时的timestam
    Item(Item &&other) {
        tm = std::chrono::system_clock::now();
        //     std::cout
        //         <<
        //         std::chrono::duration_cast<std::chrono::nanoseconds>(tm.time_since_epoch()).count()
        //         << '\n';
    }
    // 什么都不做
    Item &operator=(Item &&other) {
        // std::cout << "move assignment" << std::endl;
        return *this;
    }


public:
    std::chrono::time_point<std::chrono::system_clock> tm;
};

const int         n_push_thrds = 10;   // number of push thread
const int         n_pop_thrds  = 10;   // number of pop thread
std::vector<Item> res;
std::mutex        mut_res;
bool              push_quit = false;
bool              pop_quit  = false;

void ThreadFuncPush(ThreadsafeQueue<Item> &q) {
    while (!push_quit) {
        Item it;
        q.Push(it);
        // break;
    }
}

void ThreadFuncPop(ThreadsafeQueue<Item> &q) {
    Item it;

    while (1) {
        if (q.WaitForPop(it)) {
            std::unique_lock<std::mutex> lk(mut_res);
            res.push_back(it);
            lk.unlock();
        } else {
            if (pop_quit) break;
        }
    }
}

TEST(thread_safe, queue) {
    std::thread          *push_thrds[n_push_thrds] = {nullptr};
    std::thread          *pop_thrds[n_pop_thrds]   = {nullptr};
    ThreadsafeQueue<Item> q;

    // start threads
    for (int i = 0; i < n_pop_thrds; i++) {
        pop_thrds[i] = new std::thread(ThreadFuncPop, std::ref(q));
    }
    for (int i = 0; i < n_push_thrds; i++) {
        push_thrds[i] = new std::thread(ThreadFuncPush, std::ref(q));
    }

    sleep(5);
    push_quit = true;
    for (int i = 0; i < n_push_thrds; i++) {
        push_thrds[i]->join();
        delete push_thrds[i];
    }
    sleep(5);
    pop_quit = true;
    for (int i = 0; i < n_pop_thrds; i++) {
        pop_thrds[i]->join();
        delete pop_thrds[i];
    }

    for (int i = 0; i < res.size() - 1; i++) {
        auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(res[i].tm.time_since_epoch())
                      .count();
        auto t2 =
            std::chrono::duration_cast<std::chrono::nanoseconds>(res[i + 1].tm.time_since_epoch())
                .count();
        EXPECT_TRUE(t1 <= t2);
    }
}