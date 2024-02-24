
#ifndef LIST_STACK_H
#define LIST_STACK_H


#include <stdexcept>
#include <vector>

/**
 * \brief: 基于列表实现的栈
 */
template<typename T>
class ListStack {
public:
    ListStack() {}
    ~ListStack() {}

    void Push(T val) { _data.push_back(val); }

    T Pop() {
        if (_data.size() < 0) {
            throw std::runtime_error("stack is empty!");
        }
        T tmp = _data.back();
        _data.pop_back();
        return tmp;
    }

    T Peek() const {
        if (_data.size() < 0) {
            throw std::runtime_error("stack is empty!");
        }
        return _data.back();
    }

    bool Empty() const { return _data.size() == 0; }
    int  Size() const { return _data.size(); }

private:
    std::vector<T> _data;
};


#endif