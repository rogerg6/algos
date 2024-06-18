#ifndef _THREAD_SAFE_STACK_H
#define _THREAD_SAFE_STACK_H

#include <memory>
#include <mutex>
#include <stack>
#include <stdexcept>

struct empty_stack : std::exception {
    const char *what() const throw() { return "empty stack"; };
};

template<typename T>
class ThreadsafeStack {
public:
    ThreadsafeStack()
        : data_(std::stack<T>()) {}
    ~ThreadsafeStack() {}

    ThreadsafeStack(const ThreadsafeStack &other) {
        std::lock_guard<std::mutex> lk(other.mtx_);
        data_ = other.data_;
    }

    ThreadsafeStack &operator=(const ThreadsafeStack &other) = delete;

    void Push(const T &val) {
        std::lock_guard<std::mutex> lk(mtx_);
        data_.push(val);
    }

    // 返回引用
    void Pop(T &val) {
        std::lock_guard<std::mutex> lk(mtx_);
        if (data_.size() == 0) throw empty_stack();

        val = data_.top();
        data_.pop();
    }

    // 返回ptr
    std::shared_ptr<T> Pop() {
        std::lock_guard<std::mutex> lk(mtx_);
        if (data_.size() == 0) throw empty_stack();

        std::shared_ptr<T> ret(std::make_shared<T>(data_.top()));
        data_.pop();
        return ret;
    }

    /**
     * 不提供top接口的原因: 防止接口间的竞争. 考虑一种情况:
     * val = stack.top();      // 1
     * if (val == ??)
     *    do_something()       // 2
     * 如果执行完1后stack为空了, 则2这一句可能会出现bug, 具体依赖2的实现
     *
     * 故将接口top和pop合并为pop
     */
    // void Top(T &val) {
    //     std::lock_guard<std::mutex> lk(mtx_);
    //     if (data_.size() == 0) throw empty_stack();
    //     val = data_.top();
    // }

    // std::shared_ptr<T> Top() {
    //     std::lock_guard<std::mutex> lk(mtx_);
    //     if (data_.size() == 0) throw empty_stack();

    //     std::shared_ptr<T> ret(std::make_shared<T>(data_.top()));
    //     return ret;
    // }

    bool Empty() const {
        std::lock_guard<std::mutex> lk(mtx_);
        return data_.size() == 0;
    }

private:
    std::stack<T>      data_;
    mutable std::mutex mtx_;
};


#endif
