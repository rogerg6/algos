#ifndef _THREAD_SAFE_QUEUE_H
#define _THREAD_SAFE_QUEUE_H

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

/**
 * \brief: 线程安全队列
 */
template<typename T>
class ThreadsafeQueue {
public:
    ThreadsafeQueue() {}
    ~ThreadsafeQueue() {}

    void Push(T val) {
        std::lock_guard<std::mutex> lk(mtx_);
        q_.push(std::move(val));
        cond_.notify_one();
    }

    void WaitPop(T &val) {
        std::unique_lock<std::mutex> lk(mtx_);
        cond_.wait(lk, [this] { return !q_.empty(); });
        val = std::move(q_.front());
        q_.pop();
    }
    // Pop的timeout, if timeout return
    bool WaitForPop(T &val) {
        auto                         timeout = std::chrono::microseconds(500);
        std::unique_lock<std::mutex> lk(mtx_);
        if (!cond_.wait_for(lk, timeout, [this] { return !q_.empty(); })) return false;
        val = std::move(q_.front());
        q_.pop();
        return true;
    }

    bool Empty() {
        std::lock_guard<std::mutex> lk(mtx_);
        return q_.empty();
    }

private:
    std::queue<T>           q_;
    std::mutex              mtx_;
    std::condition_variable cond_;
};


#endif